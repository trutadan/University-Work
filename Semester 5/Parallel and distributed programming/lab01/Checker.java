import java.util.ArrayList;
import java.util.HashSet;
import java.util.concurrent.atomic.AtomicBoolean;

public class Checker {
    private final ArrayList<Node> parentNodes;

    public Checker(ArrayList<Node> parentNodes) {
        this.parentNodes = parentNodes;
    }

    public boolean runChecker() {
        var isValid = true;

        try {
            // lock all the nodes to check if the consistency is maintained
            lockAllNodes();
            isValid = checkNodes();
        } finally {
            // unlock the nodes after check was performed
            unlockAllNodes();
        }

        return isValid;
    }

    private boolean checkNodes() {
        // use a hashset to remove the case of possible duplicates
        var setOfNodes = new HashSet<Node>();
        AtomicBoolean isValid = new AtomicBoolean(true);

        // add all the nodes in the hashset
        this.parentNodes.forEach(parent -> {
            setOfNodes.add(parent);
            addChildNodes(parent, setOfNodes);
        });

        // execute the check for all the nodes
        setOfNodes.forEach(node -> {
            if (!checkNode(node)) {
                isValid.set(false);
            }
        });

        return isValid.get();
    }

    private void addChildNodes(Node parent, HashSet<Node> setOfNodes) {
        // add the children of the current node to the set recursively
        parent.getChildrenNodes().forEach(child -> {
            setOfNodes.add(child);
            addChildNodes(child, setOfNodes);
        });
    }

    private boolean checkNode(Node node) {
        // first check if the node has no inputs
        if (node.getParentNodes().isEmpty()) {
            return true;
        }

        // verify that all the secondary variables are the sums of their inputs
        int expectedValue = node.getParentNodes().stream().
                                reduce(0, (subtotal, eachNode) -> subtotal + eachNode.getValue(), Integer::sum);

        return expectedValue == node.getValue();
    }

    private void lockAllNodes() {
        // lock all the nodes related to the current one
        this.parentNodes.forEach(parent -> {
            parent.mutex.lock();
            lockChildNodes(parent);
        });
    }

    private void lockChildNodes(Node parent) {
        // lock the child nodes of the current node recursively
        parent.getChildrenNodes().forEach(child -> {
            child.mutex.lock();
            lockChildNodes(child);
        });
    }

    private void unlockAllNodes() {
        // unlock all the nodes related to the current one
        this.parentNodes.forEach(parent -> {
            parent.mutex.unlock();
            unlockChildNodes(parent);
        });
    }

    private void unlockChildNodes(Node parent) {
        // unlock the child nodes of the current node recursively
        parent.getChildrenNodes().forEach(child -> {
            child.mutex.unlock();
            unlockChildNodes(child);
        });
    }
}