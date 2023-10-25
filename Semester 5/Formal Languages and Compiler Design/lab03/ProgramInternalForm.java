import java.util.ArrayList;
import java.util.List;

public class ProgramInternalForm {
    private final List<Pair<Pair<String, Integer>, Pair<Integer, Integer>>> array;

    public ProgramInternalForm() {
        this.array = new ArrayList<>();
    }

    public List<Pair<Pair<String, Integer>, Pair<Integer, Integer>>> getArray() {
        return this.array;
    }

    public void add(Pair<String, Integer> token, Pair<Integer, Integer> symbolTablePosition) {
        Pair<Pair<String, Integer>, Pair<Integer, Integer>> pair = new Pair<>(token, symbolTablePosition);
        this.array.add(pair);
    }

    @Override
    public String toString() {
        StringBuilder stringRepresentation = new StringBuilder();
        stringRepresentation.append("PIF: {\n");

        for (Pair<Pair<String, Integer>, Pair<Integer, Integer>> pair : this.array)
            stringRepresentation.append("  (").append(pair.getKey().toString()).append(", ").append(pair.getValue().toString()).append(")\n");

        stringRepresentation.append("}");
        return stringRepresentation.toString();
    }
}
