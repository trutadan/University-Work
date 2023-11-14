import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class TokenScanner {
    private final FiniteAutomata identifierFiniteAutomata;
    private final FiniteAutomata integerConstantFiniteAutomata;

    public TokenScanner() {
        this.identifierFiniteAutomata = new FiniteAutomata();
        this.initializeIdentifierFiniteAutomata();

        this.integerConstantFiniteAutomata = new FiniteAutomata();
        this.initializeIntegerConstantFiniteAutomata();
    }

    private Set<Character> generateAlphabetRange(char start, char end) {
        Set<Character> alphabetRange = new HashSet<>();
        for (char character = start; character <= end; character++) {
            alphabetRange.add(character);
        }

        return alphabetRange;
    }

    private Set<Character> generateLowercaseLetters() {
        return generateAlphabetRange('a', 'z');
    }

    private Set<Character> generateUppercaseLetters() {
        return generateAlphabetRange('A', 'Z');
    }

    private Set<Character> generateDigits() {
        return generateAlphabetRange('0', '9');
    }

    private Set<Character> generateNonzeroDigits() {
        return generateAlphabetRange('1', '9');
    }

    public List<Transition> generateTransitionsList(Set<Character> set, String sourceState, String destinationState) {
        List<Transition> transitions = new ArrayList<>();

        for (Character element : set) {
            transitions.add(new Transition(sourceState, element, destinationState));
        }

        return transitions;
    }

    public Set<Character> concatenateSets(Set<Character> set1, Set<Character> set2) {
        Set<Character> concatenatedSet = new HashSet<>(set1);
        concatenatedSet.addAll(set2);
        return concatenatedSet;
    }

    public static List<Transition> concatenateTransitionsLists(List<Transition> list1, List<Transition> list2) {
        List<Transition> concatenatedList = new ArrayList<>();
        concatenatedList.addAll(list1);
        concatenatedList.addAll(list2);
        return concatenatedList;
    }

    private void initializeIdentifierFiniteAutomata() {
        String initialState = "q0";
        String finalState = "q1";
        Set<String> finalStates = Set.of(finalState);
        Set<String> states = Set.of(initialState, finalState);

        Set<Character> alphabet = concatenateSets(generateDigits(), concatenateSets(generateLowercaseLetters(), concatenateSets(generateUppercaseLetters(), Set.of('_'))));

        this.identifierFiniteAutomata.setStates(states);
        this.identifierFiniteAutomata.setAlphabet(alphabet);
        this.identifierFiniteAutomata.setInitialState(initialState);
        this.identifierFiniteAutomata.setFinalStates(finalStates);

        Set<Character> alphabetQ0 = concatenateSets(generateLowercaseLetters(), concatenateSets(generateUppercaseLetters(), Set.of('_')));
        List<Transition> transitionsQ0Q1 = generateTransitionsList(alphabetQ0, initialState, finalState);
        List<Transition> transitionsQ1Q1 = generateTransitionsList(alphabet, finalState, finalState);

        this.identifierFiniteAutomata.setTransitions(concatenateTransitionsLists(transitionsQ0Q1, transitionsQ1Q1));
    }

    private void initializeIntegerConstantFiniteAutomata() {
        String initialState = "q0";
        String finalStateQ2 = "q2";
        String finalStateQ3 = "q3";
        Set<String> finalStates = Set.of(finalStateQ2, finalStateQ3);
        Set<String> states = Set.of("q0", "q1", "q2", "q3");

        Set<Character> digitsAlphabet = generateDigits();
        Set<Character> nonzeroDigitsAlphabet = generateNonzeroDigits();
        Set<Character> signAlphabet = Set.of('+', '-');

        Set<Character> alphabet = concatenateSets(digitsAlphabet, signAlphabet);

        this.integerConstantFiniteAutomata.setStates(states);
        this.integerConstantFiniteAutomata.setAlphabet(alphabet);
        this.integerConstantFiniteAutomata.setInitialState(initialState);
        this.integerConstantFiniteAutomata.setFinalStates(finalStates);

        List<Transition> transitionsQ0Q3 = generateTransitionsList(Set.of('0'), initialState, finalStateQ3);
        List<Transition> transitionsQ0Q1 = generateTransitionsList(signAlphabet, initialState, "q1");
        List<Transition> transitionsQ0Q2 = generateTransitionsList(nonzeroDigitsAlphabet, initialState, finalStateQ2);

        List<Transition> transitionsQ1Q2 = generateTransitionsList(nonzeroDigitsAlphabet, "q1", finalStateQ2);
        List<Transition> transitionsQ2Q2 = generateTransitionsList(digitsAlphabet, finalStateQ2, finalStateQ2);

        List<Transition> transitionsQ0 = concatenateTransitionsLists(transitionsQ0Q3, concatenateTransitionsLists(transitionsQ0Q1, transitionsQ0Q2));
        List<Transition> transitions = concatenateTransitionsLists(transitionsQ0, concatenateTransitionsLists(transitionsQ1Q2, transitionsQ2Q2));

        this.integerConstantFiniteAutomata.setTransitions(transitions);
    }

    public boolean isIdentifier(String token) {
        return this.identifierFiniteAutomata.isAccepted(token);
    }

    public boolean isIntegerConstant(String token) {
        return this.integerConstantFiniteAutomata.isAccepted(token);
    }
}
