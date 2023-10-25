public class Pair<K, V> {
    private K key;
    private V value;

    public Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public K getKey() {
        return this.key;
    }

    public void setKey(K key) {
        this.key = key;
    }

    public V getValue() {
        return this.value;
    }

    public void setValue(V value) {
        this.value = value;
    }

    public boolean valid() {
        if (key instanceof Integer && value instanceof Integer)
            return !(((Integer) key == -1) && ((Integer) value == -1));

        return true;
    }

    @Override
    public String toString() {
        return "(" + this.key + ", " + this.value + ")";
    }
}
