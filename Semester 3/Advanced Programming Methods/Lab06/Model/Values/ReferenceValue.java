package Model.Values;

import Model.Types.ReferenceType;
import Model.Types.Type;

// done for LAB04
public class ReferenceValue implements Value{
    int address;
    Type locationType;

    public ReferenceValue(int _address, Type _locationType) {
        this.address = _address;
        this.locationType = _locationType;
    }

    public int getAddress() {
        return this.address;
    }

    public Type getLocationType() {
        return this.locationType;
    }

    public Type getType() {
        return new ReferenceType(this.locationType);
    }

    public Value createDeepCopy() {
        return new ReferenceValue(this.address, this.locationType);
    }

    @Override
    public String toString() {
        return "(" + this.locationType.toString() + "*) " + this.address;
    }
}
