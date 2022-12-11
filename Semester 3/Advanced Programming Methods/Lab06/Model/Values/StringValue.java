package Model.Values;

import Model.Types.StringType;
import Model.Types.Type;

import java.util.Objects;

// done for LAB03
public class StringValue implements Value{
    String value;

    public StringValue(String _value) {
        this.value = _value;
    }

    public String getValue() {
        return this.value;
    }

    public boolean equals(Object another) {
        if (!(another instanceof StringValue))
            return false;

        return Objects.equals(this.value, ((StringValue) another).getValue());
    }

    public Type getType() {
        return new StringType();
    }

    public Value createDeepCopy() {
        return new StringValue(this.value);
    }

    @Override
    public String toString() {
        return this.value;
    }

}
