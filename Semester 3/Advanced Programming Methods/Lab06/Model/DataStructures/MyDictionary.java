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
        return this.hashmap;
    }

    public boolean isDefined(T1 key) {
        return this.hashmap.containsKey(key);
    }

    public T2 lookUp(T1 key) throws MyException {
        if (!isDefined(key))
            throw new MyException("There is no value for the key " + key.toString() + "!");

        return this.hashmap.get(key);
    }

    public void add(T1 key, T2 value) {
        this.hashmap.put(key, value);
    }

    public void removeByKey(T1 key) throws MyException {
        if (!isDefined(key))
            throw new MyException("There is no key called " + key.toString() + "!");

        this.hashmap.remove(key);
    }

    public void update(T1 key, T2 value) throws MyException {
        if (!isDefined(key))
            throw new MyException("There is no value for the key " + key.toString() + "!");

        this.hashmap.put(key, value);
    }

    public MyiDictionary<T1, T2> createDeepCopy() {
        MyiDictionary<T1, T2> toReturn = new MyDictionary<>();
        for (T1 key: this.hashmap.keySet())
            toReturn.add(key, this.lookUp(key));

        return toReturn;
    }

    @Override
    public String toString() {
        return this.hashmap.toString();
    }
}
