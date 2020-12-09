#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
	int n = -1;
	int c = -1;
	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	int rank,size;
		MPI_Status status[size];
		MPI_Request request[size];
		MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
		MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator


	do {
		c = c++;
		if (rank == 0) { 

			printf("Please enter a number!\n");
			scanf("%d",&n);
			if(n<=0) {
				return(-1);
			}
		 	printf("Process %d got a %d\n",rank,n);

		}else if(n >= 0){

		 	MPI_Irecv(&n,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&request[rank]); 
			printf("Process %d got %d from process %d\n",rank,n,rank-1);
		}

		if(n >=0){

			MPI_Isend(&n,1,MPI_INT,(rank+1)%size,0,MPI_COMM_WORLD,&request[rank]); 
			MPI_Wait(&request[rank],&status[rank]);
		}

		if(rank==0 && n>=0) {
		
			MPI_Irecv(&n,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&request[rank]); 
		}
	}while(n>=0);
		//MPI_Waitall(size,&request,&status);
		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}
