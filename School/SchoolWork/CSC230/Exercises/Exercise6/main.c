/**
    @file main.c
    @author Angela Ho (aho)
    This program reads in a text and replace
    spaces with '-'. Then prived the number of
    spaced included.
 */

#include <stdio.h>
#include <stdlib.h>
#include "print.h"

/**
    Start point of program
 */
int main()
{
  int ch;
  
  // Read all the characters from standard input.
  while ( ( ch = getchar() ) != EOF ) {
    // Let the print component print out this character.
    dashesForSpaces( ch );
  }

  // Report the number of spaces, as counted by the print component.
  printf( "\n" );
  printf( "That contained %d spaces\n", spaceCount );

  return EXIT_SUCCESS;
}
