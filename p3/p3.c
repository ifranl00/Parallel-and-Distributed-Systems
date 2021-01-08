/*
	
	PDP WINTER PROJECT: program 3

	3. Write a program that calculates the value of the expression using the Mclaurin series. Compare the
	obtained value with the value from the math library. Measure the time of execution of the program
	for the different number of threads. The program should be made with the use of MPI or Pthreads.

*/

#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <pthread.h>
#include <time.h>
#include <tmeas.h>
#include <math.h>

/* define the number of threads to create */
#define WAIT 1000000
#define NUM_THREADS	6// 6 threads may be needed to divide the work of calculating mclaurin serie
float x,result,d,s,j;
pthread_mutex_t mutex;
/* Function declarations */

void* my_pthread_function();


/* Begin of the Main thread */
int main()
{
	float time = 0.0;
	result = 1.0;
	s = 1.0; // dividend of each term of the serie will be calculated and added to s and the first one is 1
	d = 1.0; // divisor of each term (n!)
	j = 0.0; // index to calculate the divisor of each term
	int i, thr;


	// Ask the number of subintervals by console
	printf("Please enter the value of x to obtain the value of e to the power of x!\n");
	scanf("%f",&x); // Number of intervals will be saved in the int variable named n


	tstart(); // Start to measure the time 
	pthread_t thread_array[NUM_THREADS];

	for( i = 0; i < NUM_THREADS; i++ ) // Creation of all the threads
	{
		thr = pthread_create( &thread_array[i], NULL, my_pthread_function, (void *)i );
		
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

    printf("\nApproximate Result using Mclaurin serie: %f\n",result);
	printf("Result using math.h: %lf\n",exp(x));
	time = tstop();
	printf("Execution time: %lf\n",time);
	return EXIT_SUCCESS;    
}


/* FUnction definitions */
void* my_pthread_function()
{
	int i;

	pthread_mutex_lock(&mutex); //to protect the global variables to be accesed at the same time
	d = d*(j+1); //calculation of the divisor of ecah term (n!)
	s = (s*x); //dividend of each term
	result = result + (s/d); // cummulate summatory
	j = j +1 ; // to increment the index to calculate the factorial
	pthread_mutex_unlock(&mutex);
	//busy waiting
	while(i<WAIT) i++;
}

