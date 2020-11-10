#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
    Read in all the elemets of gird from standard input.
    @param rows number of rows in grid
    @param cols number of cols in grid
    @param grid[ rows ][ cols ] grid for the elements
 */
void readGrid( int rows, int cols, int grid[ rows ][ cols ] )
{
  // Add code to read in all the elements of grid from standard input.
    int val;
    for ( int i = 0; i < rows; i++ ) {
        for (int j = 0; j < cols; j++ ) {
            scanf("%d", &val);
            grid[ i ][ j ] = val;
        }
    
    }
}

// Add parameters to to pass a variable-sized array to the following
// function.  It's the same as the previous function, but I want you
// to get a chance to type it in yourself.
void reportMaxima( int rows, int cols, int grid[ rows ][ cols ] )
{
  // Add code to find local maxima and print them out in row major order.
    for ( int i = 0; i < rows ; i++ ) {
        for( int j = 0; j < cols; j++ ) {
            int num = grid[ i ][ j ];
            if ( i == 0 && j == 0 ) {
                if ( ( num > grid[ i ][ j + 1 ] ) &
                     ( num > grid[ i + 1 ][ j + 1] ) &
                    ( num > grid[ i + 1 ][ j ] ) ) {
                    printf("%d %d\n",i,j);
                }
            } else if ( i == 0 && j == cols - 1 ) {
                if ( ( num > grid[ i ][ j - 1 ] ) &
                    ( num > grid[ i - 1 ][ j -1 ] )&
                    ( num > grid[ i + 1 ][ j ]) ) {
                    printf("%d %d\n",i,j);
                }
            }else if ( i == rows - 1 && j == 0 ) {
                if ( ( num > grid[ i - 1 ][ j ] ) &
                    ( num > grid[ i - 1 ][ j + 1 ] ) &
                    ( num > grid[ i ][ j + 1 ] ) ) {
                    printf("%d %d\n",i,j);
                }
            }else if ( i == rows - 1 && j == cols - 1) {
                if ( ( num > grid[ i ][ j - 1 ] ) &
                    ( num > grid[ i - 1 ][ j - 1 ] ) &
                    ( num > grid[ i - 1 ][ j ] ) ) {
                    printf("%d %d\n",i,j);
                }
            }else if ( i == 0 ) {
                if ( ( num > grid[ i ][ j - 1 ] ) &
                    ( num > grid[ i + 1 ][ j - 1 ] ) &
                    ( num > grid[ i + 1 ][ j ] ) &
                    ( num > grid[ i + 1 ][ j + 1 ] ) &
                    ( num > grid[ i ][ j + 1 ] ) ) {
                    printf("%d %d\n",i,j);
                }
            } else if ( i == rows - 1 ) {
                if ( ( num > grid[ i ][ j - 1 ] )&
                    ( num > grid[ i - 1 ][ j - 1 ] ) &
                    ( num > grid[ i - 1 ][ j ] ) &
                    ( num > grid[ i - 1 ][ j + 1 ] ) &
                    ( num > grid[ i ][ j + 1 ] ) ) {
                    printf("%d %d\n",i,j);
                }
            } else if ( j == 0 ){
                if ( ( num > grid[ i - 1 ][ j ] )&
                    ( num > grid[ i - 1 ][ j + 1 ] ) &
                    ( num > grid[ i ][ j + 1] ) &
                    ( num > grid[ i + 1 ][ j + 1 ] ) &
                    ( num > grid[ i + 1 ][ j ] ) ) {
                    printf("%d %d\n",i,j);
                }
            } else if ( j == cols - 1 ) {
                if ( ( num > grid[ i - 1 ][ j ] ) &
                    ( num > grid[ i - 1 ][ j - 1 ] ) &
                    ( num > grid[ i ][ j - 1 ] ) &
                    ( num > grid[ i + 1 ][ j - 1 ] )&
                    ( num > grid[ i + 1 ][ j ] ) ) {
                    printf("%d %d\n",i,j);
                }
            } else {
                if ( ( num > grid[ i - 1 ][ j ] ) &
                    ( num > grid[ i - 1 ][ j - 1 ] ) &
                    ( num > grid[ i ][ j - 1 ] ) &
                    ( num > grid[ i + 1 ][ j - 1 ] ) &
                    (num > grid[ i + 1 ][ j ] ) &
                    ( num > grid[ i + 1 ][ j + 1] ) &
                    ( num > grid[ i ][ j + 1 ] ) &
                    ( num > grid[ i - 1 ][ j + 1 ] ) ) {
                    printf("%d %d\n",i,j);
                }
            }
        }
    }
}

int main()
{
  // Add code to read in the grid size from standard input.
    int rows;
    int cols;
    scanf("%d", &rows);
    scanf("%d", &cols);

  // Declare a variable-sized array to hold the grid.
    int grid[rows][cols];

  // Call readGrid() to populate the array.
    readGrid(rows,cols,grid);
  
  // Call reportMaxima() to print out all local maxima.
    reportMaxima(rows, cols, grid);
  
  return EXIT_SUCCESS;
}
