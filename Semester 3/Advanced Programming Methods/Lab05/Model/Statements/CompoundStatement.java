package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiStack;
import Model.ProgramState.ProgramState;

// done for LAB02
public class CompoundStatement implements iStatement {
    iStatement first;
    iStatement second;

    public CompoundStatement(iStatement _first, iStatement _second) {
        this.first = _first;
        this.second = _second;
    }

    public ProgramState execute(ProgramState state)  throws MyException {
        MyiStack<iStatement> statementStack = state.getExecutionStack();
        statementStack.push(this.second);
        statementStack.push(this.first);

        return null;
    }

    public iStatement createDeepCopy() {
        return new CompoundStatement(this.first.createDeepCopy(), this.second.createDeepCopy());
    }

    @Override
    public String toString() {
        return "(" + this.first.toString() + "| " + this.second.toString() + ")";
    }
}