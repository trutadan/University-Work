package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

// done for LAB06
public class OpenReadFileStatement implements iStatement{
    ProgramExpression expression;

    public OpenReadFileStatement(ProgramExpression _expression) {
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        MyiHeap heapTable = state.getHeapTable();

        Value value = this.expression.evaluate(state.getSymbolsTable(), heapTable);
        if (!value.getType().equals(new StringType()))
            throw new MyException("The expression must be a StringType!");

        StringValue fileName = (StringValue) value;
        if (state.getFileTable().isDefined(fileName.getValue()))
            throw new MyException("The file is already opened!");

        BufferedReader bufferedReader;
        try {
            bufferedReader = new BufferedReader(new FileReader(fileName.getValue()));
        } catch (FileNotFoundException exception) {
            throw new MyException(fileName + " file could not be opened!");
        }

        MyiDictionary<String, BufferedReader> fileTable = state.getFileTable();
        fileTable.add(fileName.getValue(), bufferedReader);
        state.setFileTable(fileTable);

        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        if (!(this.expression.typeCheck(typesTable).equals(new StringType())))
            throw new MyException("OpenReadFile: A string expression must be provided!");

        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new OpenReadFileStatement(this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "OpenReadFile(" + this.expression.toString() + ")";
    }
}
