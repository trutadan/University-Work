package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;

import java.util.Objects;

// done for LAB02
public class LogicalExpression implements ProgramExpression {
    ProgramExpression firstExpression;

    ProgramExpression secondExpression;

    String operation;

    public LogicalExpression(ProgramExpression _firstExpression, ProgramExpression _secondExpression, String _operation) throws MyException {
        firstExpression = _firstExpression;
        secondExpression = _secondExpression;
        operation = _operation;
    }

    public Value evaluate(MyiDictionary<String, Value> table) throws MyException {
        if (!Objects.equals(operation, "and") && !Objects.equals(operation, "or"))
            throw new MyException(operation + " is not a valid operation!");

        Value firstValue = firstExpression.evaluate(table);
        if (firstValue.getType().equals(new BoolType()))
            throw new MyException(firstExpression + " is not a boolean!");

        Value secondValue = secondExpression.evaluate(table);
        if (secondValue.getType().equals(new BoolType()))
            throw new MyException(secondExpression + " is not a boolean!");

        BoolValue firstBoolean = (BoolValue) firstExpression;
        BoolValue secondBoolean = (BoolValue) secondExpression;
        if (Objects.equals(operation, "and"))
            return new BoolValue(firstBoolean.getValue() && secondBoolean.getValue());

        if (Objects.equals(operation, "or"))
            return new BoolValue(firstBoolean.getValue() || secondBoolean.getValue());

        return null;
    }

    public ProgramExpression createDeepCopy() {
        return new LogicalExpression(firstExpression, secondExpression, operation);
    }

    @Override
    public String toString() {
        return firstExpression.toString() + " " + operation + " " + secondExpression.toString();
    }
}