#include <stdlib.h>
#include <time.h>
#include "../include/sorting.h"

/*
 * TODO
 */
void swap(int* first, int* second)
{
    int temp = *first;
    *first =  *second;
    *second = temp;
}

/*
 * @brief   Function to partition the array based on a randomly selected pivot.
 * @param   array   The array to be partitioned.
 * @param   low     The starting index of the partition.
 * @param   high    The ending index of the partition.
 * @return  The index of the pivot element after partitioning.
 */
long long partition(int* array, long long low, long long high)
{
    // Selecting a random pivot
    srand(time(NULL));
    long long random_index = low + rand() % (high - low + 1);
    long long pivot = array[random_index];

    // Swapping the pivot with the last element
    swap(&array[high], &array[random_index]);

    long long i = low - 1;

    for (long long j = low; j < high; ++j) {
        if (array[j] <= pivot) {
            ++i;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);

    return i + 1;
}

/*
 * @brief   Quicksort function to sort the given array.
 * @param   array   The array to be sorted.
 * @param   low     The starting index of the array.
 * @param   high    The ending index of the array.
 */
void quicksort(int* array, long long low, long long high)
{
    if (low < high) {
        // Partitioning the array and obtaining the pivot index
        long long pivot_index = partition(array, low, high);

        // Recursively calling quicksort on sub-arrays
        quicksort(array, low, pivot_index - 1);
        quicksort(array, pivot_index + 1, high);
    }
}
