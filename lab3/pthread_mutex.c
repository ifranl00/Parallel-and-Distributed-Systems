#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#define NUM_BASKETS 2
#define NUM_CLIENTS 5

/* global variable */
int shopping_baskets[NUM_BASKETS];

/* initialize mutex */
pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER;

void* my_pthread_func( void *arg )
{
    int id,pos,founded,t,visit;
    id=(int)arg;

    
      visit = 0;
    printf("The client no. %d entered the supermarket\n",id+1);

    do{
        pthread_mutex_lock( &my_mutex );
      founded = 0;
      pos = 0;
        for (int i = 0; i < NUM_BASKETS; i++){

          if(shopping_baskets[i] == 0 && founded == 0) {

            shopping_baskets[i] = 1; //This client has taken a basket
            founded = 1;
            pos = i+1;
         
        }
     
      }
       pthread_mutex_unlock( &my_mutex );

      if(founded != 0) {
        printf("Client no. %d is taking the shopping cart no. %d\n",id+1,pos);
        visit +=1;
        t = (rand() % (10-1))+1;
        sleep(t);
        printf("Client no. %d left the supermarket after %d time units releasing the basket no.%d\n",id+1,t,pos);

        pthread_mutex_lock( &my_mutex );
        shopping_baskets[pos-1] = 0; //Release of the basket
        pthread_mutex_unlock( &my_mutex );
        sleep(1);


      }else {
        //printf("Client no. %d has left the supermarket for a while because there is not available baskets now.\n",id+1);
        sleep(1);
      }

    }while(founded == 0 || visit <2);
  
  
  return (void*)0;
}


int main(void) 
{
  	pthread_t thread_array[NUM_CLIENTS];
  	int i,thr,x;

    /* Initialization of the array of baskets as all were available as 0. */
    for (i = 0; i < NUM_BASKETS; i++)
    {
      shopping_baskets[i] = 0;
    }

    srand(time(NULL)); 
    
  for (int j = 0; j < NUM_CLIENTS; j++)
  {
   thr = pthread_create( &thread_array[j], NULL, my_pthread_func, (void *)j);
    
    if( thr ) {
      fprintf( stderr, "Error: return code from pthread_create() - %d", thr);
      exit(-1);
    }
  }
  	for( x = 0; x< NUM_CLIENTS; x++ ) 
    pthread_join( thread_array[x], NULL);

  	exit(0);

    return 0;

}
