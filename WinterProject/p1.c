/*
	PDP WINTER PROJECT: program 1

	1. Design a program to simulate the lift. Passengers come to random floors and if the lift is idle, they
	call for it. When the lift is in motion, the passenger has to wait on his floor, until it becomes idle and
	then he can invoke it. It may happen that the lift will stop on the floor because someone is getting
	off. In such case it can take passengers, who are going in the same direction as the lift. The lift is
	idle on the floor where all the passengers leaves it and no one is waiting for it. The program should
	be made with the use of MPI.

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> 
#include <string.h>
#include "mpi.h" 
 
typedef struct {
	int elevatorFloor;
	int elevatorFree;
	int passenger;
	char requests[20];
} Data;


int main(int argc, char **argv) 
{ 
	char name[20];
	char temp[50] = {0};
	char temp2[50] = {0};
	int len,rank,size,elevatorFloor,i,j;
	len=20;
	i = 0;
	j = 0;
	MPI_Datatype new_type;
	MPI_Datatype type[4] = { MPI_INT, MPI_INT, MPI_INT, MPI_CHAR};
	int blen[4] = { 1,1,1,20};
	MPI_Aint disp[4];
	MPI_Aint base, addr;
	Data tabrecord;

printf("size: %d\n",size);

	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	MPI_Status status; 
	MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
	MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator
	MPI_Get_processor_name(name,&len); //gets the name of the processor

	// Each passenguer is in a random initial floor before taking the lift
		int initFloor[size];

			MPI_Get_address(&tabrecord, &base);
			MPI_Get_address(&(tabrecord.elevatorFloor), &addr);
			disp[0] = addr - base;
			MPI_Get_address(&(tabrecord.elevatorFree), &addr);
			disp[1] = addr - base;
			MPI_Get_address(&(tabrecord.passenger), &addr);
			disp[2] = addr - base;
			MPI_Get_address(&(tabrecord.passenger), &addr);
			disp[3] = addr - base;
			
			MPI_Type_create_struct(4, blen, disp, type, &new_type);
			MPI_Type_commit(&new_type);

		srand (time(NULL) + rank); //diferent seed for each process
		initFloor[rank] = (rand() % (size + 1)); //floors between the number of process and 0
		printf("Passenger %d INITIAL FLOOR -> %d.\n",rank,initFloor[rank]);
		MPI_Barrier(MPI_COMM_WORLD); //Blocks until all processes in the communicator have reached this routine. 

	// Each passenguer will have a random destination floor
		int destFloor[size];
		srand (time(NULL) + rank + 1); //diferent seed for each process
		destFloor[rank] = (rand() % (size + 1)); //floors between the number of process and 0
		printf("Passenger %d DESTINATION FLOOR -> %d.\n",rank,destFloor[rank]);
		tabrecord.elevatorFloor = 0;
		tabrecord.elevatorFree = 0;
		tabrecord.passenger = -1;
		tabrecord.requests[20] = "0";


		MPI_Barrier(MPI_COMM_WORLD); //Blocks until all processes in the communicator have reached this routine. 

	// The elevator is avalable to use and there are requests for it

		//MPI_Pack(&rank,1,MPI_INT,temp,50, 0, MPI_COMM_WORLD);
		//MPI_Send(temp,0,MPI_PACKED,1,50,MPI_COMM_WORLD);

		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}