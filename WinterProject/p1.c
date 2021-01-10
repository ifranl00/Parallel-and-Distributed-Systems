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
void initializeToI(int array[],int n);
void initializeToXChar(char array[],int n,char value);
void getRandomRequests(int array[], int n);

int main(int argc, char **argv) 
{ 
	char name[20];
	int len,rank,size,elevatorFloor,i,j,numPassengers;
	char buffer[1000];
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


		int passenger = -1; //passenger who called first
		int currentPassenger = -1; // passenguer usin the lift
		int offPassengers[size-1]; // array where the passenguers will saved when they are not longuer using the lift
		int randomRequest[size-1]; // every time the lift is idle the first passenguer to ask for it is saved 
		numPassengers = size -1; // all the threads except the lift who is thread 0
	// Each passenguer and the lift is in a random initial floor before taking the lift
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

		if(rank == 0) {

			printf("Lift (process %d) INITIAL FLOOR -> %d.\n",rank,initFloor[rank]);

		}else{
			printf("Passenger %d INITIAL FLOOR -> %d.\n",rank,initFloor[rank]);

		}
		MPI_Barrier(MPI_COMM_WORLD); //Blocks until all processes in the communicator have reached this routine. 

	
		int destFloor[size-1];// Each passenguer will have a random destination floor

		if(rank == 0) {

			initializeToXInt(offPassengers,size-1,-1);
			initializeToXChar(buffer,110,' ');
			initializeToI(randomRequest,size-1);

			getRandomRequests(randomRequest,size-1);
			for (int i = 0; i < size-1; ++i)
			{
				printf("Request %d passenger %d\n",i+1,randomRequest[i]);
			}

		}
		
		srand (time(NULL) + rank + 1); //diferent seed for each process
		if(rank != 0){ // the lift wont have a random destination floor
			destFloor[rank-1] = (rand() % (10 + 1)); //floors between 10 and 0
			printf("Passenger %d DESTINATION FLOOR -> %d.\n",rank,destFloor[rank-1]);
		}
		
		// initialization of tabrecord
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

		
		while(isArrayFull(offPassengers,size-1) == 1 && offPassengers[rank-1] == -1 ) { //while there is passenguers that want to use the lift

			// 1. Who is going to use the lift? The fist to call for it if it is idle
			if(rank == 0){ // the lift

				initializeToXChar(buffer,110,' '); // reset the buffer

				// Which passanguer I have to pick up?
				passenger = randomRequest[i];
				i = i +1;
				printf(" I am the lift (process %d) in floor %d and passenguer %d is going to be picked up\n", rank, initFloor[rank],passenger);
				//printf("Destination floor of passenguer %d: %d", passenger,destFloor[passenger]);
				tabrecord.elevatorFloor = destFloor[passenger-1];
				tabrecord.elevatorFree = rank;
				tabrecord.passenger = passenger;
				
				MPI_Pack(&tabrecord, 1, new_type, buffer, 1000, &position, MPI_COMM_WORLD);


				for (int i = 0; i < size-1; i++)
				{
					if(offPassengers[i] != -1) { // a passenguer has already ysed the lift
						numPassengers = numPassengers - 1; // is not going to use the lift again per execution
					}
				}
				for(i=1;i<numPassengers;i++) {
					MPI_Send(&buffer,0,MPI_PACKED,i,1000,MPI_COMM_WORLD); //performs a blocking send

				}
        		sleep((destFloor[passenger-1]-initFloor[rank])*2); //time using the lift 2 sec per floor
        		offPassengers[passenger-1] = passenger; // the passenguer is not longuer using the lift
				printf(" I am the lift (process %d) in floor %d and passenguer %d has reached floor %d\n", rank, initFloor[rank],passenger,destFloor[passenger-1]);
				passenger == -1;
			}else {
				MPI_Recv(buffer,1000,MPI_PACKED,0,1000,MPI_COMM_WORLD,&status); // Blocking receive for a message
 				MPI_Unpack(buffer, 1000, &position, &tabrecieved, 1, new_type, MPI_COMM_WORLD);
				
				if(rank != tabrecieved.passenger) {
					printf("Passenger %d is waiting for the lift:\n",rank);
		        	printf("\t - Elevantor floor: %d\n",tabrecieved.elevatorFloor);
		        	printf("\t - Free: %d\n",tabrecieved.elevatorFree);
		        	printf("\t - Passenger using the floor: %d\n",tabrecieved.passenger );			}
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

/* Initialize the int array received to ordered values */

void initializeToI(int array[],int n){

	for (int i = 0; i < n; i++)
	{
		array[i] = i+1;
	}
}
/* Initialize the char array received to the value received */

void initializeToXChar(char array[],int n,char value){

	for (int i = 0; i < n; i++)
	{
		array[i] = value;
	}
}

/* returns random generated vector shuffled */
void getRandomRequests(int array[], int n)
{
	int i,j,t;
    if (n > 1) 
    {
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
         j = i + rand() / ( RAND_MAX/ (n - i) + 1);
          t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}