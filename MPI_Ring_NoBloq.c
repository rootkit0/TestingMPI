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

    int *message = (int*)malloc(M*sizeof(int));
    for(int i=0; i<M; ++i) {
        message[i] = 0;
    }
    int count = 0;
    int source = 0;
    int dest = 0;
    double start_time, stop_time, total_time;
    MPI_Request request;
    while(count < N) {
        if(rank == 0) {
            ++count;
            source = size-1;
            dest = 1;
            start_time = MPI_Wtime();
            MPI_Isend(message, M, MPI_INT, dest, 0, MPI_COMM_WORLD, &request);
            MPI_Irecv(message, M, MPI_INT, source, 0, MPI_COMM_WORLD, &request);
            stop_time = MPI_Wtime();
            total_time += stop_time-start_time;
        }
        else {
            ++count;
            source = rank-1;
            dest = ((rank+1)%size);
            MPI_Irecv(message, M, MPI_INT, source, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(message, M, MPI_INT, dest, 0, MPI_COMM_WORLD, &request);
        }
    }

    MPI_Wait(&request, &status);

    if(rank == 0) {
        printf("Tiempo total de transmission: %.20f\n", total_time);
        printf("Tiempo medio de transmission/mensaje: %.20f\n", total_time/(N/2));
        int nbytes = N*M;
        printf("Bandwidth: %.5f MB/s\n", (nbytes/total_time)/1024);
    }
    
	free(message);

    MPI_Finalize();
    return 0;
}