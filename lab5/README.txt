
				LABORATORY 5                           


**Exercise 2:
	
	2.1. If we uncomment the NOWAIT directive, a thread will continue executing a parallel region not waiting for the other thereads to complete this region, so we can see in the execution that, in difference to a execution without the NOWAIT, threads are not waiting to do the for iterations so in this case, threads involved in sections with the sleep not overtake tthe rest because the first ones,fact that does not occur with the notwait commented.


	2.2. A omp barrier specifies from what point the threads must wait until all of them arrive.

	In this case, i can see not differnce at execution level with that barrier with or without nowait but the barrier does specify that threads must wait untill all of them arrive from the point where is established.

**Exercise 3:

	3.1. With parallization: 
		Insert number:
			5
			Square=12500
			Execution time: 0.000010

	3.2 Without parallization:

		Insert number:
			5
			Square=12500
			Execution time: 0.000002

	For testing and comparing properly it is used the test reduction clause #pragma omp parallel for reduction(+:square).

	For measuring execution times is it used omp_get_wtime().

**Exercise 4:

	4.1. If we want to involve parallel, we have to use #pragma omp parallel shared(A,B,C) private(i, j, k) for specifying the variables that are private and the shared ones that may be modificated.

	We can try diferent paralelizations by changing the schedule, for example:

		- with dynamic schedule: #pragma omp for schedule(dynamic):
			Time of matrix multiplification = 7.008215

		- with static schedule: #pragma omp for schedule(static):
			Time of matrix multiplification = 6.725896

	4.2. If we do not use parallel:
		Time of matrix multiplification = 6.315442







