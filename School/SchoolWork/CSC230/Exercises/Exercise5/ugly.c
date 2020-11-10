// Same prime-detection strategy, but without any structured
// looping constructs.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * Report a list of prime values.
 */
int main( void )
{
    // Get the range of values we're supposed to test.
    unsigned int low, high;
    if ( scanf( "%d%d", &low, &high ) != 2 ) {
        printf( "Invalid input\n" );
        exit( EXIT_FAILURE );
    }
  
    // Write your own, ugly solution, using goto instead of structured looping.
    unsigned int i = low;
    unsigned int fact = 2;
    
topOfPrimeLoop:
    
    if ( i % fact == 0 ) {
        goto notPrime;
    }
    
    if ( fact*fact > i ) {
        goto isPrime;
    }
    
    fact ++;
    goto topOfPrimeLoop;
    
isPrime:
    
    printf("%u\n", i);
    
notPrime:
    
    if ( i == high) {
        goto doneWithLoop;
    }
    
    i++;
    fact = 2;
    goto topOfPrimeLoop;
    
doneWithLoop:
    
  
  return EXIT_SUCCESS;
}
