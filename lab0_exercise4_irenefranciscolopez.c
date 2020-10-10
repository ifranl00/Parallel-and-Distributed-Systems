// LAB 0: EXERCISE 4: Write a program on the basis of the block diagram

#include <stdio.h>

int main() {
	
	double a;
	double result;

	do 
	 {
	 	printf("Insert the value of a\n");
	 	scanf("%lf",&a);
	 	}while(a>0);
	result = (double) 3*a;
	printf("The result of 3*a is %f:\n", result);
		
	return 0;

}
