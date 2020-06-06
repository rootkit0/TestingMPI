#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const int N = 200;
    int M = 128;
    if(argc > 1) {
        M = atoi(argv[1]);
    }
    
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;

    if(size != 2) {
        printf("Se necesitan 2 tareas para ejecutar el programa!");
        MPI_Finalize();
        exit(0);
    }

    int *message = (int*)malloc(M*sizeof(int));
    for(int i=0; i<M; ++i) {
        message[i] = 0;
    }

    int count = 0;
    int tag1 = 10;
    int tag2 = 20;
    double start_time, stop_time, total_time;
    while(count < N) {
        if (rank == 0) {
            ++count;
            start_time = MPI_Wtime();
            MPI_Send(message, M, MPI_INT, 1, tag1, MPI_COMM_WORLD);
            MPI_Recv(message, M, MPI_INT, 1, tag2, MPI_COMM_WORLD, &status);
            stop_time = MPI_Wtime();
            total_time += stop_time-start_time;
        }
        else if(rank == 1) {
            ++count;
            MPI_Recv(message, M, MPI_INT, 0, tag1, MPI_COMM_WORLD, &status);
            MPI_Send(message, M, MPI_INT, 0, tag2, MPI_COMM_WORLD);
        }
    }

    if(rank == 0) {
        printf("Tiempo total de transmission: %.20f\n", total_time);
        printf("Tiempo medio de transmission/mensaje: %.20f\n", total_time/(N/2));
        int nbytes = N*M*2;
        printf("Bandwidth: %.5f MB/s\n", (nbytes/total_time)/1024);
    }

	free(message);
    
    MPI_Finalize();    
    return 0;
}