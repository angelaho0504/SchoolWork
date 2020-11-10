import java.util.*;
import java.io.*;
import java.lang.*;

public class proj3 {
    
    static LinkedList<Integer> adjList[];
    static Edge[] heap;
    static Edge[] edge;
    public static final int MAX_EDGE = 5000;
    static int heapSize = 0;
    static int counter = 0;
    static int xCount = 0;
    static int yCount = 0;
    
    @SuppressWarnings("unchecked")
    public static void main (String[] args) {
        
        Scanner scan = new Scanner(System.in);
        System.out.println("Input Filename: ");
        String inputFilename = scan.next();
        System.out.println("Output Filename: ");
        String outputFilename = scan.next();
        int numberOfVertex = 0;
        int numberOfEdge = 0;
        try {
            File inputFile = new File(inputFilename);
        
            numberOfVertex = countVertex(inputFile);
            
            // Create an array of LinkedList
            adjList = new LinkedList[numberOfVertex];
            
            // Create array for heap and set the first val to smallest val
            heap = new Edge[MAX_EDGE];
            heap[0] = new Edge(Integer.MIN_VALUE, Integer.MIN_VALUE, Integer.MIN_VALUE);
            
            
            for( int i = 0; i < numberOfVertex; i++ ) {
                adjList[i] = new LinkedList<>();
            }
            
            Scanner input = new Scanner(inputFile);
        
            while( input.hasNextLine() ) {
                String line = input.nextLine();
                Scanner inputLine = new Scanner(line);
                // scan the vertices and construct an edge for it
                int vertex1 = inputLine.nextInt();
                if( vertex1 == -1 ) {
                    break;
                }
                int vertex2 = inputLine.nextInt();
                double weight = inputLine.nextDouble();
                Edge edge = new Edge(vertex1, vertex2, weight);
                insert(edge);
                addEdge(vertex1,vertex2);
                numberOfEdge++;
            }
        } catch ( FileNotFoundException e) {
            System.out.println("Cannot open file");
        }
        
        try {
            File outputFile = new File(outputFilename);
            PrintStream print = new PrintStream(outputFile);
            printHeap(print);
            createKruskalMST(numberOfVertex, numberOfEdge,print);
            printgraph(print, numberOfVertex);
        } catch ( FileNotFoundException e ) {
            System.out.println("Cannot open file");
        }
        
    }
    /**
     * This method calculates the number of vertex in the graph
     * @param f the input file
     * @return the number of vertex in the graph
     */
    public static int countVertex(File f){
        int vertexArray[] = new int[1000];
        int numberOfVertex = 0;
        boolean contain = false;
        try{
            Scanner scan = new Scanner(f);
            while(scan.hasNextLine()) {
                String line = scan.nextLine();
                Scanner scanLine = new Scanner(line);
                int vertex = scanLine.nextInt();
                if ( vertex == -1 ) {
                    break;
                }
                for ( int i = 0; i < numberOfVertex; i++ ) {
                    if ( vertex == vertexArray[i]) {
                        contain = true;
                    }
                }
                if (contain == false) {
                    vertexArray[numberOfVertex] = vertex;
                    numberOfVertex++;
                }
                vertex = scanLine.nextInt();
                contain = false;
                for ( int i = 0; i < numberOfVertex; i++ ) {
                    if ( vertex == vertexArray[i]) {
                        contain = true;
                    }
                }
                if (contain == false) {
                    vertexArray[numberOfVertex] = vertex;
                    numberOfVertex++;
                }
            }
            return numberOfVertex;
        } catch (FileNotFoundException e ) {
            System.out.println("Cannot open file");
        }
        return numberOfVertex;
    }
    
    /**
     * add edge to the adjacency list
     * @param src
     */
    public static void addEdge(int src, int dest) {
        adjList[src].add(dest);
        adjList[dest].add(src);
    }
    
    public static void printgraph(PrintStream print, int numberOfVertex) {
        for (int i = 0; i < numberOfVertex; i++ ) {
            Collections.sort(adjList[i]);
        }
        
        for (int i = 0; i < numberOfVertex ; i++) {
            if(adjList[i].size()>0) {
                for (int j = 0; j < adjList[i].size(); j++) {
                    print.printf("%4d ",adjList[i].get(j));
                }
                print.println();
            }
        }
    }
    
