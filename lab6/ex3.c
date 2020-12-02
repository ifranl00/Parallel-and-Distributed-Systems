#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
	int n = 5;

		//do {
	
		int rank,nsent,size,source,dest,tag,i,len;
		 char name[20];
		 len=20;
		 MPI_Status status; 
		 MPI_Init(&argc,&argv); //iniatialize MPI execution environment
		 MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
		 MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator
		 MPI_Get_processor_name(name,&len); //gets the name of the processor

		 for(i=0;i<7;i++){
		 	 if(rank==0) {

			 	/*printf("Please enter a number!");
				scanf("%d",&n);
			  	dest=0; 
			  	tag=0;*/
			 
			    MPI_Send(&n,1,MPI_INT,1,tag,MPI_COMM_WORLD); //performs a blocking send -> int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type,int destination_ID, int tag, MPI_Comm comm); 
			    printf("lol\n");
			    MPI_Recv(&n,1,MPI_INT,rank-1,MPI_ANY_TAG,MPI_COMM_WORLD,&status); // Blocking receive for a message -> int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type,int sender_ID, int tag, MPI_Comm comm, MPI_Status *status);
			 	printf("Process %d got %d from process %d\n",rank,n,rank-1); 
			 } else { 
				MPI_Recv(&n,1,MPI_INT,rank-1,MPI_ANY_TAG,MPI_COMM_WORLD,&status); // Blocking receive for a message -> int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type,int sender_ID, int tag, MPI_Comm comm, MPI_Status *status);
				printf("Process %d got %d from process %d\n",rank,n,(rank+1)%size);
				MPI_Send(&n,1,MPI_INT,(rank+1)%size,tag,MPI_COMM_WORLD); //performs a blocking send -> int MPI_Send(void *data_to_send, int send_count, MPI_Datatype send_type,int destination_ID, int tag, MPI_Comm comm); 
			 }
			 /*
			 if(rank==0) {
			 	MPI_Recv(&nsent,1,MPI_INT,rank-1,MPI_ANY_TAG,MPI_COMM_WORLD,&status); // Blocking receive for a message -> int MPI_Recv(void *received_data, int receive_count, MPI_Datatype receive_type,int sender_ID, int tag, MPI_Comm comm, MPI_Status *status);
			  	printf("Process %d got %d from process %d\n",rank,n,rank-1); 

			 }
*/
		 }
		
		 MPI_Finalize(); //Terminates MPI execution environment


	//}while(n>=0);
	
 return(0); 
}