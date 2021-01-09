/*

	PDP WINTER PROJECT: program 6

	Write a program that calculates the prime numbers using the sieve of Erathosthenes. The program
	should be made with the use of OpenMP.

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
	int i,j,k,n;
	int *p1; 
	// Ask the number of intervals
	printf("Please enter n!\n");
	scanf("%d",&n); 
	p1 = malloc(sizeof(float)*n); // from 1 to n
	omp_set_num_threads(10); //the number of threads is deteermined to 4 (0,1,2,3)

/* With schedule clause we can specify which iterations are going to be executed by each thread*/
  //This is a block squedule where the iterrations are divided in chunks of a similar size and each one is assigned to a different thread.

    for (i = 0; i < n; i++) 
    {
		p1[i] = i; // initialize the array with all natural numbers from 1 to n
	}

	#pragma omp parallel shared(p1) private(i,j,k)
    #pragma omp for schedule(static)
	for (int i = 0; i < 1; i++) //just one iteration to validate the openmpi canonical rules of a loop
	{
	
	for ( j = 2; j*j<=n; j++) // start from 2 because is the first prime number
		{
			if(p1[j] != 0) { // may be a prime number 
				for ( k =j*j; k <=n ; k +=j) // to detect the multiples of prime numbers
				{
					p1[k] = 0; // is not a prime number because is a multiple of a one
				}		
			}
		}
	}	

	printf("The prime numbers: \n");
	for ( i = 2; i <= n; i++)
	{
		if(p1[i] != 0){ // if is setted as prime
			printf("%d ",p1[i]);
		}
	}
	
}