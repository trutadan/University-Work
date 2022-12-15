package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.IntType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.Value;

// done for LAB06
public class ArithmeticExpression implements ProgramExpression {
    ProgramExpression firstExpression;
    ProgramExpression secondExpression;
    char operation;

    public ArithmeticExpression(char _operation, ProgramExpression _firstExpression, ProgramExpression _secondExpression) {
        this.firstExpression = _firstExpression;
        this.secondExpression = _secondExpression;
        this.operation = _operation;
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

                if (this.operation == '+')
                    return new IntValue(firstNumber + secondNumber);

                if (this.operation == '-')
                    return new IntValue(firstNumber - secondNumber);

                if(this.operation == '*')
                    return new IntValue(firstNumber * secondNumber);

                if(this.operation == '/') {
                    if (secondNumber == 0)
                        throw new MyException("Error! Division by zero not allowed!");

                    else
                        return new IntValue(firstNumber / secondNumber);
                }
            } else
                throw new MyException("Second operand is not an integer!");
        } else
            throw new MyException("First operand is not an integer!");

        return null;
    }

    public Type typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type firstExpressionType = this.firstExpression.typeCheck(typesTable);
        Type secondExpressionType = this.secondExpression.typeCheck(typesTable);

        if (!firstExpressionType.equals(new IntType()))
            throw new MyException("ArithmeticExpression: First operand is not an integer!");

        if (!secondExpressionType.equals(new IntType()))
            throw new MyException("ArithmeticExpression: Second operand is not an integer!");

        return new IntType();
    }

    public ProgramExpression createDeepCopy() {
        return new ArithmeticExpression(this.operation, this.firstExpression, this.secondExpression);
    }

    @Override
    public String toString() {
        return this.firstExpression.toString() + this.operation + this.secondExpression.toString();
    }
}
