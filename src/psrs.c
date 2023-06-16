#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/psrs.h"
#include "../include/sorting.h"
#include "../include/utils.h"

/*
 * TODO
 */
void regular_sampling(int* array, long long length, int n_threads, int* pivots)
{
    int* samples;
    samples = (int*)malloc(n_threads * n_threads * sizeof(int));

#pragma omp parallel num_threads(n_threads) shared(array, length, n_threads, samples)
    {
        int thread_id = omp_get_thread_num();
        long long low, high;

        low = thread_id * (length / n_threads);
        high = (thread_id + 1) * (length / n_threads) - 1;

        if (length % n_threads) {
            if (thread_id < (length % n_threads)) {
                low += thread_id;
                high += thread_id + 1;
            } else {
                low += length % n_threads;
                high += length % n_threads;
            }

            low = min(low, length - 1);
            high = min(high, length - 1);
        }
        quicksort(array, low, high);

        long long sample_index, array_index;
        for (long long i = 0; i < n_threads; ++i) {
            sample_index = i + thread_id * n_threads;
            array_index = low + i * length / (n_threads * n_threads);
            samples[sample_index] = array[array_index];
        }
    }

    quicksort(samples, 0, n_threads * n_threads - 1);

    for (int i = 0; i < n_threads - 1; ++i) {
        pivots[i] = samples[(i + 1) * n_threads + n_threads / 2 - 1];
    }

    free(samples);
}

/*
 * TODO
 */
void psrs(int* array, long long length, int n_threads)
{

    int* pivots;
    pivots = (int*)malloc((n_threads - 1) * sizeof(int));

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (!rank) {
        regular_sampling(array, length, n_threads, pivots);
        for (long long i = 0; i < length; ++i) {
            printf("%d ", array[i]);
        }

        printf("\n");
        for (int i = 0; i < n_threads - 1; ++i) {
            printf("%d ", pivots[i]);
        }
        printf("\n");
    }
    MPI_Bcast(pivots, n_threads - 1, MPI_INT, 0, MPI_COMM_WORLD);

    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    int* sendc;
    sendc = (int*)malloc(comm_size * sizeof(int));

    for (int i = 0; i < comm_size; ++i) {
        sendc[i] = length / n_threads;
        if (i < length % n_threads) {
            ++(sendc[i]);
        }
    }

    int* displacement;
    displacement = (int*)malloc((comm_size + 1) * sizeof(int));
    get_displacement(sendc, displacement);

    MPI_Scatterv(array, sendc, displacement, MPI_INT,
        array, sendc[rank], MPI_INT, 0, MPI_COMM_WORLD);

    multpivot_partition(array, sendc[rank], pivots, displacement, sendc);

    int* recvc;
    recvc = (int*)malloc(comm_size * sizeof(int));

    MPI_Alltoall(sendc, 1, MPI_INT, recvc, 1, MPI_INT, MPI_COMM_WORLD);

    int* recvdisp;
    recvdisp = (int*)malloc((comm_size + 1) * sizeof(int));

    get_displacement(recvc, recvdisp);

    MPI_Alltoallv(array, sendc, displacement, MPI_INT,
        array, recvc, recvdisp, MPI_INT, MPI_COMM_WORLD);

    /*printf("rank %d array: ", rank);
    for (long long i = 0; i < recvdisp[comm_size]; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
    printf("rank %d sendc: ", rank);
    for (long long i = 0; i < comm_size; ++i) {
        printf("%d ", sendc[i]);
    }
    printf("\n");
    printf("rank %d recvc: ", rank);
    for (long long i = 0; i < comm_size; ++i) {
        printf("%d ", recvc[i]);
    }
    printf("\n");

    printf("rank %d disp: ", rank);
    for (long long i = 0; i < comm_size; ++i) {
        printf("%d ", recvdisp[i]);
    }

    printf("\n");*/
}

/*
 * TODO
 */
void multpivot_partition(int* array, long long length, int* pivots,
    int* displacement, int* sendcount)
{
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    for (int i = 0; i < comm_size; ++i) {
        sendcount[i] = 0;
    }

    int pivot_index;
    pivot_index = 0;

    long long array_index;
    array_index = 0;

    while (array_index < length && pivot_index < comm_size - 1) {
        if (array[array_index] < pivots[pivot_index]) {
            ++(sendcount[pivot_index]);
        } else {
            --array_index;
            ++pivot_index;
        }
        array_index++;
    }

    while (array_index < length) {
        ++(sendcount[pivot_index]);
        ++array_index;
    }

    get_displacement(sendcount, displacement);
}

void get_displacement(int* sendc, int* displacement)
{
    int comm_size;
    MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

    displacement[0] = 0;
    for (int i = 1; i <= comm_size; ++i) {
        displacement[i] = displacement[i - 1] + sendc[i - 1];
    }
}
