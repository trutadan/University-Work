package Model.DataStructures;

import Exceptions.MyException;

import java.util.HashMap;

// done for LAB02
public class MyDictionary<T1, T2> implements MyiDictionary<T1, T2>{
    HashMap<T1, T2> hashmap;

    public MyDictionary() {
        this.hashmap = new HashMap<>();
    }

    public HashMap<T1, T2> getContent() {
        return hashmap;
    }

    public boolean isDefined(T1 key) {
        return hashmap.containsKey(key);
    }

    public T2 lookUp(T1 key) throws MyException {
        if (!isDefined(key))
            throw new MyException("There is no value for the key " + key.toString() + "!");

        return hashmap.get(key);
    }

    public void addSymbol(T1 key, T2 value) {
        hashmap.put(key, value);
    }

    public void removeSymbol(T1 key) {
        if (!isDefined(key))
            throw new MyException("There is no key called " + key.toString() + "!");

        hashmap.remove(key);
    }

    public void update(T1 key, T2 value) throws MyException {
        if (!isDefined(key))
            throw new MyException("There is no value for the key " + key.toString() + "!");

        hashmap.put(key, value);
    }

    @Override
    public String toString() {
        return hashmap.toString();
    }
}
