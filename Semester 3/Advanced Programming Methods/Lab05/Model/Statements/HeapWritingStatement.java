package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB04
public class HeapWritingStatement implements iStatement {
    String variableName;
    ProgramExpression expression;

    public HeapWritingStatement(String _variableName, ProgramExpression _expression) {
        this.variableName = _variableName;
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (!symbolsTable.isDefined(this.variableName))
            throw new MyException("Variable " + this.variableName + " is not defined in the symbols table!");

        Value value = symbolsTable.lookUp(this.variableName);
        if (!(value.getType() instanceof ReferenceType))
            throw new MyException(this.variableName + "'s value must be of ReferenceType!");

        MyiHeap heapTable = state.getHeapTable();
        Value expressionValue = this.expression.evaluate(symbolsTable, heapTable);
        Type locationType = ((ReferenceValue)value).getLocationType();
        if (!expressionValue.getType().equals(locationType)) {
            throw new MyException("The variable and the expression must be of the same type!");
        }

        heapTable.update(((ReferenceValue) value).getAddress(), expressionValue);

        state.setHeapTable(heapTable);

        return null;
    }

    public iStatement createDeepCopy() {
        return new HeapWritingStatement(this.variableName, this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "HeapWrite(" + this.variableName + ", " + this.expression.toString() + ")";
    }
}
