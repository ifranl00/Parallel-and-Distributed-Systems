#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <tmeas.h>

int main() {

	float b = 0.0;
	double time = 0.0;

	tstart();

	for (int i = 0; i < 1000000; i++)
	{
		b = 2.0+b;
	}


	for (int i = 0; i < 20; i++)
	{
		printf("%lf\n",b);
		
	}
	time = tstop();
	printf("Execution time:%lf\n", time);

	return 0;
}
