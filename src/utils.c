#include <omp.h>
#include <stdlib.h>
#include <time.h>

#include "../include/utils.h"

/*
 * @brief Computes the minimum value between two numbers.
 *
 * @param first The first number.
 * @param second The second number.
 * @return The minimum value between first and second.
 */
long long min(long long first, long long second)
{
    return (first < second) ? first : second;
}

/*
 * @brief Fills an array with random values.
 *
 * @param array The array to be filled.
 * @param length The length of the array.
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
