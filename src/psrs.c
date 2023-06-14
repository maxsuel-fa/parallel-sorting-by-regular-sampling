#include "../include/sorting.h"
#include "../include/psrs.h"

/*
 * TODO
 */
void psrs(int* array, long long length, int n_threads)
{
    long long subarray_len;
    subarray_len = (length % n_threads)\
                   ? length / n_threads + 1\
                   : length / n_threads;

#pragma omp parallel shared(array, length, subarray_len) n_threads(n_threads)
    {
        int thread_id = omp_get_thread_num();
        long long low, high;

        low = thread_id * subarray_len;
        high = (thread_id + 1) * subarray_len - 1;
        if (high > length - 1) {
            high = length - 1;
        }

        quicksort(array, low, high);
    }
}
