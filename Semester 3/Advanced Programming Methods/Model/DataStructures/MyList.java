package Model.DataStructures;

import java.util.ArrayList;
import java.util.List;

// done for LAB02
public class MyList<T> implements MyiList<T>{
    List<T> list;

    public MyList() {
        this.list = new ArrayList<>();
    }

    public void add(T newValue) {
        this.list.add(newValue);
    }

    @Override
    public String toString() {
        return this.list.toString();
    }
}
