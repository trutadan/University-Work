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

// done for LAB06
public class HeapAllocationStatement implements iStatement {
    String variableName;
    ProgramExpression expression;

    public HeapAllocationStatement(String _variableName, ProgramExpression _expression) {
        this.variableName = _variableName;
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (!symbolsTable.isDefined(this.variableName))
            throw new MyException("Variable " + this.variableName + " is not defined in the symbols table!");

        Value variable = symbolsTable.lookUp(this.variableName);
        if (!(variable.getType() instanceof ReferenceType))
            throw new MyException(this.variableName + "'s value must be of ReferenceType!");

        MyiHeap heapTable = state.getHeapTable();
        Value valueOfExpression = this.expression.evaluate(symbolsTable, heapTable);
        Type locationType = ((ReferenceValue)variable).getLocationType();
        if (!valueOfExpression.getType().equals(locationType)) {
            throw new MyException("The variable and the expression must be of the same type!");
        }

        Integer address = heapTable.add(valueOfExpression);
        symbolsTable.add(this.variableName, new ReferenceValue(address, locationType));

        state.setHeapTable(heapTable);
        state.setSymbolsTable(symbolsTable);

        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type variableType = typesTable.lookUp(this.variableName);
        Type expressionType = this.expression.typeCheck(typesTable);

        if (!(variableType.equals(new ReferenceType(expressionType))))
            throw new MyException("HeapAllocationStatement: Right hand side and left hand side have different types!");

        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new HeapAllocationStatement(this.variableName, this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "HeapAllocation(" + this.variableName + ", " + this.expression + ")";
    }
}
