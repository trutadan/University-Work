package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiList;
import Model.Expressions.ProgramExpression;
import Model.ProgramState.ProgramState;
import Model.Values.Value;

// done for LAB02
public class PrintStatement implements iStatement {
    ProgramExpression expression;

    public PrintStatement(ProgramExpression _expression) {
        this.expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        // get the output values the program has up until this moment of execution
        MyiList<Value> outputValues = state.getOutputValues();

        // add the new value to the output values list
        outputValues.add(this.expression.evaluate(state.getSymbolsTable(), state.getHeapTable()));

        // change the output values of the state
        state.setOutputValues(outputValues);
        return null;
    }

    public iStatement createDeepCopy() {
        return new PrintStatement(this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "Print(" + this.expression.toString() + ")";
    }
    
}
