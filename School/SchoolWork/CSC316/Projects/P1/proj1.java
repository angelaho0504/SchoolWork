import java.util.*; // Scanner class

/**
 */
public class proj1 {
  
  /** starting point of proj1 */
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    LinkedList list = new LinkedList();
    int position;
    int token;
    if ( !scan.hasNextInt() ) {
      System.out.print("0 ");
      // scan line by line
      while(  scan.hasNextLine() ) {
        Scanner scanWord = new Scanner(scan.nextLine());
        // scan word by word
        while ( scanWord.hasNext() ) {
          
          String str = scanWord.next();
          
          char special = str.charAt(str.length()-1);
          
          // if there is a special character
          if ( special == '.' || special == ',' || special == '/'|| special == '%'
              || special == '&' || special == '!' || special == '@' || special == '#'|| special == '$'|| special == '?' || special == '-' || special == '_' || special == '>'|| special == '<'|| special == '(' || special == ')' || special == '[' || special == ']'|| special == '\t'|| special == ';') {

            str = str.substring(0,str.length()-1);

            position = list.lookUp(str);
            
            if ( position == 0 ) {
              list.insert(str);
              System.out.print(str+special);
            } else {
              System.out.print(position+""+special);
            }
            if ( scanWord.hasNext()) {
              System.out.print(" ");
            }
          }
          else {
            position = list.lookUp(str);

            if  ( position == 0 ) {
              list.insert(str);
              
              System.out.print(str);
            } else {
              System.out.print(position);
            }
            if ( scanWord.hasNext()) {
              System.out.print(" ");
            }
          }
        }
        System.out.println();
      }
    } else {
      scan.next();
      while ( scan.hasNextLine() ) {
        Scanner scanWord = new Scanner(scan.nextLine());
        while ( scanWord.hasNext() ) {
          
          if ( scanWord.hasNextInt() ) {
            int num = scanWord.nextInt();
            String str = list.getString(num);
            list.lookUp(str);
            System.out.print(str);
            if ( scanWord.hasNext()) {
              System.out.print(" ");
            }
          } else {
            String str = scanWord.next();
            char special = str.charAt(str.length()-1);
            if ( special == '.' || special == ',' || special == '/'|| special == '%'
                || special == '&' || special == '!' || special == '@' || special == '#'|| special == '$'|| special == '?' || special == '-' || special == '_' || special == '>'|| special == '<'|| special == '(' || special == ')' || special == '[' || special == ']'|| special == '\t'|| special == ';') {
              str = str.substring(0,str.length()-1);
              Scanner scanInt = new Scanner(str);
              if ( scanInt.hasNextInt()) {
                int num = scanInt.nextInt();
                str = list.getString(num);
                list.lookUp(str);
                System.out.print(str + special);
                if ( scanWord.hasNext()) {
                  System.out.print(" ");
                }
              } else {
                list.insert(str);
                list.lookUp(str);
                System.out.print(str + special);
                if ( scanWord.hasNext()) {
                  System.out.print(" ");
                }
              }
            }else {
              list.insert(str);
              list.lookUp(str);
              System.out.print(str);
              if ( scanWord.hasNext()) {
                System.out.print(" ");
              }
            }
          }
        }
          System.out.println();
      }
    }
  }

  /**
   * Implemented Linked List inner class
   */
  static class LinkedList {
    Node head;
    Node tail;
    
    /**
     * inner class node for linkedlist
     */
    private class Node {
      String str;
      Node next;
    
      // Constructor of the node
      Node(String s) {
        str = s;
        next = null;
      }
    }
  
    /** insert the new element to front of the list
     * @param str the string to insert the linked list
     */
    public void insert(String str) {
    
      Node temp = new Node(str);
    
      if( head == null) {
        head = temp;
        tail = temp;
      }
      else {
        Node n = new Node(str);
        n.next = head;
        head = n;
      }
    }
    
    /**
     * Look up the key string in the linked list, return the number's position
     * if not found else return 0
     * @param key the string to lookup in the linked list
     * @return count the position of the number in the linked list
     */
    public int lookUp(String key) {
      Node current = head;
      int count = 0;
      Node prev = null;
    
      while( current != null) {
        count ++;
        if ( current.str.equals(key)) {
          if ( prev != null ) {
            prev.next = current.next;
            current.next = head;
            head = current;
          }
          return count;
        }
        prev = current;
        current = current.next;
      }
      return 0;
    }
    
    /**
     *
     */
    public String getString(int index) {
      Node temp = head;
      
      // sequentially displaying nodes
      while (index > 1) {
        // incrementing node pointer.
        temp = temp.next;
        index --;
      }
      return temp.str;
      
    }
    
    /**
     * Print the list out
     */
    public void printList() {
    
      if ( head == null ) {
        System.out.println("Nothing to print");
        return;
      }
      Node temp = head;
    
      // sequentially displaying nodes
      while (temp != null) {
        System.out.println(temp.str);
      
        // incrementing node pointer.
          temp = temp.next;
      }
    }
  }
}
