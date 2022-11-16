package Model.DataStructures;

// done for LAB02
public interface MyiStack<T> {
    T pop();

    void push(T newValue);

    boolean isEmpty();
}