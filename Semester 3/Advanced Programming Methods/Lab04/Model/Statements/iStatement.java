package Model.Statements;

import Exceptions.MyException;
import Model.ProgramState;

// done for LAB02
public interface  iStatement {
    public ProgramState execute(ProgramState state) throws MyException;

    public iStatement createDeepCopy();
}