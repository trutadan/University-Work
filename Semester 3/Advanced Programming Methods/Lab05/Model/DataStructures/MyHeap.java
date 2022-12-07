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
        this.map = new HashMap<>();
        this.lastOccupiedHeapAddress = 0;
    }

    public Map<Integer, Value> getContent() {
        return this.map;
    }

    public void setContent(Map<Integer, Value> newHeap) {
        this.map = newHeap;
    }

    public Integer addSymbol(Value value) {
        this.lastOccupiedHeapAddress += 1;
        this.map.put(this.lastOccupiedHeapAddress, value);

        return this.lastOccupiedHeapAddress;
    }

    public boolean isDefined(Integer address) {
        return this.map.containsKey(address);
    }

    public Value lookUp(Integer address) throws MyException {
        if (!isDefined(address))
            throw new MyException("There is no value for the key " + address.toString() + "!");

        return this.map.get(address);
    }

    public void updateSymbol(Integer address, Value expressionValue) {
        if (!map.containsKey(address))
            throw new MyException("There is no value for the key " + address.toString() + "!");

        this.map.put(address, expressionValue);
    }

    @Override
    public String toString() {
        return this.map.toString();
    }
}
