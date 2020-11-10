import java.util.*;
import java.io.*;
import java.lang.*;

public class proj2 {
  
  public static int MAX_CHAR = 256;
  
  public static char[] pretrav = new char[MAX_CHAR];
  public static char[] posttrav = new char[MAX_CHAR];
  public static int pathA = 0;
  public static int pathB = 0;
  public static int traversed = 0;
  public static int totalElem = 0;
  public static int counter = 0;

  public static void main(String[] args) {
    
    System.out.println("Input File Name: ");
    Scanner scanPrompt = new Scanner(System.in);
    String inputFile = scanPrompt.nextLine();
    File file = new File(inputFile);
    System.out.println("Output File Name: ");
    String outputFile = scanPrompt.nextLine();
    int preCounter = 0;
    int postCounter = 0;
    char starter = ' ';
    try {
      Scanner scanFile = new Scanner(file);
      while(scanFile.hasNextLine()) {
        String line = scanFile.nextLine();
        Scanner scanChar = new Scanner(line);

        if ( scanChar.hasNext()) {
          starter = scanChar.next().charAt(0);
        }
        // if line start with < store the charcters in pretrav array
        if ( starter == '<') {
          while( scanChar.hasNext()) {
            char ch = scanChar.next().charAt(0);
            pretrav[preCounter] = ch;
            preCounter++;
          }
        }
        // if line start with > store the charcters in posttrav array
        if (starter == '>') {
          while( scanChar.hasNext()) {
            char ch = scanChar.next().charAt(0);
            posttrav[postCounter] = ch;
            postCounter++;
          }
          break;
        }
        totalElem = preCounter;
      }
      Node root = buildTree(totalElem,0, 0);
      
      PrintWriter writer = new PrintWriter(outputFile);

      while(scanFile.hasNextLine()) {

        String line = scanFile.nextLine();
        Scanner scanChar = new Scanner(line);

        if ( scanChar.hasNext()) {
          starter = scanChar.next().charAt(0);
        }

        if (starter == '?') {

          while( scanChar.hasNext()) {

            char a = scanChar.next().charAt(0);
            char b = scanChar.next().charAt(0);
            
            pathA = 0;
            pathB = 0;
            
            markFirstAncestors(root, a);
            findFirstMark(root,b);
            findCommonA(root,a);
            findCommonB(root,b);

              if (pathA == 0 && pathB == 0) {
                writer.println(a + " is " + b + ".");
              }
              else if (pathA == 0 && pathB == 1) {
                writer.println(a + " is " + b + "'s parent.");
              }
              else if (pathA == 0 && pathB == 2) {
                writer.println(a + " is " + b + "'s grandparent.");
              }
              else if (pathA == 0 && pathB == 3) {
                writer.println(a + " is " + b + "'s great-grandparent.");
              }
              else if (pathA == 0 && pathB > 3) {
                writer.println(a + " is " + b + "'s (great)^"+ (pathB-2)+ "-grandparent.");
              }
              else if (pathA == 1 && pathB == 0) {
                writer.println(a + " is " + b + "'s child.");
              }
              else if (pathA == 2 && pathB == 0) {
                writer.println(a + " is " + b + "'s grandchild.");
              }
              else if (pathA >= 3 && pathB == 0) {
                writer.println(a + " is " + b + "'s (great)^"+ (pathB-2)+ "-grandchild.");
              }
              else if (pathA == 1 && pathB == 1) {
                writer.println(a + " is " + b + "'s sibling.");
              }
              else if (pathA == 1 && pathB == 2) {
                writer.println(a + " is " + b + "'s aunt/uncle.");
              }
              else if (pathA == 1 && pathB >= 2) {
                writer.println(a + " is " + b + "'s (great)^"+ (pathB-2)+ "-aunt/uncle.");
              }
              else if (pathA == 2 && pathB == 1) {
                writer.println(a + " is " + b + "'s niece/nephew.");
              }
              else if (pathA >= 2 && pathB == 1) {
                writer.println(a + " is " + b + "'s (great)^"+ (pathB-2)+ "-niece/nephew.");
              }
              else if (pathA >= 2 && pathB >= 2) {
                writer.println(a + " is " + b + "'s " + ((Math.min(pathB,pathA))-1) + "th cousin " + Math.abs(pathA-pathB) + " times removed.");
              }
              unMarkAll(root);
          }
        }
      }
      writer.close();
      
      char[] charArray = new char[totalElem];
      levelOrder(root, charArray);
      for( int i = 0; i < totalElem; i++ ) {
        writer.print(charArray[i]);
        if ( i < totalElem -1){
          writer.print(", ");
        }
      }
      writer.println(".");
      writer.close();
    }
    catch( FileNotFoundException e) {
      e.printStackTrace();
    }
    
  }
  public static void levelOrder(Node p, char[] arr) {
    Queue<Node> q = new LinkedList<>();
    if (p == null) {
      return;
    }
    q.add(p);
    int count = 0;
    while(!q.isEmpty()) {
      Node d = q.remove();
      arr[count] = d.getChar();
      count++;
      int i = 0;
      while(d.getNumberOfChildren() > 0 && i < d.getNumberOfChildren()) {
        Node r = d.getChildNode(i);
        q.add(r);
        i++;
      }
    }
  }
  public static boolean markFirstAncestors(Node root, char a ) {
    
      if ( root.getChar() != a ) {
        if ( root.getNumberOfChildren() > 0 ) {
          for ( int i = 0; i < root.getNumberOfChildren(); i++ ) {
            Node newRoot = root.getChildNode(i);
            if (markFirstAncestors(newRoot, a)) {
              root.markAncestor();
              return true;
            }
          }
        }
      }
      else {
        root.markAncestor();
        return true;
      }
      return false;
  }
   
