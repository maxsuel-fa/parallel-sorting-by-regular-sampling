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

int* random_array(long long length)
{
    int* array;
    array = (int*) malloc(length * sizeof(int));
    srand(time(NULL));

#pragma omp parallel shared(length)
    {
#pragma omp for 
        for (long long i = 0; i < length; ++i) {
            array[i] = rand() % length;
        } 
    }

    return array;
}
