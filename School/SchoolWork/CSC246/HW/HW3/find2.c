/* to compile this program, type
 gcc -std=c99 find2.c -lpthread in Linux Lab Machine (Realm RHEnterprise 6) environment
 */

#include <pthread.h>  //prototypes are here
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

/** struct for the fuction parameter */
typedef struct {
  char target[100]; // variable for the target word
  char fileName[100]; // filename of the file
} thread_param;


/** function to perform in each thread */
void *print ( void *args ) {
  
  FILE *fp;
  
  char *word; // create a variable to store for word in line
  
  char line[100]; // create a string variable to store the scanned line
  
  char newLine[100]; // create a variable to copy over the scanned line
  
  thread_param *actual_args = args;
  
  fp = fopen( actual_args->fileName, "r");
  
  printf("Word found in %s is in these lines:\n", actual_args->fileName );
  
  int num = 0; // counter for the amount of line that has the word
  
  while ( fgets ( line, sizeof line, fp ) ) { // read the file line by line
    
    strcpy(newLine, line); // copy over the line to newLine
    
    word = strtok( line, " \n\t" ); // truncates the line by the delimiters
    
    int count = 0; // counter of the line
    
    while ( word != NULL ) {
      
      if ( (strcmp( word, actual_args->target ) == 0 ) && count == 0 ) {
        
        printf("%s",newLine); // print out the line if word is equal to target
        num++; // increase the number of line print
        count ++; // increase the number of word found in one line
        
      }
      word = strtok (NULL, " \n\t" ); // end the while loop
    }
  }
  if ( num == 0 ) {
    printf("No word found in %s \n", actual_args->fileName); // print if no word found in this file
  }
  free(actual_args); // free the allocated memory
  
  pthread_exit(NULL); // exit the thread
}



int main( int argc, char *argv[] ) {
  
  pthread_t thread[argc-1]; // an array of thread to be join upon
  
  
  for ( int i = 2; i < argc ; i++ ) {
    
    thread_param *args = malloc(sizeof *args); // create the struct that contains the parameter info
    
    strcpy(args->target, argv[1]); // copy the target word to variable
    strcpy(args->fileName, argv[i]); // copy the file word to variable
    pthread_create(&thread[i-2], NULL, print, args); // create thread
    pthread_join(thread[i-2], NULL); // wait until the thread to be done
    
  }
  return 0;
}