  public static boolean findFirstMark(Node root, char b ) {
    
    if ( root.getChar() != b ) {
      if ( root.getNumberOfChildren() > 0 ) {
        for ( int i = 0; i < root.getNumberOfChildren(); i++ ) {
          Node newRoot = root.getChildNode(i);
          if (findFirstMark(newRoot, b)) {
            if ( root.getMarkVal() == 1 ) {
              root.markB();
              return false;
            }
            return true;
          }
        }
      }
    }
    else {
      if ( root.getMarkVal() == 1) {
        root.markB();
        return false;
      }
      return true;
    }
    return false;
  }

  public static boolean findCommonA( Node root, char a) {
    if ( root.getChar() != a ) {
      if ( root.getNumberOfChildren() > 0 ) {
        for ( int i = 0; i < root.getNumberOfChildren(); i++ ) {
          Node newRoot = root.getChildNode(i);
          if (findCommonA(newRoot, a)) {
            pathA++;
            if ( root.getMarkB() == 1) {
              return false;
            }
            return true;
          }
        }
      }
    }
    else {
      if ( root.getMarkB() == 1) {
        return false;
      }
      return true;
    }
    return false;
  }

  public static boolean findCommonB( Node root, char a) {
    if ( root.getChar() != a ) {
      if ( root.getNumberOfChildren() > 0 ) {
        for ( int i = 0; i < root.getNumberOfChildren(); i++ ) {
          Node newRoot = root.getChildNode(i);
          if (findCommonB(newRoot, a)) {
            pathB++;
            if ( root.getMarkB() == 1) {
              return false;
            }
            return true;
          }
        }
      }
    }
    else {
      if ( root.getMarkB() == 1) {
        return false;
      }
      return true;
    }
    return false;
  }
  
  public static void unMarkAll(Node root) {
    root.unMarkAncestor();
    root.unMarkB();
    if ( root.getNumberOfChildren() > 0 ){
      for ( int i = 0; i < root.getNumberOfChildren(); i++ ) {
        Node newRoot = root.getChildNode(i);
        unMarkAll(newRoot);
      }
    }
  }
  
  public static Node buildTree(int size,int prestart, int poststart) {

    Node root = new Node(pretrav[prestart]);
    traversed++;
    prestart++;
    
    int remain = size;

    while( remain > 0 && prestart < totalElem) {
      int newSize = 0;
      for ( int i = poststart; i < totalElem; i++ ) {
        newSize++;
        if ( pretrav[prestart] == posttrav[i]) {
          break;
       }
     }
     remain = size - newSize - traversed;
     //System.out.println("newSize" + newSize);
     //System.out.println(remain);
     if ( newSize == 1) {
       for ( int i = 0; i < size - 1; i++ ) {
         Node child = new Node(pretrav[prestart+i]);
         traversed++;
         root.addChild(child);
       }
      return root;
    }

    root.addChild(buildTree(newSize, prestart, poststart));
    prestart += newSize;
    //System.out.println("prestart"+prestart);
    poststart += newSize;
    //System.out.println("poststart"+poststart);

  }
      return root;
    }
  }

class Node {
  char key;
  ArrayList<Node> children;
  int mark = 0;
  int markB = 0;
  
  Node(char ch) {
    this.key = ch;
    this.children = new ArrayList<Node>();
  }
  public void addChild(Node n) {
    children.add(n);
  }
  public char getChar() {
    return key;
  }
  
  public void markAncestor() {
    mark = 1;
  }
  public void unMarkAncestor() {
    mark = 0;
  }
  
  public void markB() {
    markB = 1;
  }
  public void unMarkB() {
    markB = 0;
  }
  
  public Node getChildNode(int i) {
    return children.get(i);
  }
  
  public int getNumberOfChildren() {
    return children.size();
  }
  public int getMarkVal() {
    return mark;
  }
  
  public int getMarkB() {
    return markB;
  }
}