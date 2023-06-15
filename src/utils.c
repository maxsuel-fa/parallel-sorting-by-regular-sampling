#include <omp.h>
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

#pragma omp parallel shared(length)
    {
#pragma for 
        for (long long i = 0; i < length; ++i) {
            array[i] = rand() % length;
        } 
    }

    return array;
}
