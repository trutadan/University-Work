package Model.DataStructures;


import Exceptions.MyException;
import Model.Values.Value;

import java.util.HashMap;
import java.util.Map;

// done for LAB04
public class MyHeap implements MyiHeap {
    Map<Integer, Value> map;
    Integer lastOccupiedHeapAddress;

    public MyHeap() {
        map = new HashMap<>();
        lastOccupiedHeapAddress = 0;
    }

    public Map<Integer, Value> getContent() {
        return map;
    }

    public void setContent(Map<Integer, Value> newHeap) {
        map = newHeap;
    }

    public Integer addSymbol(Value value) {
        lastOccupiedHeapAddress += 1;
        map.put(lastOccupiedHeapAddress, value);

        return lastOccupiedHeapAddress;
    }

    public boolean isDefined(Integer address) {
        return map.containsKey(address);
    }

    public Value lookUp(Integer address) throws MyException {
        if (!isDefined(address))
            throw new MyException("There is no value for the key " + address.toString() + "!");

        return map.get(address);
    }

    public void updateSymbol(Integer address, Value expressionValue) {
        if (!map.containsKey(address))
            throw new MyException(String.format("%d is not present in the heap", address));

        map.put(address, expressionValue);
    }

    @Override
    public String toString() {
        return map.toString();
    }
}
