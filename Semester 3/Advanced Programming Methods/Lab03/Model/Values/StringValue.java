package Model.Values;

import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;

import java.util.Objects;

public class StringValue implements Value{
    String value;

    public StringValue(String _value) {
        value = _value;
    }

    public String getValue() {
        return value;
    }

    public boolean equals(Object another) {
        if (!(another instanceof StringValue))
            return false;

        return Objects.equals(value, ((StringValue) another).getValue());
    }

    public Type getType() {
        return new StringType();
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

}
