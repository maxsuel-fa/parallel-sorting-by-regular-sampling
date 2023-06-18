#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/psrs.h"
#include "../include/utils.h"

#define N_THREADS 3

int main(int argc, char** argv)
{
    int provided;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* input;
    input = (int*)malloc(atoi(argv[1]) * sizeof(int));
    double init_time;
    if (!rank) {
        random_array(input, atoi(argv[1]));
        init_time = MPI_Wtime();
    }
    psrs(input, atoi(argv[1]), N_THREADS);
    if (!rank) {
        printf("time: %lf\n", MPI_Wtime() - init_time);
        /*for (long long i = 0; i < atoi(argv[1]); ++i) {
            printf("%d ", input[i]);
        }*/
    }

    MPI_Finalize();
    return 0;
}
