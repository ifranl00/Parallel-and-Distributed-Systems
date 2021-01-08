#include <stdio.h>		/* need for fflush() */
#include <stdlib.h>		/* need for exit() */
#include <pthread.h>
#include <time.h>
#include <tmeas.h>
#include <math.h>

/* define the number of threads to create */
#define WAIT 1000000
float h; // The leght of each interval
float x[100] = {};
float y[100] = {};

/* Function declarations */

void* my_pthread_function( void *ptr );
float integration(float x);


/* Begin of the Main thread */
int main()
{
	double time = 0.0;
	int i, thr,n;
	float sumEvenNums = 0.0;
	float sumOddNums = 0.0;

	// Ask the number of subintervals by console
	printf("Please enter the number of subintervals of integration!\n");
	scanf("%d",&n); // Number of intervals will be saved in the int variable named n
	tstart(); // Start to measure the time 
	pthread_t thread_array[n];

	h = (1.0-0)/n; //trapezoidal rule given the domain of integration between 1 and 0

	for( i = 0; i < n; i++ ) // Creation of all the threads
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

	for( i = 0; i < n; i++ ) {

		pthread_join( thread_array[i], NULL);
	}


	for(i=1; i<n; i++)
    {
        if(i%2==1)
        {
            sumOddNums=sumOddNums+y[i];
        }
        else{
            sumEvenNums=sumEvenNums+y[i];
        }
    }

	float result = 4.0*(h/3.0*(y[0]+y[n]+4.0*sumOddNums+2.0*sumEvenNums));
    printf("\nApproximate result: %f\n",result);
	time = tstop();
	printf("Execution time: %lf\n",time);
	return EXIT_SUCCESS;    
}


/* FUnction definitions */
void* my_pthread_function( void *thr_data )
{
	int id,i;
	id =(int)thr_data;
	x[id]=0+id*h;
    y[id]=integration(x[id]); //call to perform the operations inside the integration
	//busy waiting
	while(i<WAIT) i++;
}

/* Operations inside the integration function will be returned by this function which receives the value of x*/
float integration(float x) {
	
	return (1.0/(1.0+pow(x,2)));
}
