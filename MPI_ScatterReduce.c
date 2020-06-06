#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int compute_plus(int *array, int size) {
    int sum = 0;
    for(int i=0; i<size; ++i) {
        sum += array[i];
    }
    return sum;
}

int main(int argc, char** argv) {
    const int N = 6;
    const int M = 10;

    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(rank == 0) {
        if(size != N) {
            printf("Este programa se ha de ejecutar con 6 tareas.");
            return 0;
        }
    }

    int *matrix = NULL;
    if (rank == 0) {
        matrix = (int*)malloc(N*M*sizeof(int));
        for(int i=0; i<N*M; ++i) {
            matrix[i] = 1;
        }
    }
    int *sub_matrix = (int*)malloc(M*sizeof(int));

    MPI_Scatter(matrix, M, MPI_INT, sub_matrix, M, MPI_INT, 0, MPI_COMM_WORLD);

    int suma = compute_plus(sub_matrix, M);
    int *get_sums = (int*)malloc(N*sizeof(int));

    MPI_Gather(&suma, 1, MPI_INT, get_sums, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_sum = compute_plus(get_sums, N);
        printf("Suma total: %d\n", total_sum);

        free(matrix);
        free(get_sums);
    }
    free(sub_matrix);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}