import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class FiniteAutomata {
    private Set<String> states;
    private Set<Character> alphabet;
    private List<Transition> transitions;
    private String initialState;
    private Set<String> finalStates;
    private final Scanner scanner;

    public FiniteAutomata() {
        this.scanner = new Scanner(System.in);
        this.resetFiniteAutomata();
    }

    private void resetFiniteAutomata() {
        this.states = new HashSet<>();
        this.alphabet = new HashSet<>();
        this.transitions = new ArrayList<>();
        this.initialState = "";
        this.finalStates = new HashSet<>();
    }

    public void setStates(Set<String> states) {
        this.states = states;
    }

    public void setAlphabet(Set<Character> alphabet) {
        this.alphabet = alphabet;
    }

    public void setTransitions(List<Transition> transitions) {
        this.transitions = transitions;
    }

    public void setInitialState(String initialState) {
        this.initialState = initialState;
    }

    public void setFinalStates(Set<String> finalStates) {
        this.finalStates = finalStates;
    }

    public void initializeElements(String inputFile) {
        try (BufferedReader reader = new BufferedReader(new FileReader(inputFile))) {
            String line;
            int lineCount = 1;

            while ((line = reader.readLine()) != null) {
                try {
                    switch (lineCount) {
                        case 1:
                            this.processStates(line);
                            break;
                        case 2:
                            this.processAlphabet(line);
                            break;
                        case 3:
                            this.processInitialState(line);
                            break;
                        case 4:
                            this.processFinalStates(line);
                            break;
                        default:
                            this.processTransitions(line);
                    }
                } catch (IllegalArgumentException e) {
                    System.out.println("Error in line " + lineCount + ": " + e.getMessage());
                    this.resetFiniteAutomata();
                    break;
                }

                lineCount++;
            }
        } catch (IOException error) {
            System.out.println(error.getMessage());
        }
    }

    private void processStates(String line) throws IllegalArgumentException {
        // the line format is Q = {state1, state2, ..., stateN}
        int startIndex = line.indexOf("{") + 1;
        int endIndex = line.indexOf("}");

        if (startIndex > 0 && endIndex > 0) {
            String statesPart = line.substring(startIndex, endIndex);
            String[] stateNames = statesPart.split(",\\s*");

            this.states.addAll(Arrays.asList(stateNames));
        } else {
            throw new IllegalArgumentException("Invalid state format: " + line);
        }
    }

    private void processAlphabet(String line) throws IllegalArgumentException {
        // the line format is Σ = {symbol1, symbol2, ..., symbolN}
        int startIndex = line.indexOf("{") + 1;
        int endIndex = line.indexOf("}");

        if (startIndex > 0 && endIndex > 0) {
            String alphabetPart = line.substring(startIndex, endIndex);
            String[] charArray = alphabetPart.split(",\\s*");

            for (String charStr : charArray) {
                if (charStr.length() == 1) {
                    char inputSymbol = charStr.charAt(0);
                    this.alphabet.add(inputSymbol);
                } else {
                    throw new IllegalArgumentException("Invalid alphabet format: " + line);
                }
            }
        } else {
            throw new IllegalArgumentException("Invalid alphabet format: " + line);
        }
    }

    private void processInitialState(String line) {
        // the line contains only the initial state name
        this.initialState = line.trim();
    }

    private void processFinalStates(String line) throws IllegalArgumentException {
        // the line format is F = {state1, state2, ..., stateN}
        int startIndex = line.indexOf("{") + 1;
        int endIndex = line.indexOf("}");

        if (startIndex > 0 && endIndex > 0) {
            String finalStatesPart = line.substring(startIndex, endIndex);
            String[] stateNames = finalStatesPart.split(",\\s*");

            this.finalStates.addAll(Arrays.asList(stateNames));
        } else {
            throw new IllegalArgumentException("Invalid final states format: " + line);
        }
    }

    private void processTransitions(String line) throws IllegalArgumentException {
        // the line format is "δ(sourceState,inputSymbol) = destinationState"
        Transition transition = Transition.fromLine(line);
        this.transitions.add(transition);
    }

    private void displayMenu() {
        System.out.println("M = (Q, Σ, δ, q0, F)");
        System.out.println("[0] Exit the menu.");
        System.out.println("[1] Display states.");
        System.out.println("[2] Display alphabet.");
        System.out.println("[3] Display transitions.");
        System.out.println("[4] Display initial state.");
        System.out.println("[5] Display final states.");
        System.out.println("[6] Display finite automata.");
        System.out.println("[7] Check if sequence is accepted.");
        System.out.println("Enter your option:");
    }

    private void displayStates() {
        System.out.println("Q = {" + String.join(", ", this.states) + "}\n");
    }

    private void displayAlphabet() {
        System.out.println("Σ = {" + String.join(", ", this.alphabet.stream().map(String::valueOf).toArray(String[]::new)) + "}\n");
    }

    private void displayTransitions() {
        for (Transition transition : this.transitions) {
            System.out.println(transition.toString());
        }
        System.out.println();
    }

    private void displayInitialState() {
        System.out.println(this.initialState + "\n");
    }

    private void displayFinalStates() {
        System.out.println("F = {" + String.join(", ", this.finalStates) + "}\n");
    }

    public void checkIfSequenceIsAccepted() {
        System.out.println("Enter the sequence to check:");
        String sequence = this.scanner.nextLine();

        boolean isAccepted = isAccepted(sequence);
        if (isAccepted) {
            System.out.println("The sequence is accepted by the Finite Automata.\n");
        } else {
            System.out.println("The sequence is not accepted by the Finite Automata.\n");
        }
    }

    public void runMenu() {
        this.displayMenu();

        int option = this.scanner.nextInt();
        this.scanner.nextLine();

        while (option != 0) {
            switch (option) {
                case 1:
                    this.displayStates();
                    break;
                case 2:
                    this.displayAlphabet();
                    break;
                case 3:
                    this.displayTransitions();
                    break;
                case 4:
                    this.displayInitialState();
                    break;
                case 5:
                    this.displayFinalStates();
                    break;
                case 6:
                    System.out.println(this);
                    break;
                case 7:
                    this.checkIfSequenceIsAccepted();
                    break;
                default:
                    System.out.println("Invalid option. Please enter a valid option.");
                    break;
            }

            this.displayMenu();

            option = this.scanner.nextInt();
            this.scanner.nextLine();
        }

        System.out.println("Menu closed...");

        this.scanner.close();
    }

    public boolean isDFA() {
        // if |δ(q, a)| ≤ 1 => deterministic finite automaton (DFA)
        // if |δ(q, a)| > 1 (more than a state obtained as result) => non-deterministic finite automaton (NFA)

        // see if each state has a unique transition for every symbol in the alphabet
        for (String state : this.states) {
            Set<Character> seenSymbols = new HashSet<>();

            for (Transition transition : this.transitions) {
                if (transition.getSourceState().equals(state)) {
                    char symbol = transition.getInputSymbol();

                    // check if the symbol has not been seen before for the current state
                    if (seenSymbols.contains(symbol)) {
                        return false;
                    }

                    seenSymbols.add(symbol);
                }
            }

            // check if all symbols in the alphabet are seen for the current state
            if (!seenSymbols.containsAll(this.alphabet)) {
                return false;
            }
        }

        return true;
    }

    public boolean isAccepted(String sequence) {
        String currentState = initialState;

        for (char symbol : sequence.toCharArray()) {
            boolean transitionFound = false;

            for (Transition transition : transitions) {
                if (transition.getSourceState().equals(currentState) && transition.getInputSymbol() == symbol) {
                    currentState = transition.getDestinationState();
                    transitionFound = true;
                    break;
                }
            }

            if (!transitionFound) {
                return false;
            }
        }

        return finalStates.contains(currentState);
    }

    @Override
    public String toString() {
        StringBuilder result = new StringBuilder();

        result.append("Q = {").append(String.join(", ", this.states)).append("}\n");
        result.append("Σ = {").append(String.join(", ", this.alphabet.stream().map(String::valueOf).toArray(String[]::new))).append("}\n");
        result.append(this.initialState).append("\n");
        result.append("F = {").append(String.join(", ", this.finalStates)).append("}\n");

        for (Transition transition : this.transitions) {
            result.append(transition.toString()).append("\n");
        }

        return result.toString();
    }
}
