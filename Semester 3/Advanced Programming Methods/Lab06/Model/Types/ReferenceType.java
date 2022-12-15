package Model.Types;

import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB04
public class ReferenceType implements Type {
    Type inner;

    public ReferenceType(Type _inner) {
        this.inner = _inner;
    }

    public Type getInner() {
        return this.inner;
    }

    public boolean equals(Object another){
        if (another instanceof ReferenceType)
            return this.inner.equals(((ReferenceType) another).getInner());

        else
            return false;
    }
    public Value getDefaultValue() {
        return new ReferenceValue(0, this.inner);
    }

    @Override
    public String toString() {
        return "Reference(" + this.inner.toString() + ")";
    }
}