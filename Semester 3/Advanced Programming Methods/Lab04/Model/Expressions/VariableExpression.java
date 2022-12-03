package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Values.Value;

// done for LAB02
public class VariableExpression implements ProgramExpression {
    String id;

    public VariableExpression(String _id) {
        id = _id;
    }

    public Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException {
        return table.lookUp(id);
    }

    public ProgramExpression createDeepCopy() {
        return new VariableExpression(id);
    }

    @Override
    public String toString() {
        return id;
    }
}