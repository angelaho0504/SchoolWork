// Code to read numbers from standard input inserting them into a list
// in sorted order as we read them.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node for building our linked list.
struct NodeTag {
  // Value in this node.
  int value;

  // Pointer to the next node.
  struct NodeTag *next;
};

// A short type name to use for a node.
typedef struct NodeTag Node;

/*
  Create a node for the given value and insert it into the given list
  in the proper location to keep the list sorted.  Return an updated
  head pointer.  The head should only need to change if this value gets
  inserted at the front of the list.  Otherwise, you can just return
  the old head pointer.
*/
Node *insert( Node *head, int val )
{
  Node *n = (Node *)malloc( sizeof( Node ) );
  if ( !head || head->value > val) {
    n->value = val;
    n->next = head;
    head = n;
  } else {
    n = head;
    while (n->next!= NULL && n->next->value < val) {
      n = n->next;
      n->value =val;
    }
  }
  return head;
    
}

int main()
{
  // Pointer to the head node.
  Node *head = NULL;

  // Read a list of numbers from building a sorted list as we
  // read them.
  int x;
  while ( scanf( "%d", &x ) == 1 ){
    // Insert the new value, and get back the (possibly updated) head pointer.
    head = insert( head, x );
  }

  // Print out the list.
  for ( Node *n = head; n; n = n->next ) {
    printf( "%d ", n->value );
  }
  
  // Free all the nodes.
  while ( head ) {
    Node *next = head->next;
    free( head );
    head = next;
  }
  
  return 0;
}
