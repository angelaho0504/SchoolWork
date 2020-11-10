#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // For NULL, although we don't need it.

/**
    Increment a, b and c by the value of the 4th parameter.
    @param a address of a
    @param b address of b
    @param c address of c
 */
void incrementAll ( int * a, int * b, int * c , int increment ) {
    *a += increment;
    *b += increment;
    *c += increment;
}

/**
    Copy the value of b to a, c to b and a to c.
    @param a address of a
    @param b address of b
    @param c address of c
 */
void rotate ( int * a, int * b, int * c ) {
    int temp = *a;
    *a = *b;
    *b = *c;
    *c = temp;
}

/**
    Return the address of the one containing the largest value.
    @param a address of a
    @param b address of b
    @param c address of c
 */
int * getLargest( int * a, int * b, int * c ) {
    int max = *a;
    if ( *b > max ) {
        max = *b;
    }
    if ( *c > max ) {
        max = *c;
    }
    
    if ( max == *a ) {
        return a;
    } else if ( max == *b ) {
        return b;
    } else {
        return c;
    }
}

/**
    Starting point of the program
 */
int main()
{
    int a = 100;
    int b = 50;
    int c = 25;

    // Get initial values for a, b and c.
    printf( "a = %d b = %d c = %d\n", a, b, c );

    // Call a function to increment all the values by the given constant
    // (10 here)
    incrementAll( &a, &b, &c, 10 );

    // Report current values for a, b and c.
    printf( "a = %d b = %d c = %d\n", a, b, c );

    // Simultaneously move the value from b to a, from c to b and from a
    // to c.
    rotate( &a, &b, &c );

    // Report current values for a, b and c.
    printf( "a = %d b = %d c = %d\n", a, b, c );

    // Get back a pointer to the largest value.
    int *largest = getLargest( &a, &b, &c );

    // Make this value smaller.  We do need the parentheses here.
    (*largest)--;

    // Report final values for a, b and c.
    printf( "a = %d b = %d c = %d\n", a, b, c );

    return EXIT_SUCCESS;
}
