#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/psrs.h"
#include "../include/utils.h"

#define N_THREADS 3

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    int* input;
    input = (int*)malloc(atoi(argv[1]) * sizeof(int));

    double init_time;
    if (!rank) {
        random_array(input, atoi(argv[1]));
        init_time = MPI_Wtime();
    }

    psrs(input, atoi(argv[1]), N_THREADS);

    if (!rank) {
        //for (long long i = 0; i < atoi(argv[1]); ++i) {
            printf("%lf\n", MPI_Wtime() - init_time);
        //}
    }

    MPI_Finalize();
    return 0;
}
