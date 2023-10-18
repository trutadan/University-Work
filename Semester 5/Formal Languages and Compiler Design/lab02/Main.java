import java.util.NoSuchElementException;

public class Main {
    public static void main(String[] args) {
        SymbolTable symbolTable = new SymbolTable(5);

        // Add symbols to the SymbolTable
        symbolTable.add("apple");
        symbolTable.add("banana");
        symbolTable.add("cherry");

        // Run tests on the HashTable through the SymbolTable
        testHashTable(symbolTable);

        System.out.println(symbolTable);
    }

    public static void testHashTable(SymbolTable symbolTable) {
        // Get and test elements from the HashTable using the SymbolTable

        // Test if elements exist
        System.out.println("Does 'apple' exist? " + symbolTable.exists("apple"));
        System.out.println("Does 'banana' exist? " + symbolTable.exists("banana"));
        System.out.println("Does 'grape' exist? " + symbolTable.exists("grape"));

        // Test getting elements by position
        Pair<Integer, Integer> positionApple = symbolTable.search("apple");
        Pair<Integer, Integer> positionCherry = symbolTable.search("cherry");

        System.out.println("Position of 'apple': " + positionApple);
        System.out.println("Position of 'cherry': " + positionCherry);

        // Test adding duplicate symbol
        Pair<Integer, Integer> position1 = symbolTable.add("apple");
        Pair<Integer, Integer> position2 = symbolTable.add("apple");

        System.out.println("Position of the first 'apple': " + position1);
        System.out.println("Position of the second 'apple': " + position2);

        System.out.println(symbolTable);

        // Test removing elements
        try {
            symbolTable.remove("apple");
            // This will throw NoSuchElementException
            symbolTable.remove("grape");
        } catch (NoSuchElementException e) {
            System.out.println("Caught NoSuchElementException: " + e.getMessage());
        }
    }
}
