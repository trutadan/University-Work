package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.Type;
import Model.Values.Value;

// done for LAB06
public interface ProgramExpression {
    Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException;

    Type typeCheck(MyiDictionary<String,Type> typesTable) throws MyException;

    ProgramExpression createDeepCopy();
}
