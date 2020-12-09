#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
	int n = 5;
	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	int rank,size;
		MPI_Status status;
		MPI_Request request;
		MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
		MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator

	do{
		if (rank == 0) { 
			printf("Please enter a number!\n");
			scanf("%d",&n);
			if(n<0) {
				printf("Program finished because you entered a negative number.\n");
				MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			}
		 	printf("Process %d got a %d\n",rank,n);

		}else{
		 	MPI_Irecv(&n,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&request);
		 	MPI_Wait(&request,&status);
			printf("Process %d got %d from process %d\n",rank,n,rank-1);
			//MPI_Wait(&request[rank],&status[rank]);
		}
		MPI_Isend(&n,1,MPI_INT,(rank+1)%size,0,MPI_COMM_WORLD,&request); 
		if(rank==0 ) {
			MPI_Irecv(&n,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&request);
			MPI_Wait(&request,&status);
			printf("Process %d got %d from process %d\n",rank,n,size-1);
		}
	}while(n>=0);
		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}
