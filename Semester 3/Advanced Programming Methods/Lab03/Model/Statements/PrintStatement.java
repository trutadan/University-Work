package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiList;
import Model.Expressions.ProgramExpression;
import Model.ProgramState;
import Model.Values.Value;

// done for LAB02
public class PrintStatement implements iStatement {
    ProgramExpression expression;

    public PrintStatement(ProgramExpression _expression) {
        expression = _expression;
    }

    public ProgramState execute(ProgramState state) throws MyException {
        // get the output values the program has up until this moment of execution
        MyiList<Value> outputValues = state.getOutputValues();

        // add the new value to the output values list
        outputValues.add(expression.evaluate(state.getSymbolsTable()));

        // change the output values of the state
        state.setOutputValues(outputValues);
        return state;
    }

    public iStatement createDeepCopy() {
        return new PrintStatement(expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "print(" + expression.toString() + ")";
    }
    
}

