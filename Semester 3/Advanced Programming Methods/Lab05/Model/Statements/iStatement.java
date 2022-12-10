package Model.Statements;

import Exceptions.MyException;
import Model.ProgramState.ProgramState;

// done for LAB02
public interface  iStatement {
    ProgramState execute(ProgramState state) throws MyException;

    iStatement createDeepCopy();
}