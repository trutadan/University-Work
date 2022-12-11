package Model.Expressions;

import Exceptions.MyException;
import Model.DataStructures.MyiDictionary;
import Model.DataStructures.MyiHeap;
import Model.Types.ReferenceType;
import Model.Types.Type;
import Model.Values.ReferenceValue;
import Model.Values.Value;

// done for LAB06
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

    public Type typeCheck(MyiDictionary<String, Type> typesTable) throws MyException {
        Type expressionType = this.expression.typeCheck(typesTable);

        if (!(expressionType instanceof ReferenceType))
            throw new MyException("HeapRead: Expression is not of ReferenceType!");

        ReferenceType referenceType = (ReferenceType) expressionType;
        return referenceType.getInner();
    }

    public ProgramExpression createDeepCopy() {
        return new HeapReadingExpression(this.expression.createDeepCopy());
    }

    @Override
    public String toString() {
        return "HeapRead(" + this.expression.toString() + ")";
    }
}
