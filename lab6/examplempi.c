#include <stdlib.h>
#include <stdio.h>
#include "mpi.h" 
 
int main(int argc, char **argv) 
{ 
 int rank,ranksent,size,source,dest,tag,i,len;
 char name[20];
 len=20;
 MPI_Status status; 
 MPI_Init(&argc,&argv); //iniatialize MPI execution environment
 MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
 MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator
 MPI_Get_processor_name(name,&len); //gets the name of the processor

 if(rank==0) 
 { 
  dest=0; 
  tag=0;
  for(i=1;i<size;i++) 
    MPI_Send(&rank,1,MPI_INT,i,tag,MPI_COMM_WORLD); //performs a blocking send
 } 
 else 
 { 
  MPI_Recv(&ranksent,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD,&status); // Blocking receive for a message
  printf("Data to process %d recieved from %d on %s\n",rank,status.MPI_SOURCE,name); 

 } 
 MPI_Finalize(); //Terminates MPI execution environment
 return(0); 
}