/**
    @file stats.c
    @author Angela Ho
    Reads a sequence of real numbers and report the minimum, maximum
    and average values.
 */
#include <stdio.h>
#include <stdlib.h>

/**
    Starting point of the program
 */
int main( void )
{
    // Figure out how many values there are.
    // ...
    int n;
    scanf( "%d", &n );

    // Read in the first value into val.
    // ...
    double val;
    scanf( "%lf", &val );
    
    // That first value is our tentative min and max value.
    double minValue = val, maxValue = val, total = val;
    
    // Get the remaining n-1 values and update minValue, maxValue and total
    // based on each one.
    // ...
    double current;
    for( int i = 0; i < n-1; i++ ) {
        scanf("%lf", &current);
        if( current < minValue ){
            minValue = current;
        } else if( current > maxValue ){
            maxValue = current;
        }
        total += current;
    }
    // Report the stats.
    // ...
    printf( "Minimum: %8.2f\n", minValue );
    printf( "Maximum: %8.2f\n", maxValue );
    printf( "Average: %8.2f\n", total / n );
    
    // Exit successfully.
    // ...
    return EXIT_SUCCESS;
}
