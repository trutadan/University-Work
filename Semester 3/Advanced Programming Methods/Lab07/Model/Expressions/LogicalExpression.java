package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

import java.util.Objects;

// done for LAB06
public class LogicalExpression implements ProgramExpression {
    ProgramExpression firstExpression;

    ProgramExpression secondExpression;

    String operation;

    public LogicalExpression(ProgramExpression _firstExpression, ProgramExpression _secondExpression, String _operation) throws MyException {
        this.firstExpression = _firstExpression;
        this.secondExpression = _secondExpression;
        this.operation = _operation;
    }

    public Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException {
        if (!Objects.equals(this.operation, "and") && !Objects.equals(this.operation, "or"))
            throw new MyException(this.operation + " is not a valid operation!");

        Value firstValue = this.firstExpression.evaluate(table, heap);
        if (firstValue.getType().equals(new BoolType()))
            throw new MyException(this.firstExpression + " is not a boolean!");

        Value secondValue = this.secondExpression.evaluate(table, heap);
        if (secondValue.getType().equals(new BoolType()))
            throw new MyException(this.secondExpression + " is not a boolean!");

        BoolValue firstBoolean = (BoolValue) firstValue;
        BoolValue secondBoolean = (BoolValue) secondValue;
        if (Objects.equals(this.operation, "and"))
            return new BoolValue(firstBoolean.getValue() && secondBoolean.getValue());

        if (Objects.equals(this.operation, "or"))
            return new BoolValue(firstBoolean.getValue() || secondBoolean.getValue());

        return null;
    }

    public Type typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type firstExpressionType = this.firstExpression.typeCheck(typesTable);
        Type secondExpressionType = this.secondExpression.typeCheck(typesTable);

        if (!firstExpressionType.equals(new BoolType()))
            throw new MyException("LogicalExpression: First operand is not a boolean expression!");

        if (!secondExpressionType.equals(new BoolType()))
            throw new MyException("LogicalExpression: Second operand is not a boolean expression!");

        return new BoolType();
    }

    public ProgramExpression createDeepCopy() {
        return new LogicalExpression(this.firstExpression.createDeepCopy(), this.secondExpression.createDeepCopy(), this.operation);
    }

    @Override
    public String toString() {
        return this.firstExpression.toString() + " " + this.operation + " " + this.secondExpression.toString();
    }
}