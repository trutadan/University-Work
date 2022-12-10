package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.DataStructures.MyiStack;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.BoolType;
import Model.Values.BoolValue;
import Model.Values.Value;

// done for LAB04
public class WhileStatement implements iStatement {
    ProgramExpression expression;
    iStatement statement;

    public WhileStatement(ProgramExpression _expression, iStatement _statement) {
            this.expression = _expression;
            this.statement = _statement;
        }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        MyiHeap heapTable = state.getHeapTable();

        Value value = this.expression.evaluate(symbolsTable, heapTable);
        if (!(value.getType() instanceof BoolType))
            throw new MyException("The expression must be an instance of BoolType!");

        BoolValue booleanValue = (BoolValue) value;
        if (booleanValue.getValue()) {
            MyiStack<iStatement> executionStack = state.getExecutionStack();
            executionStack.push(this);
            executionStack.push(this.statement);
        }

        return null;
    }

    public iStatement createDeepCopy() {
        return new WhileStatement(this.expression.createDeepCopy(), this.statement.createDeepCopy());
    }

    @Override
    public String toString() {
        return "while(" + this.expression.toString() + ") { " + this.statement.toString() + " }";
    }
}
