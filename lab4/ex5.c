#include<stdio.h>
#include<omp.h> //include the header file opm.h

omp_lock_t lock;

int main()
{
	omp_init_lock(&lock); //lock state is unlocked and for now it can be setted to locked or unlocked 
	int a=0,i;
	double t_start, t_end;
	omp_set_num_threads(4); //the number of threads is deteermined to 4 (0,1,2,3)
/* With schedule clause we can specify which iterations are going to be executed by each thread*/

//a)static, chunk_size = 3
	//This is a block cycle schedule and the iterations are divided in size of 3 chunks and aasigned in cycle in order of the threads.

	printf("LOOP 1: static, chunk_size = 3\n"); 

	t_start = omp_get_wtime();
	#pragma omp parallel for schedule(static,3)
		for(i=0;i<150000;i++)
		{
			a*=0.5;
			//printf("Thread %d, index %d\n",omp_get_thread_num(),i);
		}

	t_end = omp_get_wtime();
	printf("LOOP 1 finished in %lf secs\n", t_end-t_start);

//b)static, default chunk size
  //This is a block squedule where the iterrations are divided in chunks of a similar size and each one is assigned to a different thread.

	printf("LOOP 2: static, default chunk size\n"); 

	t_start = omp_get_wtime();
	#pragma omp parallel for schedule(static)
		for(i=0;i<150000;i++)
		{
			a*=0.5;
			//printf("Thread %d, index %d\n",omp_get_thread_num(),i);
		}

	t_end = omp_get_wtime();
	printf("LOOP 2 finished in %lf secs\n", t_end-t_start);

//c)dynamic, chunk_size = 3
  //The iterations are divided in chunks of size 3 and assigned to the threads in order that the chunks are given to the thread that comes first or finish its chunk first.

	printf("LOOP 3: dynamic, chunk_size = 3\n");

	t_start = omp_get_wtime();
	#pragma omp parallel for schedule(dynamic,3)
		for(i=0;i<150000;i++)
		{
			a*=0.5;
			//printf("Thread %d, index %d\n",omp_get_thread_num(),i);
		}

	t_end = omp_get_wtime();
	printf("LOOP 3 finished in %lf secs\n", t_end-t_start);
//d)dynamic, default chunk size
  //The iterations are divided in chunks of size 1 by default and assigned to the threads in order that the chunks are given to the thread that comes first or finish its chunk first.
	printf("LOOP 4: dynamic, default chunk size\n");

	t_start = omp_get_wtime();
	#pragma omp parallel for schedule(dynamic)
		for(i=0;i<150000;i++)
		{
			a*=0.5;
			//printf("Thread %d, index %d\n",omp_get_thread_num(),i);
		}

	t_end = omp_get_wtime();
	printf("LOOP 4 finished in %lf secs\n", t_end-t_start);

	//with omp_get_wtime() we are able to compare execution times in diferent schedules but it would take to run many times and consider the processor and another important information of our device to create a good stadistic and say properly which is faster/slower for x methods or operations.
}	

