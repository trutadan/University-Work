package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.ProgramState.ProgramState;
import Model.Types.Type;

// done for LAB06
public interface  iStatement {
    ProgramState execute(ProgramState state) throws MyException;

    MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException;

    iStatement createDeepCopy();
}