package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiStack;
import Model.ProgramState;

// DONE FOR LAB2
public class CompoundStatement implements iStatement {
    iStatement first;
    iStatement second;

    public CompoundStatement(iStatement _first, iStatement _second) {
        first = _first;
        second = _second;
    }

    public ProgramState execute(ProgramState state)  throws MyException {
        MyiStack<iStatement> statementStack = state.getExecutionStack();
        statementStack.push(second);
        statementStack.push(first);

        return state;
    }

    public iStatement createDeepCopy() {
        return new CompoundStatement(first.createDeepCopy(), second.createDeepCopy());
    }

    @Override
    public String toString() {
        return "(" + first.toString() + "|" + second.toString() + ")";
    }
}