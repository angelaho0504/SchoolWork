/**
    @file textbox.c
    @author Angela Ho (aho)
    Print text from standard input with border around the text.
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Width of each line of text in the box. */
#define LINE_WIDTH 60
/** Symbol used to draw the border around the box. */
#define BORDER '*'

/**
    Reads and prints single line of text inside the border. Extra spaces
    will be added at the end to make the box rectangular if the line of
    text isn't long enough. Additional characters will be discarded to
    keep the box rectangular.
    @return false if there's no line of text to print, otherwise return true.
  */
bool paddedLine()
{
    int ch = getchar();
    int count = 0;
    if ( ch == EOF ){
        return 0;
    }
    putchar(BORDER);
    while ( ch != '\n' ){
        if( count < LINE_WIDTH ) {
            putchar(ch);
        }
        ch = getchar();
        count ++;
    }
    while ( count < LINE_WIDTH ){
        printf(" ");
        count++;
    }
    putchar( BORDER );
    return 1;
}

/**
    Prints out multiple copies of given character, followed by a newline.
    @param ch given character to print
    @param count number of copies
  */
void lineOfChars( char ch, int count )
{
    putchar( BORDER );
    putchar( BORDER );
    int pos = 0;
    int symbol = ch;
    while ( pos < count ){
        putchar( symbol );
        pos++;
    }
    printf( "\n" );
}

/**
    Program starting point, creates a border around a text.
    @return program exist status
  */
int main()
{
    lineOfChars( BORDER, LINE_WIDTH  );
    
    while( paddedLine() == 1 ){
        printf( "\n" );
    }
    lineOfChars( BORDER, LINE_WIDTH );
    return EXIT_SUCCESS;
}
