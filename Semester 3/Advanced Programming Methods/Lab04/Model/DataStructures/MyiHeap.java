package Model.DataStructures;

import Exceptions.MyException;
import Model.Values.Value;

import java.util.Map;

// done for LAB04
public interface MyiHeap{
    Map<Integer, Value> getContent();

    void setContent(Map<Integer, Value> newHeap);

    Integer addSymbol(Value value);

    Value lookUp(Integer key) throws MyException;

    void updateSymbol(Integer address, Value expressionValue);
}
