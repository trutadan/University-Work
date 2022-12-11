package Model.Types;

import Model.Values.StringValue;
import Model.Values.Value;

// done for LAB03
public class StringType implements Type{
    public boolean equals(Object another) {
        return another instanceof StringType;
    }
    public Value getDefaultValue() {
        return new StringValue("");
    }

    @Override
    public String toString() {
        return "string";
    }
}
