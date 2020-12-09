#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
	int n;
	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	do {
	
	
		int rank,size,i;
		MPI_Status status; 
		MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
		MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator


		if (rank == 0) { 

			printf("Please enter a number!\n");
			scanf("%d",&n);
			if(n<0) {
				printf("Program finished because you entered a negative number.\n");
				MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
			}
		 	printf("Process %d got a %d\n",rank,n);

		}else {

		 	MPI_Recv(&n,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status); // Blocking receive for a message -> int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type,int sender_ID, int tag, MPI_Comm comm, MPI_Status *status);
			printf("Process %d got %d from process %d\n",rank,n,rank-1);
		}

		MPI_Send(&n,1,MPI_INT,(rank+1)%size,0,MPI_COMM_WORLD); //performs a blocking send -> int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type,int destination_ID, int tag, MPI_Comm comm); 

	
		if(rank==0) {
		
			MPI_Recv(&n,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status); // Blocking receive for a message -> int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type,int sender_ID, int tag, MPI_Comm comm, MPI_Status *status);
			printf("Process %d got %d from process %d\n",rank,n,size-1);
		}

	}while(n>=0);
			
		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}