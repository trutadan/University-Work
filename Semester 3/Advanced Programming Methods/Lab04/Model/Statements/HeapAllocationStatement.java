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
public class HeapAllocationStatement implements iStatement {
    String variableName;
    ProgramExpression expression;

    public HeapAllocationStatement(String _variableName, ProgramExpression _expression) {
        variableName = _variableName;
        expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (!symbolsTable.isDefined(variableName))
            throw new MyException("Variable " + variableName + " is not defined in the symbols table!");

        Value variable = symbolsTable.lookUp(variableName);
        if (!(variable.getType() instanceof ReferenceType))
            throw new MyException(variableName + "'s value must be of ReferenceType!");

        MyiHeap heapTable = state.getHeapTable();
        Value valueOfExpression = expression.evaluate(symbolsTable, heapTable);
        Type locationType = ((ReferenceValue)variable).getLocationType();
        if (!valueOfExpression.getType().equals(locationType)) {
            throw new MyException("The variable and the expression must be of the same type!");
        }

        Integer address = heapTable.addSymbol(valueOfExpression);
        symbolsTable.addSymbol(variableName, new ReferenceValue(address, locationType));

        state.setHeapTable(heapTable);
        state.setSymbolsTable(symbolsTable);

        return state;
    }

    public iStatement createDeepCopy() {
        return new HeapAllocationStatement(variableName, expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "new(" + variableName + ", " + expression + ")";
    }
}
