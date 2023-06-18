#ifndef __SORTING_H__
#define __SORTING_H__

void swap(int*, int*);
long long partition(int*, long long, long long);
void quicksort(int*, long long, long long);

void merge(int*,
    int*, long long, long long,
    int*, long long, long long);

void merge_sort(int*, long long, long long);
#endif
