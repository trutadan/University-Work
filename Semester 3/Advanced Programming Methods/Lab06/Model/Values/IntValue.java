package Model.Values;

import Model.Types.IntType;
import Model.Types.Type;

// done for LAB02
public class IntValue implements Value {
    int value;

    public IntValue(int _value) {
        this.value = _value;
    }

    public int getValue() {
        return this.value;
    }

    public boolean equals(Object another) {
        if (!(another instanceof IntValue))
            return false;

        return this.value == ((IntValue) another).getValue();
    }

    public Type getType() {
        return new IntType();
    }

    public Value createDeepCopy() {
        return new IntValue(this.value);
    }

    @Override
    public String toString() {
        return String.valueOf(this.value);
    }

}