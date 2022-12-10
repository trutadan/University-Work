package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.*;
import Model.ProgramState.ProgramState;
import Model.Values.Value;

import java.util.Map;

// done for LAB05
public class CreateThreadStatement implements iStatement{
    iStatement statement;

    public CreateThreadStatement(iStatement _statement) {
        this.statement = _statement;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiStack<iStatement> newStack = new MyStack<>();

        MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
        MyiDictionary<String, Value> symbolsTableDeepCopy = new MyDictionary<>();
        for (Map.Entry<String, Value> entry: symbolsTable.getContent().entrySet())
            symbolsTableDeepCopy.add(entry.getKey(), entry.getValue().createDeepCopy());

        return new ProgramState(this.statement, newStack, symbolsTableDeepCopy, state.getOutputValues(), state.getFileTable(), state.getHeapTable());
    }

    public iStatement createDeepCopy() {
        return new CreateThreadStatement(this.statement.createDeepCopy());
    }

    @Override
    public String toString() {
        return "CreateThread(" + this.statement.toString() + ")";
    }
}