    public static void swap(int first, int second) {
        Edge tmp;
        tmp = heap[first];
        heap[first] = heap[second];
        heap[second] = tmp;
    }
    
    public static void insert(Edge e) {
        heap[heapSize] = e;
        heapSize++;
        upHeap(heapSize-1);
    }
    
    public static Edge deleteMin() {
        Edge x = heap[0];
        heapSize--;
        swap(0, heapSize);
        downHeap(0);
        return x;
    }
    
    public static void downHeap(int pos) {
        int i = 0;
        if ( (2*pos) + 2 < heapSize ) {
            if ( heap[2*pos+2].getWeight() <= heap[2*pos+1].getWeight()) {
                i = 2*pos+2;
            }
            else {
                i = (2*pos) + 1;
            }
        }
        else if ( (2*pos) + 1 < heapSize) {
            i = (2*pos) + 1;
        }
        if((i > 0) && (heap[pos].getWeight() > heap[i].getWeight())){
            swap(pos, i);
            downHeap(i);
        }
    }
    public static void upHeap(int pos) {
        
        if ( pos > 0 ) {
            if (heap[(pos-1) / 2].getWeight() > heap[pos].getWeight()) {
                swap((pos - 1)/2, pos);
                upHeap((pos-1)/2);
            }
        }
    }
    
    public static boolean isLeaf(int pos) {
        if ( pos >= (heapSize / 2) && pos <= heapSize ) {
            return true;
        }
        return false;
    }
    
    public static void printHeap(PrintStream print) {
        for ( int i = 0; i < heapSize ; i++ ) {
            int vertex1 = Math.min(heap[i].getVertex1(), heap[i].getVertex2());
            int vertex2 = Math.max(heap[i].getVertex1(), heap[i].getVertex2());
            print.printf("%4d %4d", vertex1, vertex2);
            print.println();
        }
    }
    
    /**
     * make root of one set point to root of the other
     */
    public static void union(int parent[], int size[], int x, int y) {
        
        int xSet = find(parent, x);
        xCount = counter;
        counter = 0;
        int ySet = find(parent, y);
        yCount = counter;
        counter = 0;
        
        if ( xCount >= yCount) {
            parent[ySet] = xSet;
            xCount += yCount;

        } else {
            parent[xSet] = ySet;
            yCount += xCount;
        }
    }
    
    /**
     * Find the root of the tree
     */
    public static int find ( int parent[] ,int v) {
        counter++;
        if ( parent[v] == v ) {
            return v;
        }
        return find(parent, parent[v]);
    }
    
    public static void createKruskalMST(int numberOfVertex, int numberOfEdge, PrintStream print) {
        ArrayList<Edge> mst = new ArrayList<>();
        
        int [] parent = new int[numberOfVertex];
        int [] size = new int [numberOfVertex];
        
        for ( int i = 0; i < numberOfVertex; i++ ) {
            parent[i] = i;
            size[i] = 1;
        }
        

        int components = numberOfVertex;
        while ( components > 1) {
            Edge edge = deleteMin();
            System.out.println(edge.getWeight());
            int firstSet = find(parent, edge.getVertex1());
            int secondSet = find(parent, edge.getVertex2());

            if(firstSet != secondSet) {
                union(parent,size,firstSet,secondSet);
                mst.add(edge);
                components--;
            }
        }
        printMST(mst, numberOfEdge, print);
    }
    
    public static void printMST(ArrayList<Edge> edges, int numberOfEdge, PrintStream print) {
        for ( int i = 0; i < edges.size(); i ++ ) {
            Edge edge = edges.get(i);
            int vertex1 = Math.min(edge.getVertex1(), edge.getVertex2());
            int vertex2 = Math.max(edge.getVertex1(), edge.getVertex2());
            print.printf("%4d %4d", vertex1, vertex2);
            print.println();
        }
    }
}
class Edge {
    int vertex1;
    int vertex2;
    double weight;
    Edge next;
    
    Edge(int v1, int v2, double w) {
        vertex1 = v1;
        vertex2 = v2;
        weight = w;
        next = null;
    }
    
    public double getWeight() {
        return weight;
    }
    public int getVertex1() {
        return vertex1;
    }
    public int getVertex2() {
        return vertex2;
    }
}


