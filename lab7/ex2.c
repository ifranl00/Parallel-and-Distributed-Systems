#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
	char name[20];
	int n,len;
	len=20;
	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	do {
	
	
		int rank,size;
		MPI_Status status; 
		MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
		MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator
		MPI_Get_processor_name(name,&len); //gets the name of the processor

		if (rank == 0) { 

			printf("Please enter a number!\n");
			scanf("%d",&n);
			if(n<0) {
				printf("Program finished because you entered a negative number.\n");
				MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			}
		}
		//Broadcasts a message from the process with rank "root" to all other processes of the communicator 
		//int MPI_Bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm)
		MPI_Bcast(&n, 1, MPI_INT,0, MPI_COMM_WORLD);
		printf("Process %d got a %d on %s\n",rank,n,name);
	}while(n>=0);
			
		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}