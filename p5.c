/*
	
	PDP WINTER PROJECT: program 5

	Write a parallel program that solves the following system of linear equations with the use of OpenMP:

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<stdio.h>
#include <unistd.h>
#include<omp.h> //include the header file opm.h

omp_lock_t lock;

int main()
{
	omp_init_lock(&lock); //lock state is unlocked and for now it can be setted to locked or unlocked 
	int i,j, numThreads;
	float sum;
	float *b;
	float *x; // vector to save bn values

	// Ask the number of intervals
	printf("Please enter n!\n");
	scanf("%d",&numThreads); 

	float aMatrix[numThreads][numThreads]; // matrix of a elements
	
	b = malloc(sizeof(float)*numThreads); 
	x = malloc(sizeof(float)*numThreads); 
	omp_set_num_threads(numThreads); //the number of threads is deteermined to 4 (0,1,2,3)

	srand(time(NULL)); // seed 
/* With schedule clause we can specify which iterations are going to be executed by each thread*/
  //This is a block squedule where the iterrations are divided in chunks of a similar size and each one is assigned to a different thread.
	printf("\nThe random generated is matrix is : \n");
	for(i=0;i<numThreads;i++)
	{
		printf("\n");
		for(j=0;j<numThreads;j++){
			aMatrix[i][j] = rand() % 10+1;
			printf("%f\t", aMatrix[i][j]);
		}printf("\n\n");
	}
	printf("\nThe random generated is b vector is : \n");
	for(i=0;i<numThreads;i++)
	{
		b[i] = rand() % 10;
		x[i] = 100.0;
		printf("%f  ",b[i]);
	}printf("\n\n");

	printf("\nThe solution of the system is  : \n");
	#pragma omp parallel shared(aMatrix,b,x) private(i, j)
    #pragma omp for schedule(static)
    
    for (i = 0; i < numThreads; i++) 
    {
		if (i!=0) // no need to check because the first terms not depend on the others
		{
			while(x[i-1] == 100.0) { // wait till the prevoius terms of the serie is calculated

			sleep(1);
		   }
		}
		
		
		sum = 0.0;

       for (j = 0; j <= i; j++)
       {
		   
		   if (j==i) //last term of the serie
		   {
			  
			sum= (b[j]-sum)/aMatrix[i][j]; // xn =() bn - previus terms) / ajj
		   }else{
			
		   
		   sum = sum + (aMatrix[i][j] * x[j]); // sum of the serie updated with echa calculated term till ann*xnn(last term with a special calculation)
		   }
		}
		x[i] = sum; //each value of x is saved solving the system 
		printf("X%d is: %f \n ",i,x[i]);
	}
}