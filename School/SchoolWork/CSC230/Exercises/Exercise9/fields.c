#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/**
 Starting point of the program. Read in the input.txt file
 and output the file with specified format.
 */
int main()
{
  // Open the input file and print an error message if we're unsuccessful.
  // (the error message is mostly to help you with debugging.  We won't test
  // this behavior).
  // ...
  FILE *fp;
  fp = fopen("input.txt","r");
  if ( !fp ) {
    fprintf( stderr, " Unable to open input file.\n" );
    exit(1);
  }
  char first[50];
  char last[50];
  char email[50];
  char atChar[50];
  char capLetters[50];
  char digit1[50];
  char digit2[50];
  char digit3[50];
  float mark;

  // Counting input lines, so we can report errors.
  int lineCount = 1;
 
  // Keep reading input lines until we reach the end-of-file.
  // Write an output line or an error message for each one.
  // ...
  do {
    fscanf(fp, "%11s", first );
    fscanf( fp, "%11s", last );
    fscanf( fp, "%*d " );
    fscanf( fp, "%[a-z]", email );
    fscanf( fp, "%1c%*[a-z.]", atChar );
    fscanf( fp, "%[A-Z^ ]", capLetters);
    fscanf( fp, "%3c - %3c - %4c", digit1, digit2, digit3 );
    fscanf(fp, "%*[^\n]");
    int c = strlen(capLetters);
    if ( atChar[0] != '@' ) {
      fprintf(stderr, "Invalid input, line %d\n" , lineCount );
    } else if ( c == 1 ) {
      fprintf(stderr, "Invalid input, line %d\n" , lineCount );
    } else {
      printf("%8s %11s %11s (%s)%s-%s\n", email, first, last, digit1, digit2, digit3);
    }
    lineCount++;
  } while ( fscanf(fp, "%f\n", &mark) != EOF );
  fclose(fp);
    return EXIT_SUCCESS;
}

