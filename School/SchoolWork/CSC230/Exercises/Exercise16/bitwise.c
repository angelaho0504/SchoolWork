/**
    @file bitwise.c
    @author Angela Ho
    Accomplish simple bit manipulation tasks.
 */
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

/*
 * Clear the 6 high-order bits of the given short value, return the result.
 */
unsigned short clear6( unsigned short v )
{
  v = v & 0x03FF;
  return v;
}

/*
 * Set the low-order 9 bits of the given short value, passed by address.
 */
void set9( unsigned short *v )
{
  *v = *v | 0x01FF;
}

/*
 * Set just bit 7 (counting from low-order bit zero) to 1 if flag is true.
 * clear it otherwise.
 */
void set7( unsigned short *v, bool flag )
{
  if( flag == 1 ) {
    *v = *v | 0x0080;
  } else {
    *v = *v & 0xFF7F;
  }
}

int main()
{
  // Try out our functions.  Don't change any of the lines below.  My test program may
  // automatically modify this part of your source code when it tests your implementation.

  printf( "----- clear6 -----\n" );
  
  //111111111111 -> 0000001111111111 (1111111100000011)
  printf( "%04x\n", clear6( 0xFFFF ) );
  // 000000000000 -> 0000000000000000
  printf( "%04x\n", clear6( 0x0000 ) );
  // 1010001101111101 -> 0000001101111101 (0000001010001101)
  printf( "%04x\n", clear6( 0xA37D ) );
  // 0100011010011110 -> 0000001010011110
  printf( "%04x\n", clear6( 0x469E ) );

  printf( "----- set9 -----\n" );

  // For the next two functions, we need a real variable.
  unsigned short v;
  
  v = 0xFFFF;
  set9( &v );
  printf( "%04x\n", v );

  v = 0x0000;
  set9( &v );
  printf( "%04x\n", v );

  v = 0xB842;
  set9( &v );
  printf( "%04x\n", v );

  v = 0x19C0;
  set9( &v );
  printf( "%04x\n", v );

  printf( "----- set7 -----\n" );

  v = 0xFFFF;
  set7( &v, 0 );
  printf( "%04x\n", v );

  v = 0x0000;
  set7( &v, 1 );
  printf( "%04x\n", v );

  v = 0x5A70;
  set7( &v, 1 );
  printf( "%04x\n", v );

  v = 0x4F96;
  set7( &v, 1 );
  printf( "%04x\n", v );

  return 0;
}
