package Model.Types;

import Model.Values.BoolValue;

// done for LAB02
public class BoolType implements Type {
    public boolean equals(Object another) {
        return another instanceof IntType;
    }
    public BoolValue getDefaultValue() {
        return new BoolValue(false);
    }

    @Override
    public String toString() {
        return "bool";
    }
}

