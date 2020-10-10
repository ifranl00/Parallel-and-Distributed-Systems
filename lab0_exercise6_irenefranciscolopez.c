// LAB 0: EXERCISE 6: Write a program which for the given array returns the maximun a minimum values.

#include <stdio.h>

int minMaxGetter(int sample[], int size) {
	
	int min = 0;
	int max = 0;
	int i;
	
	for(i = 1; i<size; i++) {
		
		if(min>sample[i]) {
			min = sample[i];
		}
		
		if(max<sample[i]) {
			max = sample[i];	
		}
		
	}
	printf("The minimum of the entered array is: %d\n",min);
	printf("The maximum of the entered array is: %d\n",max);
	
}

int main() {
	
	int sample[1000],x,size;
	
	printf("Enter size of the array: ");
    scanf("%d", &size);
 
    printf("Enter the elements of the array: ");
    for(x=0; x<size; x++) {
    
        scanf("%d",&sample[x]);
    }
    
    minMaxGetter(sample,size);
    return 0;
}