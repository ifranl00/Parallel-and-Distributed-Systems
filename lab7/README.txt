Comparation of the results obatained related to the amount of time spent of each process in the program type and pack:

	- Output of execution of type:

		Time of execution of proccess 0: 0.000225
		Time of execution of proccess 1: 0.000314

	- Output of execution of pack:

		Time of execution data of proccess 0: 0.000011
		Time of execution data of proccess 1: 0.000683


The process 0 spent less time in pack program because is faster to pack all the data and make one mpi_send action than make many mpi_send actions.

The process 1 spent more time in pack program because it had to unpack before receiving and in the type program it had only to receive not unpack anything.




