/** gcc -std=c99 -lpthread sleeper.c rider.c coordinator.c to compile */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "rider.h"
#include "sleeper.h"

int *coordinator;
int cnt = 0;
int in = 0;
int out = 0;
int buff_size;

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;

//These are the condition variables for our monitor
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

// arguments to pass in rider threads
typedef struct {
  int riderId;
  int carId;
}id;

// arguments of stop thread
typedef struct {
  int second;
} record;

// thread method to stop the whole program
void * stop ( void *args ) {
  record *actual = args;
  int second = actual->second;
  sleep(second);
  exit(0);
}

int main (int argc, char *argv[] ) {
  
  buff_size = atoi(argv[1]);

  // malloc an array
  coordinator = malloc ( buff_size * sizeof(int) );
  
  // fill in the array
  for ( int i = 0; i < buff_size; i++ ) {
    coordinator[i] = i + 1;
    cnt++;
  }
  
  // number of threads from command line
  int numOfThreads = atoi(argv[2]);
  
  // number of seconds sleep
  int seconds = atoi(argv[3]);
  
  // holds the threads
  pthread_t threads[numOfThreads];
  pthread_t sleepThread[1];
  // thread that used to stop the whole process
  record *a = malloc ( sizeof *a );
  a->second = seconds; 
  pthread_create(&sleepThread[0],NULL, stop, (void*)a);
  
  // create the threads
  for ( int i = 0; i < numOfThreads; i++ ) {
    id *args = malloc( sizeof *args );
    args->riderId = i + 1;
    pthread_create(&threads[i], NULL, rider,  (void*)args );
  }
  
  // join the threads
  for ( int i = 0; i < numOfThreads; i++ ) {
    pthread_join ( threads[i],NULL);
  }
  

}

int getInLine () {
  
  // obtain the mutex
  pthread_mutex_lock( &m1 );

  while ( cnt == 0 ) {
    
    pthread_cond_wait(&empty, &m1);  //Conditional wait
    
  }
  
  int currentId = coordinator[out];
  out = ( out + 1 )% buff_size;
  cnt--;

  pthread_mutex_unlock( &m1 ); // unlock the mutex
  return currentId;
}

void returnCar(int carId) {
  
  coordinator[in] = carId;
  
  in = (in + 1) % buff_size;
  
  cnt++;
  pthread_cond_signal( &empty );    //Signal consumers
}


