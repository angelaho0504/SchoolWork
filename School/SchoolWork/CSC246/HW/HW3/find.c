/* to compile this program, type
 gcc -std=c99 find.c in Linux Lab Machine (Realm RHEnterprise 6) environment
 */

/** Header files needed for the program */
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include <string.h>

int main ( int argc, char *argv[] ) {
  
  FILE *fp; // create a variable for file
  
  char target[100]; // create a variable to store the target word
  
  strcpy(target,argv[1]); // copy the second argument (which is the user's choice of word ) to target
  
  char *word; // create a variable to store for word in line
  
  char line[100]; // create a string variable to store the scanned line
  
  char newLine[100]; // create a variable to copy over the scanned line
  
  int id = 0; // initialize id
  
  for ( int i = 2; i < argc; i++ ) {
    id = fork(); // create new child process
    if ( id == 0 ) { // Child process
      fp = fopen( argv[i] , "r" ); // open the file of i argument with read mode
      printf("Word found in %s is in these lines:\n", argv[i] );
      int num = 0; // counter for the amount of line that has the word
      while ( fgets ( line, sizeof line, fp ) ) { // read the file line by line
        strcpy(newLine, line); // copy over the line to newLine
        word = strtok( line, " \n\t" ); // truncates the line by the delimiters
        int count = 0; // counter of the line
        while ( word != NULL ) {
          if ( (strcmp( word, target ) == 0 ) && count == 0 ) {
            printf("%s",newLine); // print out the line if word is equal to target
            num++; // increase the number of line print
            count ++; // increase the number of word found in one line
          }
          word = strtok (NULL, " \n\t" ); // end the while loop
        }
      }
      if ( num == 0 ) {
        printf("No word found in %s \n", argv[i]); // print if no word found in this file
      }
      exit(0); // exit the child process
    }
      else if ( id > 0 ) {  // Parent process
        wait(NULL); // wait until the child process to exit
      }
  }
  return 0;
}
