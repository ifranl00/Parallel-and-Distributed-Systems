#include <stdio.h>
#include <stdlib.h>
#include "tmeas.h"
#include <pthread.h>

#define SIZE 12
#define NUM_THR 4
#define WAIT 1000000

/* define structure of thread's data */
typedef struct {
	int id;
	int *a;
	int *b;
	int *c;
} vectors;

struct arg_struct {
	int id;
	int size;
	int iterator;
};

vectors vec;

void* my_pthread_function( void *ptr );




int main()
{
	tstart();
	int *vec1,*vec2,*vec3;
	double t;
	struct arg_struct *args;

	pthread_t thread_array[NUM_THR];
    int i, thr;
    vec.a=(int *)malloc(sizeof(int)*SIZE);
	vec.b=(int *)malloc(sizeof(int)*SIZE);
	vec.c=(int *)malloc(sizeof(int)*SIZE);
	
	srand(time(NULL));			//random numbers generator initialization;
	

	for(i=0;i<SIZE;i++)
	{
		vec.a[i]=rand()%1001;		//random number generator
		vec.b[i]=rand()%1001;
		printf("vec.a[%d]=%d,vec.b[%d]=%d\n",i,vec.a[i],i,vec.b[i]);
	}

	i = 0;

	for( i = 0; i < NUM_THR; i++ )
	{
		args = malloc(sizeof(struct arg_struct));
		(*args).id=i;
		(*args).size=SIZE/NUM_THR;
		(*args).iterator=i*(SIZE/NUM_THR);
		thr = pthread_create( &thread_array[i], NULL, my_pthread_function, (void *)args);
		
		if( thr ) {
			fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
			exit(-1);
		}
	}
	
	
	


/* Wait till threads are complete before main continues. Unless we  */
     	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */

	for( i = 0; i < NUM_THR; i++ )	
		pthread_join( thread_array[i], NULL);

	
	
	for(i=0;i<SIZE;i++)
		printf("vec.c[%d]=%d\n",i,vec.c[i]);

	t=tstop();
	printf("Total time=%lf\n",t);

	
	return EXIT_SUCCESS;    
}

void* my_pthread_function( void *args )
{
	struct arg_struct *myargs = (struct arg_struct*)args;
	double time = 0.0;
	tstart();
	int i,id, size, iterator;

	id= (*myargs).id;
	size= (*myargs).size;
	iterator= (*myargs).iterator;
	free (args);

	printf("I am %d thread\n", id);

	for(i=iterator;i<(iterator+size);i++){
		vec.c[i]=vec.a[i]+vec.b[i];
	}

	//busy waiting
	while(i<WAIT) i++;
	time = tstop();
	printf("Execution time of %d :%lf\n", id,time);
}

	
	
