package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

// done for LAB02
public class IntValue implements Value {
    int value;

    public IntValue(int _value) {
        value = _value;
    }

    public int getValue() {
        return value;
    }

    public Type getType() {
        return new IntType();
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

}