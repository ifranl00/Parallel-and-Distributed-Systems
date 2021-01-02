/*
	
	PDP WINTER PROJECT: program 4

	Euler gamma constant is defined as the limit of a sequence g n where:
	Write a concurrent program that calculates g n , with the following assumptions:
		- N - the number of elements of the sum is loaded from the keyboard
		- P - number of processes, which will compute the sum is a constant in a program
	Each process calculate his own fragment of the sum - for example, for n = 100, p = 10, the first
	process computes elements 1 to 10, the second from 11 to 20, etc., at the end the partial sums are
	added and logarithm is subtracted. Note: n may not be divisible by p. The program can be made
	using any familliar technique .

*/