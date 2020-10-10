// LAB 0: EXERCISE 5: Do the previous task with other type of loop.

#include <stdio.h>

int main() {
	
	double a;
	double result;

	while(1) {
		
		printf("Insert the value of a\n");
	 	scanf("%lf",&a);
	 	
	 	if(a<=0) {
	 		break;
	 	}
	}
	
	result = (double) 3*a;
	printf("The result of 3*a is %f:\n", result);
		
	return 0;

}