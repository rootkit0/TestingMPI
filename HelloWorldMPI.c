#include "mpi.h" 
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char **argv ) { 
	int rank, size, len;
    pid_t process_id = getpid();
    char name[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Init( &argc, &argv ); 
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
    MPI_Get_processor_name(name, &len);

    if(rank == 0) {
        printf("La aplicacion paralela va a ejecutar %d procesos\n", size);
    }
	printf("Hola Mundo Paralelo!\n");
    printf("Ejecutable: %s, PID: %d, Rango (Proceso numero): %d, Ejecutando en: %s\n", argv[0], process_id, rank, name);
	
    MPI_Finalize(); 
	return 0; 
}