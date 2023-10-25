import java.util.NoSuchElementException;

public class SymbolTable {
    private int size;
    private final HashTable table;

    public SymbolTable(int size) {
        this.size = size;
        this.table = new HashTable(this.size);
    }

    public HashTable getTable() {
        return this.table;
    }

    public int getSize() {
        return this.size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getTerm(Pair<Integer, Integer> position) throws IndexOutOfBoundsException {
        return this.table.getElement(position);
    }

    public Pair<Integer, Integer> search(String term) {
        return this.table.search(term);
    }

    public boolean exists(String term) {
        return this.table.search(term).valid();
    }

    public Pair<Integer, Integer> add(String term) {
        return this.table.add(term);
    }

    public void remove(String term) throws NoSuchElementException {
        this.table.remove(term);
    }

    @Override
    public String toString() {
        return "Symbol" + this.table;
    }
}
