// LAB 0: EXERCISE 7: Write a program that calculates the area and volume of a sphere.

#include <stdio.h>
#include <math.h>

double getSphereArea(double *ratio) {
	
	double area = 0;
	
	area = (double) 4.0* M_PI * (pow(*ratio,2));
	return area;

}

double getSphereVolume(double *ratio) {
	
	double volume = 0;
	
	volume = (double) (4.0/3.0) * M_PI * (pow(*ratio,3));
	return volume;

}

int main() {
	
	double ratio;

	printf("Enter the ratio of the sphere\n");
	scanf("%lf",&ratio);
	
	printf("The area of the sphere is: %f\n",getSphereArea(&ratio));
	printf("The volume of the sphere is: %f\n",getSphereVolume(&ratio));
	
	return 0;
}