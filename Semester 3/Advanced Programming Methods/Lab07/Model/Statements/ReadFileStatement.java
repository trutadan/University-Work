package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Types.IntType;
import Model.Types.StringType;
import Model.Types.Type;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Model.Values.Value;

import java.io.BufferedReader;
import java.io.IOException;

// done for LAB06
public class ReadFileStatement implements iStatement{
    ProgramExpression expression;
    String variableName;

    public ReadFileStatement(ProgramExpression expression, String variableName) {
        this.expression = expression;
        this.variableName = variableName;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        if (state.getSymbolsTable().isDefined(this.variableName))
            throw new MyException(this.variableName + " is not contained in the symbols table!");

        Value value = state.getSymbolsTable().lookUp(this.variableName);
        if (!value.getType().equals(new IntType()))
            throw new MyException("The expression must be a IntType!");

        MyiHeap heapTable = state.getHeapTable();
        value = this.expression.evaluate(state.getSymbolsTable(), heapTable);
        if (!value.getType().equals(new StringType()))
              throw new MyException("The expression must be a StringType!");

        StringValue stringValue = (StringValue) value;
        if (!state.getFileTable().isDefined(stringValue.getValue()))
            throw new MyException("The file table does not contain the value " + stringValue);

        BufferedReader bufferedReader;
        try {
            bufferedReader = state.getFileTable().lookUp(stringValue.getValue());
            String currentLine = bufferedReader.readLine();
            if (currentLine == null)
                currentLine = "0";

            MyiDictionary<String, Value> symbolsTable = state.getSymbolsTable();
            symbolsTable.add(this.variableName, new IntValue(Integer.parseInt(currentLine)));

            state.setSymbolsTable(symbolsTable);

        } catch (IOException exception) {
            throw new MyException("Could not read from the file " + stringValue);
        }

        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type expressionType = this.expression.typeCheck(typesTable);
        if (!expressionType.equals(new StringType()))
            throw new MyException("ReadFileStatement: A string must be provided as expression parameter!");

        Type variableType = typesTable.lookUp(this.variableName);
        if (!(variableType.equals(new IntType())))
            throw new MyException("ReadFileStatement: An int must be provided as variable parameter!");

        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new ReadFileStatement(this.expression.createDeepCopy(), this.variableName);
    }

    @Override
    public String toString() {
        return "ReadFile(" + this.expression + ", " + this.variableName + ')';
    }
}
