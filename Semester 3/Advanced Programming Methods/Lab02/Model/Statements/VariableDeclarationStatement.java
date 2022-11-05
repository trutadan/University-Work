package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

// done for LAB2
public class VariableDeclarationStatement implements iStatement {
    String name;
    Type type;

    public VariableDeclarationStatement(String _name, Type _type) {
        name = _name;
        type = _type;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (symbolsTable.isDefined(name))
            throw new MyException("Variable " + name + " is already declared!");

        symbolsTable.addSymbol(name, type.getDefaultValue());
        state.setSymbolsTable(symbolsTable);

        return state;
    }

    public iStatement createDeepCopy() {
        return new VariableDeclarationStatement(name, type);
    }

    @Override
    public String toString() {
        return name + " " + type.toString();
    }
}
