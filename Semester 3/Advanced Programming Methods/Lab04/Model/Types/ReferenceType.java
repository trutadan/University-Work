package Model.Types;

import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB04
public class ReferenceType implements Type {
    Type inner;

    public ReferenceType(Type _inner) {
        inner = _inner;
    }

    public Type getInner() {
        return inner;
    }

    public boolean equals(Object another){
        if (another instanceof ReferenceType)
            return inner.equals(((ReferenceType) another).getInner());

        else
            return false;
    }
    public Value getDefaultValue() {
        return new ReferenceValue(0, inner);
    }

    @Override
    public String toString() {
        return "Ref(" + inner.toString() + ")";
    }
}