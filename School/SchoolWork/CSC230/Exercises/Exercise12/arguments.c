/**
    @file arguments.c
    @author Angela Ho (aho)
    Dynamically allocate a 2D array that holds the same set of strings as
    the command line arguments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
    Print out the command-line arguments, one arguments per line
    @param number of command-line arguments
    @param cols length of the string + 1
    @param args[][ cols ] dynamincally aloocated command-line arguments
 */
void printArguments( int rows, int cols, char args[][ cols ] )
{
  // Each row of the args array contains a string.  Print out each of the
  // strings.
  for ( int i = 0; i < rows; i++ ) {
    for ( int j = 0; j < strlen(args[i]); j++ ) {
      printf("%c", args[i][j]);
    }
    printf("\n");
  }
}

/**
    Starting point of the program, dynamiacally allocated the command-line
    arguments, then print them out one arguments per line.
    @param argc number of command-line arguments
    @param *argv[] array of char pointers, pointing to the start of one
    of the commandline arguments
 */
int main( int argc, char *argv[] )
{
  // Figure out the length of the longest command-line argument.
  int longest = 0;

  for ( int i = 0; i < argc; i++ ) {
    size_t len = strlen(argv[i]);
    if ( len > longest ) {
      longest = len;
    }
  }
  
  // Dynamically allocate a 2D array of characers, with one row for every
  // command-line argument and (exactly) enough columns to hold a copy of the
  // widest command-line argument (including the null terminator at the end).
  char (*words)[ longest + 1 ];
  words = ( char (*)[longest + 1])malloc( longest * argc * sizeof(char) );

  // Copy each command-line argumetn to a row of this new array.
  for ( int i = 0; i < argc; i++ ) {
    for ( int j = 0; j < strlen(argv[i]); j++ ) {
      words[ i ][ j ] = argv[i][j];
    }
  }

  // Call a function that's expecting the command-line arguments as a 2D array
  // (not as an array of pointers).
  printArguments( argc, longest + 1, words );

  free(words);
  return 0;
}
