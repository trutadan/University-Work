package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Types.StringType;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

// done for LAB03
public class CloseReadFileStatement implements iStatement{
    ProgramExpression expression;

    public CloseReadFileStatement(ProgramExpression _expression) {
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        Value value = expression.evaluate(state.getSymbolsTable());
        if (!value.getType().equals(new StringType()))
            throw new MyException("The expression must be a StringType!");

        StringValue stringValue = (StringValue) value;
        if (!state.getFileTable().isDefined(stringValue.getValue()))
            throw new MyException("The file was not found!");

        BufferedReader bufferedReader;
        try {
            bufferedReader = state.getFileTable().lookUp(stringValue.getValue());
            bufferedReader.close();
        }  catch (IOException exception) {
            throw new MyException(stringValue + " file could not be closed!");
        }

        MyiDictionary<String, BufferedReader> fileTable = state.getFileTable();
        fileTable.removeSymbol(stringValue.getValue());
        state.setFileTable(fileTable);

        return state;
    }

    public iStatement createDeepCopy() {
        return new CloseReadFileStatement(expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "CloseReadFileStatement(" + expression + ')';
    }
}
