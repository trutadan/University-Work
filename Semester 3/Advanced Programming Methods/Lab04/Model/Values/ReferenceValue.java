package Model.Values;

import Model.Types.ReferenceType;
import Model.Types.Type;

// done for LAB04
public class ReferenceValue implements Value{
    int address;
    Type locationType;

    public ReferenceValue(int _address, Type _locationType) {
        address = _address;
        locationType = _locationType;
    }

    public int getAddress() {
        return address;
    }

    public Type getLocationType() {
        return locationType;
    }

    public Type getType() {
        return new ReferenceType(locationType);
    }

    @Override
    public String toString() {
        return locationType.toString() + "* " + String.valueOf(address);
    }
}
