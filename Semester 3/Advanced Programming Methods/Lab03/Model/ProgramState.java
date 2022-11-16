package Model;

import Model.DataStructures.*;
import Model.Statements.iStatement;
import Model.Values.Value;

import java.io.BufferedReader;

// done for LAB02
public class ProgramState {
    MyiStack<iStatement> executionStack;
    MyiDictionary<String, Value> symbolsTable;
    MyiList<Value> outputValues;
    MyiDictionary<String, BufferedReader> fileTable;
    iStatement originalProgram;

    public ProgramState(iStatement _program) {
        executionStack = new MyStack<>();
        symbolsTable = new MyDictionary<>();
        outputValues = new MyList<>();
        fileTable = new MyDictionary<>();

        originalProgram = _program.createDeepCopy();

        executionStack.push(originalProgram);
    }

    public MyiStack<iStatement> getExecutionStack() {
        return executionStack;
    }

    public MyiDictionary<String, Value> getSymbolsTable() {
        return symbolsTable;
    }

    public MyiList<Value> getOutputValues() {
        return outputValues;
    }

    public MyiDictionary<String, BufferedReader> getFileTable() { return fileTable; }

    public iStatement getOriginalProgram() {
        return originalProgram;
    }

    public void setExecutionStack(MyiStack<iStatement> newExecutionStack) {
        executionStack = newExecutionStack;
    }

    public void setSymbolsTable(MyiDictionary<String, Value> newSymbolsTable) {
        symbolsTable = newSymbolsTable;
    }

    public void setOutputValues(MyiList<Value> newOutputValues) {
        outputValues = newOutputValues;
    }

    public void setFileTable(MyiDictionary<String, BufferedReader> newFileTable) { fileTable = newFileTable; }

    public void setOriginalProgram(iStatement newOriginalProgram){
        originalProgram = newOriginalProgram;
    }

    public void resetToOriginalProgram() {
        executionStack = new MyStack<>();
        symbolsTable = new MyDictionary<>();
        outputValues = new MyList<>();
        fileTable = new MyDictionary<>();

        executionStack.push(originalProgram.createDeepCopy());
    }

    @Override
    public String toString() {
        return "Execution stack: \n" + executionStack.toString() + "\nSymbols table: \n" + symbolsTable.toString() + "\nOutput values: \n" + outputValues.toString() + "\nFile table: \n" + fileTable.toString();
    }
}
