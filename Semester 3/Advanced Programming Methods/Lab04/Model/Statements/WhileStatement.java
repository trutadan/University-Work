package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.DataStructures.MyiStack;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;

// done for LAB04
public class WhileStatement implements iStatement {
    ProgramExpression expression;
    iStatement statement;

    public WhileStatement(ProgramExpression _expression, iStatement _statement) {
            expression = _expression;
            statement = _statement;
        }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        MyiHeap heapTable = state.getHeapTable();

        Value value = expression.evaluate(symbolsTable, heapTable);
        if (!(value.getType() instanceof BoolType))
            throw new MyException("The expression must be an instance of BoolType!");

        BoolValue booleanValue = (BoolValue) value;
        if (booleanValue.getValue()) {
            MyiStack<iStatement> executionStack = state.getExecutionStack();
            executionStack.push(this);
            executionStack.push(statement);
        }

        return state;
    }

    public iStatement createDeepCopy() {
        return new WhileStatement(expression.createDeepCopy(), statement.createDeepCopy());
    }

    @Override
    public String toString() {
        return "while(" + expression.toString() + ") " + statement.toString();
    }
}
