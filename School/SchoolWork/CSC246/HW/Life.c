/**
   @file Life.c
   @author Angela Ho
   The game of life in a threaded world
   compile with gcc -std=c99 Life.c -lpthread
 */

#include <pthread.h>  //prototypes are here
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>

int **grid;
int **newGrid;
/** struct for the function parameter */
typedef struct {
  int **shareGrid;
  int **newGrid;
  int i;
  int j;
  int M;
  int N;
  
 } thread_param;

/** function to perform in each thread */
void *calculate ( void *args ) {
  
  thread_param *actual_args = args;
  int count_one = 0;
  int i = actual_args->i;
  int j = actual_args->j;
  int M = actual_args->M;
  int N = actual_args->N;
  
  /** check if wrap around needed */
  int i2 = i - 1;
  int i3 = i + 1;
  int j2 = j - 1;
  int j3 = j + 1;
  if (i2 == -1) {
    i2 = M - 1;
  }
  if (i3 == M) {
    i3 = 0;
  }
  if (j2 == -1) {
    j2 = N - 1;
  }
  if (j3 == N) {
    j3 = 0;
  }
  /** count the number of ones in neighbors */
  
  if ( actual_args->shareGrid[ i2 ][j] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[ i3 ][j] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[i][ j2 ] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[i][ j3 ] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[ i2 ][ j2 ] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[ i2 ][ j3 ] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[ i3 ][ j2 ] == 1 ) {
    count_one++;
  }
  
  if ( actual_args->shareGrid[ i3 ][ j3 ] == 1 ) {
    count_one++;
  }

  if ( actual_args->shareGrid[ i ][ j ] == 1 ) {
    if ( count_one > 3 || count_one < 2 ) {
      actual_args->newGrid[ i ][ j ] = 0;
    }
  }
  
  if ( actual_args->shareGrid[ i ][ j ] == 0 ) {
    if ( count_one == 3 ) {
      actual_args->newGrid[ i ][ j ] = 1;
    }
  }
  return 0;
}

int main( int argc, char *argv[] ) {
  
  FILE *fp;
  
  fp = fopen( argv[1], "r" ); // open the input file
  
  int M, N, temp, gen;
  
  // variable for number of generation
  gen = atoi(argv[2]);
  
  
  int count = 0;
  
  // scan the generation
  fscanf(fp, "%d %d\n", &M, &N );
  
  // create 2D array by pointer
  grid = (int **)malloc(M * sizeof(int * ) );
  for (int i = 0; i < M; i++ ) {
    grid[i] = (int *)malloc(N * sizeof( int ) );
  }
  // create 2D array by pointer for new state
  newGrid = (int **)malloc(M * sizeof(int * ) );
  for (int i = 0; i < M; i++ ) {
    newGrid[i] = (int *)malloc(N * sizeof( int ) );
  }
  
  // print the original grid
  printf("Original State:\n");
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      fscanf(fp, "%d", &temp);
      grid[i][j] = temp;
      printf("%d", grid[i][j]);
    }
    printf("\n");
  }
  
  pthread_t thread[M*N];  // an array of thread to be join upon

  for ( int a = 0; a < gen; a++ ) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        thread_param *args = malloc( sizeof *args );   // create the struct that contains the parameter info
        args->shareGrid = grid; // Copy the data into struct
        args->newGrid = newGrid;
        args->i = i;
        args->j = j;
        args->M = M;
        args->N = N;
        pthread_create(&thread[count],NULL, calculate, args);  // create thread
        count++;
      }
    }
    // wait until the thread to be done
    for (int i = 0; i < count; i++) {
      pthread_join(thread[i],NULL);
    }
    /** printing the new state */
    printf("Next State:\n");
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        printf("%d", newGrid[i][j]);
      }
      printf("\n");
    }
    
    /** reset counter and set the original state to new state */
    count = 0;
    grid = newGrid;
  }
  
    return 0;
}
