/**
    @file sortList.c
    @author Angela Ho
    reads a list of doubles from standard input, using a resizable
    array to store as many values as needed. Then, it sorts the
    array and prints the values out in sorted order.
 */
#include <stdio.h>
#include <stdlib.h>

// Put your macro definitions here.  That should be all
// you need to do to complete this exercise.

/**
    Expands to the declaration syntax for
    the three variables used in a resizable array implementation,
    name_len, name_cap and name (the pointer itself).
 */
#define DECL_LIST( type, name )  \
  int name##_cap = 5; \
  int name##_len = 0; \
  type *name = (type *) malloc( list_cap * sizeof(type) ) \

/**
    Expands to the code to make sure the resizable array
    has enough capacity for another element and to enlarge it if it doesn’t.
 */
#define CHECK_CAP(type, name) \
  if ( name##_len >= name##_cap ) { \
  name##_cap *= 2; \
  name = (type *) realloc( name, name##_cap * sizeof(type) ); \
}

/**
    Expands to an expression for the number of
    elements currently stored in the array
 */
#define SIZE(name) name##_len

/**
    Expands to the first line of a for loop that uses an int
    variable named var to iterate from 0 up to (but not including) limit.
 */
#define FOR(var,end) for(int var = 0; var < end; var ++ )

/**
 Expands to a block of code that swaps the values of two
  variables a and b of the given type. We need the type
  parameter in order to declare a temporary variable that
  will help swap the values.
 */
#define SWAP(type, a, b) \
{ \
  type temp = a; \
  a = b; \
  b = temp; \
}  \

int main()
{
  // Make a resizable list.
  DECL_LIST( double, list );

  double val;
  while ( scanf( "%lf", &val ) == 1 ) {
    // Grow the list when needed.
    CHECK_CAP( double, list );

    // Add this item to the list
    list[ SIZE( list ) ] = val;
    SIZE( list ) += 1;
  }

  // Bubble-sort the list.
  FOR( i, SIZE( list ) )
    FOR( j, SIZE( list ) - i - 1 )
      if ( list[ j ] > list[ j + 1 ] )
        SWAP( double, list[ j ], list[ j + 1 ] );

  // Print out the resulting, sorted list, one value per line.
  FOR( i, SIZE( list ) )
    printf( "%.2f\n", list[ i ] );
  
  return EXIT_SUCCESS;
}
