/**
    @file style.c
    @author Angela Ho (aho)
    A program randomly generate a paragraph of text
 */

#include <stdio.h>
#include <stdlib.h>

/** Max number of words in a line */
#define LINE_LENGTH 72
/** Modulus of radom number for letter */
#define MOD_FOR_LETTER 26
/** Number added to get a random number for letter */
#define RAND_NUMBER_LETTER 97
/** Modulus of random number for the amount of letter printed in one time*/
#define MOD_FOR_LEN 10
/** Number added to get a random number for the amount of letter printed in one time */
#define RAND_NUMBER_LEN 1

/**
    Print random lower-case letters
    @param x number of letters needed
 */
void printWord( int x )
{
    for ( int i = 0; i < x; i++ ){
        // Print a random lower-case letter.
        printf( "%c", RAND_NUMBER_LETTER + rand() % MOD_FOR_LETTER );
    }
}

/**
    Print a line of words up to a limited length
    @return number of words
 */
int printLine()
{
    int count = 0, pos = 0, space = 0;
    int len = RAND_NUMBER_LEN + rand() % MOD_FOR_LEN;
	// Print a line of words up to a limited length.
	while ( pos + len + space < LINE_LENGTH ) {
		if ( space > 0 ) {
			printf( " " );
        }
		printWord( len );
		pos += len + space;
		len = RAND_NUMBER_LETTER + rand() % MOD_FOR_LEN;
		space = 1;
		count += 1;
	}
    printf( "\n" );
	return count;
}

/**
    Print a paragraph with n number of lines
    @param n number of lines in a paragraph
 */
int printParagraph( int n )
{
    int total = 0;
    for ( int i = 0; i < n; i++ )
        total += printLine();
    return total;
}

/**
    Starting point of the program, print a paragraph of random letter.
    @return program exit status
 */
int main()
{
    int w = printParagraph(10);
    printf("Words: %d\n",w);
    return 0;
}
