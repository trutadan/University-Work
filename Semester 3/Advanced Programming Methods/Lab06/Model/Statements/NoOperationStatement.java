package Model.Statements;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.ProgramState.ProgramState;
import Model.Types.Type;

// done for LAB06
class NoOperationStatement implements iStatement {

    public ProgramState execute(ProgramState state) throws MyException {
        return null;
    }

    public MyiDictionary<String, Type> typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        return typesTable;
    }

    public iStatement createDeepCopy() {
        return new NoOperationStatement();
    }

    @Override
    public String toString() {
        return "NoOperation";
    }
}