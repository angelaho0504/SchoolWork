#include <stdio.h>

int main() {
  // Initialize ch to hex 0
  int ch = 0;
  
  // Loop while character read is not a period
  while ( ch != '.' ) {
    
    ch = getchar();             // read char from the keyboard
    
    if ( ch == ' ' ) {          // if the character is a space
    }
    else if ( ch == '.' ) {     // if the character is a period
    }
    else if ( ( ch >= 'A' ) && ( ch <= 'Z' ) ) {        // if the character is a upper case letter
    }
    else if ( ( ch >= 'a' ) && ( ch <= 'z' ) ) {        // if the character is a lower case letter
      ch = ch - 32;             // convert it to upper case
    }
    else {
      continue;
    }
    putchar(ch);              // write it to the display
  }
  return(0);                  // terminate
}
