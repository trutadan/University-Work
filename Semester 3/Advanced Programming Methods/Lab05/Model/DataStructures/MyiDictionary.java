package Model.DataStructures;

import java.util.HashMap;

// done for LAB02
public interface MyiDictionary<T1, T2>{
    HashMap<T1, T2> getContent();

    boolean isDefined(T1 key);

    T2 lookUp(T1 key);

    void addSymbol(T1 key, T2 value);

    void removeSymbol(T1 value);

    void update(T1 key, T2 value);
}
