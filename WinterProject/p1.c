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
} Data;

/* functions declaration */

int isArrayFull(int array[], int n);
void initializeToXInt(int array[],int n,int value);
void initializeToXChar(char array[],int n,char value);

int main(int argc, char **argv) 
{ 
	char name[20];
	int len,rank,size,elevatorFloor,i,j;
	char buffer[110];
    int position = 0;
	len=20;
	i = 0;
	j = 0;
	MPI_Datatype new_type;
	MPI_Datatype type[3] = { MPI_INT, MPI_INT, MPI_INT};
	int blen[3] = { 1,1,1};
	MPI_Aint disp[3];
	MPI_Aint base, addr;
	Data tabrecord,tabrecieved;


	MPI_Init(&argc,&argv); //iniatialize MPI execution environment
	MPI_Status status; 
	MPI_Comm_rank(MPI_COMM_WORLD,&rank); //determines the rank of the calling process in the communicator
	MPI_Comm_size(MPI_COMM_WORLD,&size); //determines the size of the group associated with a communicator
	MPI_Get_processor_name(name,&len); //gets the name of the processor


		int passenger = -1; //passenger using the lift
		int offPassengers[size]; // array where the passenguers will saved when they are not longuer using the lift
	// Each passenguer is in a random initial floor before taking the lift
		int initFloor[size];

			MPI_Get_address(&tabrecord, &base);
			MPI_Get_address(&(tabrecord.elevatorFloor), &addr);
			disp[0] = addr - base;
			MPI_Get_address(&(tabrecord.elevatorFree), &addr);
			disp[1] = addr - base;
			MPI_Get_address(&(tabrecord.passenger), &addr);
			disp[2] = addr - base;
	
			MPI_Type_create_struct(3, blen, disp, type, &new_type);
			MPI_Type_commit(&new_type);

		srand (time(NULL) + rank); //diferent seed for each process
		initFloor[rank] = (rand() % (size + 1)); //floors between the number of process and 0
		printf("Passenger %d INITIAL FLOOR -> %d.\n",rank,initFloor[rank]);
		MPI_Barrier(MPI_COMM_WORLD); //Blocks until all processes in the communicator have reached this routine. 

	// Each passenguer will have a random destination floor
		int destFloor[size];
		initializeToXInt(offPassengers,size,-1);
		initializeToXChar(buffer,110,' ');
		srand (time(NULL) + rank + 1); //diferent seed for each process
		destFloor[rank] = (rand() % (size + 1)); //floors between the number of process and 0
		printf("Passenger %d DESTINATION FLOOR -> %d.\n",rank,destFloor[rank]);
		tabrecord.elevatorFloor = 0;
		tabrecord.elevatorFree = 0;
		tabrecord.passenger = -1;

		MPI_Barrier(MPI_COMM_WORLD); //Blocks until all processes in the communicator have reached this routine. 

	// The elevator is avalable to use and there are requests for it
/* MPI_PACK() AND MPI_UNPACK() packs/unpacks data into a contiguous buffer before sending it, and unpacks it from a contiguous buffer after receiving it. */
/* 
    MPI_PACK(inbuf, incount, datatype, outbuf, outsize, position, comm)
    MPI_UNPACK(inbuf, insize, position, outbuf, outcount, datatype, comm)
*/


		while(isArrayFull(offPassengers,size) == 1 && offPassengers[rank] == -1) { //while there is passenguers that want to use the lift

			printf("In process %d entre al while\n",rank);
			// 1. Who is going to use the lift? The fist to call for it if it is idle
			if(passenger == -1) { // if the lift is idle
				passenger = rank; // we save the passenguer who asked first
			}


			if(rank != 0 ){ // only executed by the passenguer who asked first for the lift
				printf("HEYYYYY\n");
				tabrecieved.elevatorFloor = 7;
				tabrecieved.elevatorFree = 1;
				tabrecieved.passenger = rank;
		        printf("In process %d the floor is %d, lift state is %d, passenguer is %d \n",rank,tabrecieved.elevatorFloor,tabrecieved.elevatorFree,tabrecieved.passenger); 

		        MPI_Recv(buffer, 110, MPI_PACKED, 0, 110, MPI_COMM_WORLD, &status);
		        MPI_Unpack(buffer, 110, &position, &tabrecieved, 1, new_type, MPI_COMM_WORLD);

		        printf("In process %d I have received all the struct:\n",rank);
		        printf("\t - name: %d\n",tabrecieved.elevatorFloor);
		        printf("\t - age: %d\n",tabrecieved.elevatorFree);
		        printf("\t - city: %d\n",tabrecieved.passenger );
			}else {
				

				printf(" I am the passenguer %d in floor %d and I am using the lift to go to %d floor\n", rank, initFloor[rank],destFloor[rank]);

				tabrecord.elevatorFloor = rank;
				tabrecord.elevatorFree = rank;
				tabrecord.passenger = rank;
				initializeToXChar(buffer,110,' '); // reset the buffer
				MPI_Pack(&tabrecord, 1, new_type, buffer, 110, &position, MPI_COMM_WORLD);
        		MPI_Send(buffer, position, MPI_PACKED, 1, 110, MPI_COMM_WORLD);
        		sleep((destFloor[rank]-initFloor[rank])*2); //time using the lift 2 sec per floor
        		offPassengers[rank] = rank; // the passenguer is not longuer using the lift
				passenger == -1;
		    	printf("In process %d the lift is idle!\n",rank);

			}

		}

		MPI_Finalize(); //Terminates MPI execution environment
	
 return(0); 
}


/* Functions definition */


/* Returns 0 if is full the array or 1 if is not full */
int isArrayFull(int array[], int n) {

	int empty = 0;
	for (int i = 0; i < n; i++)
	{
		if(array[i] == -1) { // if there is an element empty
			empty = 1; 
		}
	}
	return empty;

}

/* Initialize the int array received to the value received */

void initializeToXInt(int array[],int n,int value){

	for (int i = 0; i < n; i++)
	{
		array[i] = value;
	}
}

/* Initialize the char array received to the value received */

void initializeToXChar(char array[],int n,char value){

	for (int i = 0; i < n; i++)
	{
		array[i] = value;
	}
}
