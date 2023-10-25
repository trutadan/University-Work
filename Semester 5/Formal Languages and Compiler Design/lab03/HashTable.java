import java.util.ArrayList;
import java.util.NoSuchElementException;

public class HashTable {
    private final ArrayList<ArrayList<String>> table;
    private int size;

    public HashTable(int size) {
        this.size = size;

        this.table = new ArrayList<>();
        for(int line = 0; line < this.size; line++)
            this.table.add(new ArrayList<>());
    }

    public ArrayList<ArrayList<String>> getTable() {
        return this.table;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    private int hashFunction(String key) {
        // h(k) = (val(k) mod m) + 1
        // val(k) is the sum of ASCII codes of chars
        // +1 will be omitted since the indexing starts from 0
        int sum = 0;
        for(int position = 0; position < key.length(); position++)
            sum += key.charAt(position);

        return sum % this.size;
    }

    public String getElement(Pair<Integer, Integer> position) throws IndexOutOfBoundsException {
        if(this.table.size() <= position.getKey() || this.table.get(position.getKey()).size() <= position.getValue())
            throw new IndexOutOfBoundsException("Invalid position");

        return this.table.get(position.getKey()).get(position.getValue());
    }

    public Pair<Integer, Integer> search(String element) {
        int rowNumber = this.hashFunction(element);
        Pair<Integer, Integer> searchedPosition = new Pair<>(-1, -1);

        ArrayList<String> row = this.table.get(rowNumber);
        if (row.isEmpty())
            return searchedPosition;

        for (int index = 0; index < row.size(); index++)
            if (row.get(index).equals(element)) {
                searchedPosition = new Pair<>(rowNumber, index);
                break;
            }

        return searchedPosition;
    }

    public Pair<Integer, Integer> add(String element) {
        // Pos(token,ST) – searches token in symbol table ST; if found then
        // return position; if not found insert in SR and return position
        Pair<Integer, Integer> elementPosition = this.search(element);

        if (elementPosition.valid())
            return elementPosition;

        int rowNumber = this.hashFunction(element);
        ArrayList<String> row = this.table.get(rowNumber);

        row.add(element);
        int index = row.indexOf(element);

        elementPosition = new Pair<>(rowNumber, index);

        return elementPosition;
    }

    public void remove(String element) throws NoSuchElementException {
        Pair<Integer, Integer> elementPosition = this.search(element);

        if (elementPosition.valid())
            this.table.get(elementPosition.getKey()).remove(element);
        else
            throw new NoSuchElementException("Element not found: " + element);
    }

    @Override
    public String toString() {
        StringBuilder stringRepresentation = new StringBuilder("Table: {\n");

        for (ArrayList<String> row : table) {
            stringRepresentation.append("  [");
            for (int i = 0; i < row.size(); i++) {
                stringRepresentation.append(row.get(i));
                if (i < row.size() - 1) {
                    stringRepresentation.append(", ");
                }
            }
            stringRepresentation.append("]\n");
        }

        stringRepresentation.append("}");

        return stringRepresentation.toString();
    }
}
