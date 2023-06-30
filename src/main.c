#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/psrs.h"
#include "../include/utils.h"
#include "../include/sorting.h"

#define N_THREADS 3

int main(int argc, char** argv)
{
    int provided;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* input;
    input = (int*)malloc(atoi(argv[1]) * sizeof(int));
    if (!rank) {
        random_array(input, atoi(argv[1]));
    }

    psrs(input, atoi(argv[1]), N_THREADS);
    if (!rank) {
        for (long long i = 0; i < atoi(argv[1]) - 1; ++i) {
            printf("%d, ", input[i]);
        }
        printf("%d.\n", input[atoi(argv[1]) - 1]);
    }

    free(input);
    
    MPI_Finalize();
    return 0;
}
