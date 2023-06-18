#include "../include/sorting.h"
#include <stdlib.h>
#include <time.h>

/*
 * TODO
 */
void swap(int* first, int* second)
{
    int temp = *first;
    *first = *second;
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

/**
 * @brief Merge two sorted subarrays into a single sorted subarray.
 *
 * @param arr The main array containing elements from both subarrays.
 * @param left The left subarray.
 * @param left_start The starting index of the left subarray.
 * @param left_end The ending index of the left subarray.
 * @param right The right subarray.
 * @param right_start The starting index of the right subarray.
 * @param right_end The ending index of the right subarray.
 */
void merge(int* array,
    int* left, long long left_start, long long left_end,
    int* right, long long right_start, long long right_end)
{
    long long i = left_start, j = right_start, k = 0;
    long long merged_size = (left_end - left_start) + (right_end - right_start) + 2;
    int* merged;
    merged = (int*)malloc(merged_size * sizeof(int));

    // Merge elements from both subarrays into the merged array in sorted order
    while (i <= left_end && j <= right_end) {
        if (left[i] <= right[j]) {
            merged[k++] = left[i++];
        } else {
            merged[k++] = right[j++];
        }
    }

    // Copy any remaining elements of the left subarray to the merged array
    while (i <= left_end) {
        merged[k++] = left[i++];
    }

    // Copy any remaining elements of the right subarray to the merged array
    while (j <= right_end) {
        merged[k++] = right[j++];
    }

    // Copy the merged array back to the main array
    for (long long m = 0; m < k; ++m) {
        array[left_start + m] = merged[m];
    }
}

/*
 * @brief Perform Merge Sort on an array.
 * @param array The array to be sorted.
 * @param start The starting index of the array.
 * @param end The ending index of the array.
 */
void merge_sort(int* array, long long start, long long end)
{
    if (start < end) {
        int mid = start + (end - start) / 2;

        // Recursively sort the left and right halves of the array
        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);
        
        // Merge the sorted left and right halves
        merge(array, array, start, mid, array, mid + 1, end);
    }
}
