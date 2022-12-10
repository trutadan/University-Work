package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Values.Value;

// done for LAB02
public interface ProgramExpression {
    Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException;

    ProgramExpression createDeepCopy();
}
