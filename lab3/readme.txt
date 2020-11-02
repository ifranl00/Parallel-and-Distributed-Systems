/***********************************************************************************************/

										LABORATORY 3

									Irene Francisco López

/***********************************************************************************************/

Question 2: What is the value of this variable at the end? Check the
version with enabled and disabled mutexes.


	- Without mutexes: "Global variable 12428".
	- With mutex enabled: "Global variable 0".

	We have critic zones where the global variable are modified. Some threads may want to modify the values of the global variable at the same time and if we have mutexed enabled we can see the expedted result 0, because the critic zones are only modified by a thread while the rest are waiting for their turn. 

	In the case when we have disabled the mutexes, we obtain this result because it is not prevented that other threads will be executibg concurrently and access the same memory locations.






