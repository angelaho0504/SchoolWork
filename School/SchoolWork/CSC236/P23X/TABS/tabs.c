int main ( int argc, char argv[] ) {
  
  int ch=0;
  int tabNum = 0;
  int count = 0;
  
  if ( argc == 2 ) {
    tabNum = atoi(argv[1]);
  } else {
    tabNum = 10;
  }
  
  while(1) {
    ch = getchar();
    if ( ch == EOF) {
      break;
    }
    if (ch == 9 ) {
      for(int i = 0; i < tabNum-count; i ++ ){
        putchar(32);
      }
      count = 0;
    }else {
      putchar(ch);
    }
    count++;
    if (ch == 13) {}                             // Ignore the CR
    if (ch == 10)                                // If LF then ...
    {                                         //  start EOL processing
      printf("end of line");                    // print message
      putchar (13);                             // put CR  This is EOL
      putchar (10);                             // put LF   for the message
      putchar (13);                             // put CR  This is
      putchar (10);                             // put LF   a blank line
      count = 0;
    }
  }
  putchar (26);                                  // C detected EOF so ...
  return(0);
}
