package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.DataStructures.MyiStack;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.BoolType;
import Model.Types.Type;
import Model.Values.BoolValue;
import Model.Values.Value;

// done for LAB06
public class IfStatement implements iStatement {
    ProgramExpression expression;
    iStatement thenStatement;
    iStatement elseStatement;

    public IfStatement(ProgramExpression _expression, iStatement _thenStatement, iStatement _elseStatement) {
        this.expression = _expression;
        this.thenStatement = _thenStatement;
        this.elseStatement = _elseStatement;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        MyiHeap heapTable = state.getHeapTable();

        Value expressionValue = this.expression.evaluate(symbolsTable, heapTable);
        if (expressionValue instanceof BoolValue booleanExpression) {
            MyiStack<iStatement> executionStack = state.getExecutionStack();

            if (booleanExpression.getValue())
                executionStack.push(this.thenStatement);

            else
                executionStack.push(this.elseStatement);

            state.setExecutionStack(executionStack);
            return null;
        }

        else
            throw new MyException("Conditional expression is not a boolean!");
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type expressionType = this.expression.typeCheck(typesTable);

        if (!(expressionType.equals(new BoolType())))
            throw new MyException("IfStatement: The condition is not of BoolType!");

        this.thenStatement.typeCheck(typesTable);
        this.elseStatement.typeCheck(typesTable);

        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new IfStatement(this.expression.createDeepCopy(), this.thenStatement.createDeepCopy(), this.elseStatement.createDeepCopy());
    }

    @Override
    public String toString() {
        return "(if (" + this.expression.toString() + "), then (" + this.thenStatement.toString() + "); else (" + this.elseStatement.toString()+"))";
    }
}

