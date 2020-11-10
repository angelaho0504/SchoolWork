#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream input( "numbers.txt");
  
  int total = 0;
  int val;
  while ( input >> val ) {
    total = total + val;
  }
  cout << "Total: " << total << endl;
}
