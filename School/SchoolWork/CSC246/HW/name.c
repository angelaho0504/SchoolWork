/**
    @file name.c
    @author Angela Ho
    Print out my name to demostrate my understanding of system call and synchromizing
    the process. Used the linux environment remotely, VCL (Linux Lab Machine (Realm RHEnterprise 6)
 */

/** Header files needed for the program */
#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

int main () {
  int id = 0;            // initialize id
  id = fork();          // Create the child process
  if (id == 0) {        // Child Process
    printf("Ho, ");     // Print out the last name with child process
  exit(0);              // exit the child process
  }
  wait(NULL);           // wait until the child process exit
  printf("Angela\n");  // print out the first name with parent process
}
