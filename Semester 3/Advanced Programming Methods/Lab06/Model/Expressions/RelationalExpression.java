package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.BoolType;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.IntValue;
import Model.Values.Value;

// done for LAB06
public class RelationalExpression implements ProgramExpression{
    ProgramExpression firstExpression;
    ProgramExpression secondExpression;
    String relation;

    public RelationalExpression(String _relation, ProgramExpression _firstExpression, ProgramExpression _secondExpression) {
        this.firstExpression = _firstExpression;
        this.secondExpression = _secondExpression;
        this.relation = _relation;
    }

    public Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException {
        Value firstValue, secondValue;
        firstValue = this.firstExpression.evaluate(table, heap);

        if (firstValue.getType().equals(new IntType())) {
            secondValue = this.secondExpression.evaluate(table, heap);

            if (secondValue.getType().equals(new IntType())) {
                IntValue firstInteger = (IntValue) firstValue;
                IntValue secondInteger = (IntValue) secondValue;

                int firstNumber, secondNumber;

                firstNumber = firstInteger.getValue();
                secondNumber = secondInteger.getValue();

                return switch (this.relation) {
                    case "<" -> new BoolValue(firstNumber < secondNumber);

                    case "<=" -> new BoolValue(firstNumber <= secondNumber);

                    case "==" -> new BoolValue(firstNumber == secondNumber);

                    case "!=" -> new BoolValue(firstNumber != secondNumber);

                    case ">" -> new BoolValue(firstNumber > secondNumber);

                    case ">=" -> new BoolValue(firstNumber >= secondNumber);

                    default -> throw new MyException("Not a valid relation provided!");
                };

            } else
                throw new MyException("Second operand is not an integer!");
        } else
            throw new MyException("First operand is not an integer!");
    }

    public Type typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type firstExpressionType = this.firstExpression.typeCheck(typesTable);
        Type secondExpressionType = this.secondExpression.typeCheck(typesTable);

        if (!firstExpressionType.equals(new IntType()))
            throw new MyException("RelationalExpression: First operand is not an integer!");

        if (!secondExpressionType.equals(new IntType()))
            throw new MyException("RelationalExpression: Second operand is not an integer!");

        return new BoolType();
    }

    public ProgramExpression createDeepCopy() {
        return new RelationalExpression(this.relation, this.firstExpression.createDeepCopy(), this.secondExpression.createDeepCopy());
    }

    @Override
    public String toString() {
        return this.firstExpression.toString() + " " + this.relation + " " + this.secondExpression.toString();
    }
}
