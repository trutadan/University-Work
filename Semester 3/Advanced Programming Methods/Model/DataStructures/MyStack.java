package Model.DataStructures;

import Exceptions.MyException;

import java.util.Stack;

// done for LAB02
public class MyStack<T> implements MyiStack<T>{
    Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<>();
    }

    public boolean isEmpty() {
        return this.stack.isEmpty();
    }

    public T pop() throws MyException {
        if (isEmpty())
            throw new MyException("The stack is empty!");

        return this.stack.pop();
    }

    public void push(T newValue) {
        this.stack.push(newValue);
    }

    @Override
    public String toString() {
        return this.stack.toString();
    }
}
