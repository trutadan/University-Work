package Model.DataStructures;

// done for LAB02
public interface MyiDictionary<T1, T2>{
    boolean isDefined(T1 key);

    T2 lookUp(T1 key);

    void addSymbol(T1 key, T2 value);

    void removeSymbol(T1 value);

    void update(T1 key, T2 value);
}
