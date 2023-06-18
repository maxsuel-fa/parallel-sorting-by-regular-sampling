#ifndef __PSRS_H__
#define __PSRS_H__
void regular_sampling(int*, long long, int, int*);
void psrs(int*, long long, int);
void multpivot_partition(int*, long long, int*,\
    int*, int*, int);
void get_displacement(int*, int*);
void get_boundaries(long long, int, long long*, long long*);
#endif
