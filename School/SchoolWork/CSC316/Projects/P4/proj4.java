import java.util.*;
import java.io.*;

public class proj4 {
    
    public static int HASH_SIZE = 30577; // prime number and above the dictionary count
    
    public static void main(String[] args) {
        
        Scanner scan = new Scanner(System.in);
        System.out.println("Please provide the dictionary: ");
        String dictionaryFile = scan.next();
        System.out.println("Please provide the file to be spell checked: ");
        String spellCheckFile = scan.next();
        System.out.println("Please provide the output file: ");
        String outputFile = scan.next();
        File dictionary;
        File checkFile;
        File output;
        HashTable table;
        PrintStream ps;
        // Open file for dictionary
        try {
            dictionary = new File(dictionaryFile);
            checkFile = new File(spellCheckFile);
            output = new File(outputFile);
            ps = new PrintStream(output);
            ps.println("Misspelled Word/s: ");
            Scanner scanDictionary = new Scanner(dictionary);
            int dictionaryCount = 0;
            table = new HashTable(HASH_SIZE);
            while( scanDictionary.hasNextLine() ) {
                String word = scanDictionary.nextLine();
                table.insert(word);
                dictionaryCount++;
            }
            
            // scanner for spellcheck
            Scanner scanCheck = new Scanner(checkFile);
            
            int searchResult = 0;
            int spellcheckCount = 0;
            int misspelledCount = 0;
            int totalProbe = 0;
            int numberOfLookUp = 0;
            
            while( scanCheck.hasNextLine() ) {
                Scanner scanCheckLine = new Scanner(scanCheck.nextLine());
                while( scanCheckLine.hasNext()) {
                    
                    String checkWord = scanCheckLine.next();
                    spellcheckCount++;
                    searchResult = table.lookUp(checkWord);
                    numberOfLookUp++;
                    totalProbe += table.getProbeNum();

                    if ( searchResult == -1 ){
                        checkWord = checkWord.substring(0,1).toLowerCase() + checkWord.substring(1);
                        searchResult = table.lookUp(checkWord);
                        totalProbe += table.getProbeNum();
                        numberOfLookUp++;
                        if ( searchResult == -1) {
                            if (checkWord.length() > 2) {
                                if ( checkWord.substring(checkWord.length()-2).equals("'s")) {
                                String newCheckWord = checkWord.substring(0,checkWord.length()-2);
                                searchResult = table.lookUp(newCheckWord);
                                totalProbe += table.getProbeNum();
                                numberOfLookUp++;
                                }
                            }
                            if ( searchResult == -1) {
                                if ( checkWord.substring(checkWord.length()-1).equals("s")) {
                                    String newCheckWord = checkWord.substring(0,checkWord.length()-1);
                                    searchResult = table.lookUp(newCheckWord);
                                    totalProbe += table.getProbeNum();
                                    numberOfLookUp++;
                                }
                            }
                            if (checkWord.length() > 2) {
                                if ( searchResult == -1) {
                                    if ( checkWord.substring(checkWord.length()-2).equals("ed")) {
                                    String newCheckWord = checkWord.substring(0,checkWord.length()-2);
                                    searchResult = table.lookUp(newCheckWord);
                                    totalProbe += table.getProbeNum();
                                    numberOfLookUp++;
                                    }
                                }
                            }
                            if (checkWord.length() > 2) {
                                if ( searchResult == -1) {
                                    if ( checkWord.substring(checkWord.length()-2).equals("er")) {
                            
                                    String newCheckWord = checkWord.substring(0,checkWord.length()-2);
                                    searchResult = table.lookUp(newCheckWord);
                                    totalProbe += table.getProbeNum();
                                    numberOfLookUp++;
                                 }   
                                }
                            }
                            if (checkWord.length() > 3) {
                                if ( searchResult == -1) {
                                    if ( checkWord.substring(checkWord.length()-3).equals("ing")) {
                                        String newCheckWord = checkWord.substring(0,checkWord.length()-3);
                                        searchResult = table.lookUp(newCheckWord);
                                        totalProbe += table.getProbeNum();
                                        numberOfLookUp++;
                                    }
                                }
                            }
                            if (checkWord.length() > 2) {
                                if ( searchResult == -1) {
                                    if ( checkWord.substring(checkWord.length()-2).equals("ly")) {
                                        String newCheckWord = checkWord.substring(0,checkWord.length()-2);
                                        searchResult = table.lookUp(newCheckWord);
                                        totalProbe += table.getProbeNum();
                                        numberOfLookUp++;
                                    }
                                }
                            }
                            
                            if ( searchResult == -1) {
                                ps.println(checkWord);
                                misspelledCount++;
                            }
                        }
                    }
                }
            }
            ps.println();
            ps.println("Number of words in the dictionary:" + dictionaryCount);
            ps.println("Number of the text to be spell-checked: " + spellcheckCount);
            ps.println("Number of misspelled words: " + misspelledCount);
            ps.println("Number of probes during the checking phase: " + totalProbe);
            ps.printf("Average number of probes per word: %.2f\n", ((double)totalProbe/spellcheckCount));
            ps.printf("Average number of probes per lookup operation: %.2f\n", ((double)totalProbe / numberOfLookUp));
        }catch ( FileNotFoundException e) {
            System.out.println("File cannot be open");
        }
        

        // scanner for dictionary and insert to hashtable
        
    }
}

class HashTable {
    private int TABLE_SIZE;
    private String[] table;
    private int primeSize;
    private int numOfProbe;
    
    public HashTable(int tableSize) {
        
        TABLE_SIZE = tableSize;
        table = new String[TABLE_SIZE];
        
        for( int i = 0; i < TABLE_SIZE; i++ ){
            table[i] = null;
        }
        
    }
    
    public void insert( String word ) {
        
        int firstH = firstHash(word);
        int secondH = secondHash(word);
        // collision
        if ( table[firstH] != null ) {
            int i = 1;
            while(true) {
                int newIndex = ( firstH + i * secondH) % TABLE_SIZE;
                
                if( table[newIndex] == null) {
                    table[newIndex] = word;
                    break;
                }
                i++;
            }
        } else {
            table[firstH] = word;
        }
    }
    
    public int lookUp(String word) {
        numOfProbe = 0;
        int firstH = firstHash(word);
        int secondH = secondHash(word);
        int index = firstH;
        int i = 1;
        
        while( table[index] != null && !table[index].equals(word)) {
            index = (index + i * secondH ) % TABLE_SIZE;
            numOfProbe++;
        }
        
        if ( numOfProbe == 0) {
            numOfProbe++;
        }
        if ( table[index] != null && table[index].equals(word)) {
            return 1;
        } else {
            return -1;
        }
    }
    
    public int getProbeNum() {
        return numOfProbe;
    }
    
    public int firstHash(String word) {
        int key = word.hashCode() & 0xfffffff;
        int hashKey = key % TABLE_SIZE;
        
        return hashKey;
    }
    
    public int secondHash(String word) {
        int key = word.hashCode() & 0xfffffff;
        int hashKey = 3 - ( key % 3);
        
        return hashKey;
    }
}
