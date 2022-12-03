package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB04
public class HeapWritingStatement implements iStatement {
    String variableName;
    ProgramExpression expression;

    public HeapWritingStatement(String _variableName, ProgramExpression _expression) {
        variableName = _variableName;
        expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (!symbolsTable.isDefined(variableName))
            throw new MyException("Variable " + variableName + " is not defined in the symbols table!");

        Value value = symbolsTable.lookUp(variableName);
        if (!(value.getType() instanceof ReferenceType))
            throw new MyException(variableName + "'s value must be of ReferenceType!");

        MyiHeap heapTable = state.getHeapTable();
        Value expressionValue = expression.evaluate(symbolsTable, heapTable);
        Type locationType = ((ReferenceValue)value).getLocationType();
        if (!expressionValue.getType().equals(locationType)) {
            throw new MyException("The variable and the expression must be of the same type!");
        }

        heapTable.updateSymbol(((ReferenceValue) value).getAddress(), expressionValue);

        state.setHeapTable(heapTable);

        return state;
    }

    public iStatement createDeepCopy() {
        return new HeapWritingStatement(variableName, expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "HeapWritingStatement(" + variableName + ", " + expression.toString() + ")";
    }
}
