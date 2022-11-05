package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.Types.IntType;
import Model.Values.IntValue;
import Model.Values.Value;

// done for LAB02
public class ArithmeticExpression implements ProgramExpression {
    ProgramExpression firstExpression;
    ProgramExpression secondExpression;
    char operation;

    public ArithmeticExpression(char _operation, ProgramExpression _firstExpression, ProgramExpression _secondExpression) {
        firstExpression = _firstExpression;
        secondExpression = _secondExpression;
        operation = _operation;
    }

    public Value evaluate(MyiDictionary<String, Value> table)  throws MyException {
        Value firstValue, secondValue;
        firstValue = firstExpression.evaluate(table);

        if (firstValue.getType().equals(new IntType())) {
            secondValue = secondExpression.evaluate(table);

            if (secondValue.getType().equals(new IntType())) {
                IntValue firstInteger = (IntValue) firstValue;
                IntValue secondInteger = (IntValue) secondValue;

                int firstNumber, secondNumber;

                firstNumber = firstInteger.getValue();
                secondNumber = secondInteger.getValue();

                if (operation == '+')
                    return new IntValue(firstNumber + secondNumber);

                if (operation == '-')
                    return new IntValue(firstNumber - secondNumber);

                if(operation == '*')
                    return new IntValue(firstNumber * secondNumber);

                if(operation == '/') {
                    if (secondNumber == 0) throw new MyException("Error! Division by zero not allowed!");

                    else
                        return new IntValue(firstNumber / secondNumber);
                }
            } else
                throw new MyException("Second operand is not an integer!");
        } else
            throw new MyException("First operand is not an integer!");

        return null;
    }

    public ProgramExpression createDeepCopy() {
        return new ArithmeticExpression(operation, firstExpression, secondExpression);
    }

    @Override
    public String toString() {
        return firstExpression.toString() + " " + operation + " " + secondExpression.toString();
    }
}
