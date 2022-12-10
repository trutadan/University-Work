package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.ProgramState.ProgramState;
import Model.Types.Type;
import Model.Values.Value;

// done for LAB02
public class VariableDeclarationStatement implements iStatement {
    String name;
    Type type;

    public VariableDeclarationStatement(String _name, Type _type) {
        this.name = _name;
        this.type = _type;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        if (symbolsTable.isDefined(this.name))
            throw new MyException("Variable " + this.name + " is already declared!");

        symbolsTable.add(this.name, this.type.getDefaultValue());
        state.setSymbolsTable(symbolsTable);

        return null;
    }

    public iStatement createDeepCopy() {
        return new VariableDeclarationStatement(this.name, this.type);
    }

    @Override
    public String toString() {
        return this.type.toString() + " " + this.name;
    }
}
