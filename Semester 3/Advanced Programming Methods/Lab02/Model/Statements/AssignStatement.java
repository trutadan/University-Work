package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

// DONE FOR LAB2
public class AssignStatement implements iStatement {
    String id;
    ProgramExpression expression;

    public AssignStatement(String _id, ProgramExpression _expression) {
        id = _id;
        expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();

        if (symbolsTable.isDefined(id)) {
            Value value = expression.evaluate(symbolsTable);
            Type typeID = (symbolsTable.lookUp(id)).getType();

            if (value.getType().equals(typeID))
                symbolsTable.update(id, value);

            else
                throw new MyException("The declared type of variable " + id + " and type of the assigned expression do not match!");
        }

        else
            throw new MyException("The used variable " + id + " was not declared before!");

        return state;
    }

    public iStatement createDeepCopy() {
        return new AssignStatement(id, expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return id + "=" + expression.toString();
    }
}
