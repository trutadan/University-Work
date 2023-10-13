import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;

public class Node {
    public ReentrantLock mutex = new ReentrantLock();

    private final ArrayList<Node> parentNodes = new ArrayList<>();
    private final ArrayList<Node> childrenNodes = new ArrayList<>();

    private int value;

    public Node() {
        this.value = 0;
    }

    public Node(int value) {
        this.value = value;
    }

    public ArrayList<Node> getParentNodes() {
        return this.parentNodes;
    }

    public ArrayList<Node> getChildrenNodes() {
        return this.childrenNodes;
    }

    public int getValue() {
        return value;
    }

    public void updateValue(int incrementalValue) {
        try {
            // lock the current node
            this.mutex.lock();

            // update the value
            int oldValue = this.value;
            this.value += incrementalValue;

            // update the value of the children of the nodes recursively so the consistency is maintained
            this.getChildrenNodes().forEach(child ->
                                {child.updateValue(incrementalValue);
                                    System.out.println("Node with the value " + oldValue +
                                            " updated using the value " + incrementalValue +
                                                " and now is " + this.value);});
        } finally {
            // unlock the current node
            this.mutex.unlock();
        }
    }

    public void addChild(Node child) {
        // the current node has a new child
        this.childrenNodes.add(child);
        // the child has a new parent(the current one)
        child.addParent(this);
        // the value of the child needs to be updated so the consistency is maintained
        child.updateValue(this.value);
    }

    private void addParent(Node parent) {
        this.parentNodes.add(parent);
    }
}