// g++ barrier.cpp -lpthread to compile
#include <pthread.h>
#include <iostream>
using namespace std;


pthread_mutex_t m   = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t notFull = PTHREAD_COND_INITIALIZER;
int totalThreads = 0;
char taskWhileWaiting[] = {'A','B','C','D'};


void waitForOthers();

void * Restaurant(void * param);


int main(){

   pthread_t hungryThd[4]; 
   pthread_attr_t attr; 
   pthread_attr_init(&attr); 
   
   // create threads
  for(int i = 0; i<4; i++){
    pthread_create(&hungryThd[i], &attr, Restaurant, NULL);
  }
   
   // join threads
  for(int j=0; j<4; j++){
    pthread_join(hungryThd[j], NULL);
  }
   
   
   return 0;
}


void waitForOthers(){
  
  //Critical section
  pthread_mutex_lock(&m);
  totalThreads++;
  int current = totalThreads;
  cout<<"I am thread "<<current<<" working on Task " << taskWhileWaiting[totalThreads -1 ] << ",and waiting to eat."<<endl;
  if(totalThreads<4) {
    pthread_cond_wait(&notFull, &m);
  }
  pthread_mutex_unlock(&m);
  pthread_cond_signal(&notFull);
  cout<<"I am thread "<<current<<" and I am eating." << endl;
  pthread_exit(NULL);
   
}


void * Restaurant(void * param){

   // call wait function
  waitForOthers();
  pthread_exit(NULL);
   
}



















