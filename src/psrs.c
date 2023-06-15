#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/psrs.h"
#include "../include/sorting.h"
#include "../include/utils.h"

/*
 * TODO
 */
void psrs(int* array, long long length, int n_threads)
{
    int* samples;
    samples = (int*) malloc(n_threads * n_threads * sizeof(int));

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
}
