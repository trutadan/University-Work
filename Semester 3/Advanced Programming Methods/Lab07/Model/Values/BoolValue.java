package Model.Values;

import Model.Types.BoolType;
import Model.Types.Type;

// done for LAB02
public class BoolValue implements Value {
    boolean value;
    public BoolValue(boolean _value) {
        this.value = _value;
    }

    public boolean getValue() {
        return this.value;
    }

    public boolean equals(Object another) {
        if (!(another instanceof BoolValue))
            return false;

        return this.value == ((BoolValue) another).getValue();
    }

    public Type getType() {
        return new BoolType();
    }

    public Value createDeepCopy() {
        return new BoolValue(this.value);
    }

    @Override
    public String toString() {
        if (this.value)
            return "True";

        return "False";
    }
}