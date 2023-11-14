import java.util.ArrayList;
import java.util.List;

public class ProgramInternalForm {
    private final List<Pair<String, Pair<Integer, Integer>>> array;

    public ProgramInternalForm() {
        this.array = new ArrayList<>();
    }

    public List<Pair<String, Pair<Integer, Integer>>> getArray() {
        return this.array;
    }

    public void add(String token, Integer category, Pair<Integer, Integer> symbolTablePosition) {
        Pair<String, Pair<Integer, Integer>> pair;

        if (category == 0)
            pair = new Pair<>("const", symbolTablePosition);
        else if (category == 1)
            pair = new Pair<>("id", symbolTablePosition);
        else
            pair = new Pair<>(token, symbolTablePosition);

        this.array.add(pair);
    }

    @Override
    public String toString() {
        StringBuilder stringRepresentation = new StringBuilder();
        stringRepresentation.append("PIF: {\n");

        for (Pair<String, Pair<Integer, Integer>> pair : this.array)
            stringRepresentation.append("  (").append(pair.getKey()).append(", ").append(pair.getValue().toString()).append(")\n");

        stringRepresentation.append("}");
        return stringRepresentation.toString();
    }
}