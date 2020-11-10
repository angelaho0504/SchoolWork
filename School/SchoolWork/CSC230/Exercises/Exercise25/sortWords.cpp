#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Read words from cin into the given vector of strings.
void readWords( vector < string > &list )
{
  string word;
  
  while( cin >> word ) {
    list.push_back(word);
  }
  
}

// Use the index operator ( you know, [] ) to print out the list
// of words in reverse.
void printBackward( vector < string > &list )
{
  cout << "-- Backward --" << endl;
  for ( int i = list.size() - 1 ; i >= 0 ; i -- ) {
    cout << list[i] << endl;
  }
}

// Use iteratros to print the list forward.
void printForward( vector < string > &list )
{
  cout << "-- Forward --" << endl;
  vector < string > :: iterator p;
  for ( p = list.begin(); p != list.end(); p++ ) {
    cout << *p  << endl;
  }
}

int main()
{
  // You can make a vector of strings.  Why not.
  vector< string > words;

  // Read a list of words.
  readWords( words );

  // Use a template algorithm to sort them.
  sort(words.begin(), words.end() );

  // Print the list backward.
  printBackward( words );

  // Then print it again, forward this time.
  printForward( words );
}
