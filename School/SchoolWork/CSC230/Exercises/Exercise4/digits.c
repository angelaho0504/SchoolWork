/**
    @file digits.c
    @author Angela Ho
    Do some I/O and math with unsigned types.
 */

#include <stdlib.h>
#include <stdio.h>

/**
    Add up all the digits in the value, x, and return the sum.
    @param x unsigned long number to add up
*/
unsigned int digitSum( unsigned long x )
{
    unsigned int sum = 0;
    while ( x != 0 ) {
        sum += x % 10;
        x = x / 10;
    }
    return sum;
}

/**
    Program starting point.
 */
int main()
{
    // Range of values we're supposed to check.
    unsigned long low, high;

    // Target sum we're supposed to look for.
    unsigned int target;

    // Read the range of values from the user.
    if( scanf( "%lu", &low ) == 0) {
        return EXIT_FAILURE;
    }
    if( scanf( "%lu", &high ) == 0) {
        return EXIT_FAILURE;
    }

    // Read the digit sum we're supposed to look for.
    if( scanf( "%u", &target ) == 0 ){
        return EXIT_FAILURE;
    }
    

    // Check all values from low up to high (inclusive), and report the ones
    // that have the given digit sum.
    for( unsigned long i = low; i <= high; i++ ) {
        unsigned int num = digitSum( i );
        if ( num == target ){
            printf("%lu\n", i);
        }
    }

  return EXIT_SUCCESS;
}
