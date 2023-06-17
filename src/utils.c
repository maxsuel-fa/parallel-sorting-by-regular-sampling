#include <omp.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

/*
 * TODO
 */
long long min(long long first, long long second)
{
    return (first < second) ? first : second;
}

/*
 * TODO
 */
void random_array(int* array, long long length)
{
    srand(time(NULL));
#pragma omp parallel shared(array, length)
    {
#pragma omp for
        for (long long i = 0; i < length; ++i) {
            array[i] = rand() % length;
        }
    }
}
