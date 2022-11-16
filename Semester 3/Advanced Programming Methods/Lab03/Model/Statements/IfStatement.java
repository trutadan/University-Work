package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiStack;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Values.BoolValue;
import Model.Values.Value;

// done for LAB02
public class IfStatement implements iStatement {
    ProgramExpression expression;
    iStatement thenStatement;
    iStatement elseStatement;

    public IfStatement(ProgramExpression _expression, iStatement _thenStatement, iStatement _elseStatement) {
        expression = _expression;
        thenStatement = _thenStatement;
        elseStatement = _elseStatement;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();

        Value expressionValue = expression.evaluate(symbolsTable);
        if (expressionValue instanceof BoolValue booleanExpression) {
            MyiStack<iStatement> executionStack = state.getExecutionStack();

            if (booleanExpression.getValue())
                executionStack.push(thenStatement);

            else
                executionStack.push(elseStatement);

            state.setExecutionStack(executionStack);
            return state;
        }

        else
            throw new MyException("Conditional expression is not a boolean!");
    }

    public iStatement createDeepCopy() {
        return new IfStatement(expression.createDeepCopy(), thenStatement.createDeepCopy(), elseStatement.createDeepCopy());
    }

    @Override
    public String toString() {
        return "(IF(" + expression.toString() + ") THEN(" + thenStatement.toString() + ") ELSE(" + elseStatement.toString()+"))";
    }
}

