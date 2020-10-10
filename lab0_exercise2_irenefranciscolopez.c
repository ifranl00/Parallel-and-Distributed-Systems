// LAB 0: EXERCISE 2: Write a program that calculatees the value of expressions.

#include <stdio.h>
#include <math.h>

int main() {
	
	float x,y;
	int i,j;
	double v,w,v1,v2,v3,op1v,v4,op2v,op3v,op4v;
	double w1,op1w,op2w,w2,w3,w4;
	
	printf("Enter the values like i,j,x,y\n");
	scanf("%d%d%f%f", &i, &j, &x, &y);

	v1 = (double) log(pow(x,2));
	v2 = (double) 2* (pow(x,3));
	v3 = (double) pow(y, -2);
	op1v = v1+v2+v3;
	
	v4 = (double) sin(x)-10;
	op2v = (double) v4*j;
	
	op3v = (double) 2*i;
	op4v = (double) j+1;
	
	v = (op1v/op2v) + (op3v/op4v);
	
	printf("The value of v is: %f\n",v);
	
	w1 = (double) cos(x+1);
	w2 = (double)x*w1;
	op1w = (double)w2/2;
	
	w3 = (double) 5*(pow(i,2));
	w4 = (double) sin(w3);
	
	op2w = (double) pow(w4,2);
	
	w = op1w*op2w;
	
	printf("The value of w is: %f\n",w);
	
	
	return 0;
}