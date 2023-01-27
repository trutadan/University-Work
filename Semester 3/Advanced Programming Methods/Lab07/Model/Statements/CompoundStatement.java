package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiStack;
import Model.ProgramState.ProgramState;
import Model.Types.Type;

// done for LAB06
public class CompoundStatement implements iStatement {
    iStatement first;
    iStatement second;

    public CompoundStatement(iStatement _first, iStatement _second) {
        this.first = _first;
        this.second = _second;
    }

    public ProgramState execute(ProgramState state)  throws MyException {
        MyiStack<iStatement> executionStack = state.getExecutionStack();
        executionStack.push(this.second);
        executionStack.push(this.first);

        state.setExecutionStack(executionStack);
        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        return this.second.typeCheck(this.first.typeCheck(typesTable));
    }

    public iStatement createDeepCopy() {
        return new CompoundStatement(this.first.createDeepCopy(), this.second.createDeepCopy());
    }

    @Override
    public String toString() {
        return "(" + this.first.toString() + "| " + this.second.toString() + ")";
    }
}