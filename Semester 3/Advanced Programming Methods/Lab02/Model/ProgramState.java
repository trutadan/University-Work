package Model;

import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiList;
import Model.DataStructures.MyiStack;
import Model.Statements.iStatement;
import Model.Values.Value;

// done for LAB02
public class ProgramState {
    MyiStack<iStatement> executionStack;
    MyiDictionary<String, Value> symbolsTable;
    MyiList<Value> outputValues;
    iStatement originalProgram; //optional field, but good to have

    public ProgramState(MyiStack<iStatement> _executionStack, MyiDictionary<String, Value> _symbolsTable, MyiList<Value> _outputValues, iStatement _program) {
        executionStack = _executionStack;
        symbolsTable = _symbolsTable;
        outputValues = _outputValues;
        originalProgram = createDeepCopy(_program); //recreate the entire original program

        _executionStack.push(_program);
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

    public void setOriginalProgram(iStatement newOriginalProgram){
        originalProgram = newOriginalProgram;
    }

    private iStatement createDeepCopy(iStatement program) {
        return program.createDeepCopy();
    }

    @Override
    public String toString() {
        return "Execution stack: \n" + executionStack.toString() + "\nSymbols table: \n" + symbolsTable.toString() + "\nOutput values: \n" + outputValues.toString();
    }
}
