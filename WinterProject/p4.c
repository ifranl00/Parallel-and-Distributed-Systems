/*
	
	PDP WINTER PROJECT: program 4

	Euler gamma constant is defined as the limit of a sequence g n where:
	Write a concurrent program that calculates g n , with the following assumptions:
		- N - the number of elements of the sum is loaded from the keyboard
		- P - number of processes, which will compute the sum is a constant in a program
	Each process calculate his own fragment of the sum - for example, for n = 100, p = 10, the first
	process computes elements 1 to 10, the second from 11 to 20, etc., at the end the partial sums are
	added and logarithm is subtracted. Note: n may not be divisible by p. The program can be made
	using any familliar technique .

*/


#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <pthread.h>
#include <math.h>

/* define the number of threads to create */
#define WAIT 1000000
#define NUM_THREADS	2// number of procceses 


/* define structure of thread's data */

struct arg_struct {
	int id; //id of the thread
	int size; // size of the part of work that must be computed by ecah thread
	int iterator; //iterator updated
};
/* Function declarations */

void* my_pthread_function(void *ptr);
float *vec1;
int idOdd; // to control if the num of sum introduced by keyborad is disible by the number of threads

/* Begin of the Main thread */
int main()
{
	int i, thr,x;
	struct arg_struct *args;
	float result = 0.0;
	idOdd = -1;

	// Ask the number of intervals
	printf("Please entet the number of elements of the sum!\n");
	scanf("%d",&x); 

	pthread_t thread_array[NUM_THREADS];
	vec1 = malloc(sizeof(float)*x);

	for( i = 0; i < NUM_THREADS; i++ ) // Creation of all the threads
	{
		args = malloc(sizeof(struct arg_struct));
		(*args).id=i;
		if(x%2 != 0) { //if is not divisible
			idOdd = 1;
			(*args).size=(x+1)/NUM_THREADS;
			(*args).iterator=i*((x+1)/NUM_THREADS);
		}else{

			(*args).size=x/NUM_THREADS;
			(*args).iterator=i*(x/NUM_THREADS);
	}
		thr = pthread_create( &thread_array[i], NULL, my_pthread_function, (void *)args );
		
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
	}

	/* Wait till threads are complete before main continues. Unless we  */
     	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	for( i = 0; i < NUM_THREADS; i++ ) {

		pthread_join( thread_array[i], NULL);
	}

    
	for( i = 0; i<x; i++) {
		result = result + vec1[i];
	}
	// so in result we habe the armonic number given that number of summatories

	printf("TOTAL Sumatory: %lf \n", result);
	printf(" Approximate Euler gamma constant: %lf \n",result - log(x)); // It will be more accurate the higher the value of sums entered
	return EXIT_SUCCESS;    
}


/* FUnction definitions */
void* my_pthread_function(void *args )
{
	struct arg_struct *myargs = (struct arg_struct*)args;
	int i,id, size, iterator;

	id= (*myargs).id;
	size= (*myargs).size;
	iterator= (*myargs).iterator;

	free (args);
	if (idOdd == id){ // if x entered by keyboard is not divisible by the number of threads

		for(i=iterator;i<(iterator+size-1);i++){ // the last thread will do one computation less
			vec1[i] = 1.0/(i+1.0); // 1/k calculation
		}
	}else{
		
		for(i=iterator;i<(iterator+size);i++){
			vec1[i] = 1.0/(i+1.0); // 1/k calculation
		}
	}
	//busy waiting
	while(i<WAIT) i++;
}

