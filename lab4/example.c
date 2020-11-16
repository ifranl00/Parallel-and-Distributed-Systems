#include<stdio.h>
#include<omp.h> //include the header file opm.h

omp_lock_t lock;

int main()
{
	omp_init_lock(&lock); //lock state is unlocked and for now it can be setted to locked or unlocked 
	srand(time(NULL));
	int a=0,i;
	omp_set_num_threads(4); //the number of threads is deteermined to 4 (0,1,2,3)

	/*PRIVATE: declaring private variable in OpenMP is replicating this variable for assigning a local copy for each thread */
	printf("Loop with firstprivate:\n"); 
	#pragma omp parallel for firstprivate(a) //with firstprivate clause it is specified that each thread have personal instance of a variable.
		for(i=0;i<10;i++)
		{
			printf("Thread %d a=%d\n",omp_get_thread_num(),a);			
			a++;						
		}
	printf("After loop with firstprivate a=%d\n\n",a);//the a variable is iniatialized with its value because it exists before the parallel construct so it results 0.
	
	printf("Loop with private:\n");
	#pragma omp parallel for private(a) //private clause changes the variable value in parallel zone but not outside
		for(a=0;a<10;a++)
		{			
			printf("Thread %d a=%d\n",omp_get_thread_num(),a);// value of a may change only in this region
		}
	printf("After loop with private a=%d\n\n",a);// the variable keeps its value from before the region
	printf("Loop with lastprivate:\n");
	#pragma omp parallel for lastprivate(a) //lastprivate clause transfer values to the outside from the parallel context
		for(i=0;i<10;i++)
		{
			//1. try to change it to random number and notice how it works
			a=/*omp_get_thread_num();*/rand()%11;		
			printf("Thread %d a=%d\n",omp_get_thread_num(),a);//a is equal to the private value of the thread that executes the last part, in this case, the last iteration.
		//So using random number or the number of the thread, the value asigned to a is always the private version of thread 3 that executes the last part the latest.
		}
	printf("After loop with lastprivate a=%d\n\n",a);
	

	/*SHARED: this variables are visible for all threads and run in parallel regions that are associated*/
	printf("Loop with shared:\n");	
	a=0;
	#pragma omp parallel for shared(a) 
	for(i=0;i<10;i++)
	{
		//2. What happens when we disable locks?
		//omp_set_lock(&lock); //the lock is now in locked state
		a=omp_get_thread_num();
		printf("Thread %d a=%d\n",omp_get_thread_num(),a);	
		//omp_unset_lock(&lock); //Now its state is unlocked
		//It happens the same with or without locks because it is a shared variable that all can have access to read and write.	
	}
	//3. What is the value of "a" after several runs? 
	printf("After loop with shared a=%d\n\n",a); //it varies depending on the last thread that changes the value
	
	printf("Loop without data-sharing attribute clause:\n");	
	a=0;
	#pragma omp parallel for //this directive allows to divide the loop interations between threads
	for(i=0;i<100;i++)
	{		
		a++;
		printf("Thread %d Iteration %d a=%d\n",omp_get_thread_num(),i,a);//each thread do different iterations
	}
	//4. What is the default data scope without any clauses?
	//If thre is not additional clauses as schedule, the directive will partition the iterations as equally as possible between the all the threads.
	//So the value of a is changed and reach 100.
	printf("After loop without data-sharing attribute clause a=%d\n",a);	
}	

