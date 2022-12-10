package Model.DataStructures;

import Exceptions.MyException;

import java.util.HashMap;

// done for LAB02
public interface MyiDictionary<T1, T2>{
    HashMap<T1, T2> getContent();

    boolean isDefined(T1 key);

    T2 lookUp(T1 key) throws MyException;

    void add(T1 key, T2 value);

    void removeByKey(T1 key) throws MyException;

    void update(T1 key, T2 value) throws MyException;
}
