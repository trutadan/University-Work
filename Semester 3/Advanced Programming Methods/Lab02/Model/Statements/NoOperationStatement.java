package Model.Statements;

import Exceptions.MyException;
import Model.ProgramState;

// DONE FOR LAB2
class NoOperationStatement implements iStatement {

    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    public iStatement createDeepCopy() {
        return new NoOperationStatement();
    }

    @Override
    public String toString() {
        return "NoOperation Statement!";
    }
}