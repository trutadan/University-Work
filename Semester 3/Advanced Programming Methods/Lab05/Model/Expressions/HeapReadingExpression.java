package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.ReferenceType;
import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB04
public class HeapReadingExpression implements ProgramExpression{
    ProgramExpression expression;

    public HeapReadingExpression(ProgramExpression _expression) {
        this.expression = _expression;
    }

    public Value evaluate(MyiDictionary<String, Value> table, MyiHeap heap) throws MyException {
        Value value = this.expression.evaluate(table, heap);
        if (!(value.getType() instanceof ReferenceType))
            throw new MyException("The value of the expression must be of ReferenceType!");

        ReferenceValue referenceValue = (ReferenceValue)value;

        return heap.lookUp(referenceValue.getAddress());
    }

    public ProgramExpression createDeepCopy() {
        return new HeapReadingExpression(this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "HeapRead(" + this.expression.toString() + ")";
    }
}
