package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

// done for LAB06
public class AssignStatement implements iStatement {
    String id;
    ProgramExpression expression;

    public AssignStatement(String _id, ProgramExpression _expression) {
        this.id = _id;
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        MyiHeap heapTable = state.getHeapTable();

        if (symbolsTable.isDefined(this.id)) {
            Value value = this.expression.evaluate(symbolsTable, heapTable);
            Type typeID = (symbolsTable.lookUp(this.id)).getType();

            if (value.getType().equals(typeID))
                symbolsTable.update(this.id, value);

            else
                throw new MyException("The declared type of variable " + this.id + " and type of the assigned expression do not match!");
        }

        else
            throw new MyException("The used variable " + this.id + " has not been declared before!");

        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type idType = typesTable.lookUp(this.id);
        Type expressionType = this.expression.typeCheck(typesTable);

        if (!idType.equals(expressionType))
            throw new MyException("AssignmentStatement: Right hand side and left hand side have different types!");

        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new AssignStatement(this.id, this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return this.id + "=" + this.expression.toString();
    }
}
