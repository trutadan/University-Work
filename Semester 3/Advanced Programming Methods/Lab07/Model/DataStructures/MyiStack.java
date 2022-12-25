package Model.DataStructures;

import Exceptions.MyException;

import java.util.Stack;

// done for LAB02
public interface MyiStack<T> {
    T pop() throws MyException;

    void push(T newValue);

    boolean isEmpty();

    Stack<T> getStack();
}