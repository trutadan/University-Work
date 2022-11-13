package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;

// done for LAB03
public class OpenReadFileStatement implements iStatement{
    ProgramExpression expression;

    public OpenReadFileStatement(ProgramExpression _expression) {
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        Value value = expression.evaluate(state.getSymbolsTable());
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
        fileTable.addSymbol(fileName.getValue(), bufferedReader);
        state.setFileTable(fileTable);

        return state;
    }

    public iStatement createDeepCopy() {
        return new OpenReadFileStatement(expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "OpenReadFile(" + expression.toString() + ")";
    }
}
