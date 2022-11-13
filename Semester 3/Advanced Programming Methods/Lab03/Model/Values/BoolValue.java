package Model.Values;

import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;

// done for LAB02
public class BoolValue implements Value {
    boolean value;
    public BoolValue(boolean _value) {
        value = _value;
    }

    public boolean getValue() {
        return value;
    }

    public boolean equals(Object another) {
        if (!(another instanceof BoolValue))
            return false;

        return value == ((BoolValue) another).getValue();
    }

    public Type getType() {
        return new BoolType();
    }

    @Override
    public String toString() {
        if (value)
            return "True";

        return "False";
    }
}