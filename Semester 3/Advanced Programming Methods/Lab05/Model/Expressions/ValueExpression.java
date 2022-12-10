package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Values.Value;

// done for LAB02
public class ValueExpression implements ProgramExpression {
    Value expression;

    public ValueExpression(Value _expression) {
        this.expression = _expression;
    }

    public Value evaluate(MyiDictionary<String,Value> table, MyiHeap heap) throws MyException {
        return this.expression;
    }

    public ProgramExpression createDeepCopy() {
        return new ValueExpression(this.expression);
    }

    @Override
    public String toString() {
        return this.expression.toString();
    }
}