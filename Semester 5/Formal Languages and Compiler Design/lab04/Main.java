public class Main {
    public static void runScanner(String inputFile, String programInternalFormOutputFile, String symbolTableOutputFile) {
        System.out.println(inputFile + ":");
        LexicalAnalyzer scanner = new LexicalAnalyzer(inputFile, programInternalFormOutputFile, symbolTableOutputFile);
        scanner.scan();
        System.out.println();
    }

    public static void processFiniteAutomataFromFile(String fileName) {
        FiniteAutomata finiteAutomata = new FiniteAutomata();
        finiteAutomata.initializeElements(fileName);

        System.out.println("Check if FA is deterministic: " + finiteAutomata.isDFA());

        finiteAutomata.runMenu();
    }

    public static void main(String[] args) {
        runScanner("p1.txt", "p1_PIF.out", "p1_ST.out");
        runScanner("p1err.txt", "p1err_PIF.out", "p1err_ST.out");
        runScanner("p2.txt", "p2_PIF.out", "p2_ST.out");
        runScanner("p3.txt", "p3_PIF.out", "p3_ST.out");

        processFiniteAutomataFromFile("nfa.txt");
        processFiniteAutomataFromFile("dfa.txt");
    }
}
