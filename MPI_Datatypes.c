#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Particula {
    float x;
    float y;
    float massa;
    char nombre[50];
} part;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    //Check exactly 2 tasks
    if(size != 2) {
        printf("Este programa se ha de ejecutar con 2 tareas.");
        return 0;
    }
    //Check parameters
    int M;
    if(argc > 1) {
        M = atoi(argv[1]);
    }
    else {
        if(rank == 0) {
            printf("Introducir la dimension de la matriz cuadrada\n");
            return 0;
        }
    }
    //Matrix
    MPI_Datatype mpi_matrix;
    MPI_Type_vector(M, 1, M, MPI_INT, &mpi_matrix);
    MPI_Type_commit(&mpi_matrix);

    //Struct
    const int nitems = 4;
    int blocklenghts[4] = {1, 1, 1, 50};
    MPI_Datatype types[4] = {MPI_FLOAT, MPI_FLOAT, MPI_FLOAT, MPI_CHAR};
    MPI_Aint offsets[4];
    offsets[0] = offsetof(part, x);
    offsets[1] = offsetof(part, y);
    offsets[2] = offsetof(part, massa);
    offsets[3] = offsetof(part, nombre);
    MPI_Datatype mpi_particula;
    MPI_Type_create_struct(nitems, blocklenghts, offsets, types, &mpi_particula);
    MPI_Type_commit(&mpi_particula);

    //MATRIX SAVED ON mpi_matrix, STRUCT SAVED ON mpi_particula
    //Send datatypes between tasks
    int tag1 = 50; //Tag struct
    int tag2 = 60; //Tag matrix
    if(rank == 0) {
        part send_struct = {1.0, 1.0, 2.0, "Particula1"};
        int *send_matrix = (int*)malloc(M*M*sizeof(int));
        for(int i=0; i<M*M; ++i) {
            send_matrix[i] = 1;
        }
        MPI_Send(&send_struct, 1, mpi_particula, 1, 50, MPI_COMM_WORLD);
        MPI_Send(&send_matrix, 1, mpi_matrix, 1, 60, MPI_COMM_WORLD);
        printf("P:[%d] Printando estructura enviada x: %f, y: %f, massa: %f, nombre: %s\n", rank, send_struct.x, send_struct.y, send_struct.massa, send_struct.nombre);
        printf("P:[%d] Numero elementos matriz enviada: %ld\n", rank, sizeof(send_matrix));
    }
    else if(rank == 1) {
        part recv_struct;
        int *recv_matrix;
        MPI_Recv(&recv_struct, 1, mpi_particula, 0, 50, MPI_COMM_WORLD, &status);
        MPI_Recv(&recv_matrix, 1, mpi_matrix, 0, 60, MPI_COMM_WORLD, &status);
        printf("P:[%d] Printando estructura recibida x: %f, y: %f, massa: %f, nombre: %s\n", rank, recv_struct.x, recv_struct.y, recv_struct.massa, recv_struct.nombre);
        printf("P:[%d] Numero elementos matriz recibida: %ld\n", rank, sizeof(recv_matrix));
    }

    MPI_Finalize();
    return 0;
}