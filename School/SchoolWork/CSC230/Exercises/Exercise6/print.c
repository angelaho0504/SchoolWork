/**
    @file print.c
    @author Angela Ho (aho)
    This program print the given character,
    if the charavter is a space print '-' instead,
    also provide the number of spaces.
 */
#include "print.h"
#include <stdio.h>

/*a new global variable to keep a count of the spaces we print.*/

int spaceCount;

/**
    Print the given character, counting spaces as we print and
    replacing each space with a '-'. The parameter type is char here,
    @param ch given character
 */
void dashesForSpaces( char ch )
{
   // Fill in the body of this function.
    if ( ch == ' ') {
        putchar('-');
        spaceCount++;
    }
    else {
        putchar(ch);
    }
}
