public class Transition {
    private final String sourceState;
    private final char inputSymbol;
    private final String destinationState;

    public Transition(String sourceState, char inputSymbol, String destinationState) {
        this.sourceState = sourceState;
        this.inputSymbol = inputSymbol;
        this.destinationState = destinationState;
    }

    public String getSourceState() {
        return this.sourceState;
    }

    public char getInputSymbol() {
        return this.inputSymbol;
    }

    public String getDestinationState() {
        return this.destinationState;
    }

    public static Transition fromLine(String line) throws IllegalArgumentException {
        String[] parts = line.split("[(),=\\s]+");

        if (parts.length == 4) {
            String sourceState = parts[1];
            char inputSymbol = parts[2].charAt(0);
            String destinationState = parts[3];

            return new Transition(sourceState, inputSymbol, destinationState);
        } else {
            throw new IllegalArgumentException("Invalid transition format: " + line);
        }
    }

    @Override
    public String toString() {
        return "δ(" + this.sourceState + ", " + this.inputSymbol + ") = " + this.destinationState;
    }
}
