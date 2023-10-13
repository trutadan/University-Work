import java.util.ArrayList;
import java.util.Timer;

public class Main {

    public static ArrayList<Node> primaryNodes = new ArrayList<>();

    public static void main(String[] args) {
        createTreeStructure();
        scheduleNodeUpdateTasks(10);
        scheduleCheckerTask();
    }

    private static void scheduleCheckerTask() {
        var timer = new Timer();
        timer.schedule(new CheckerTask(), 5, 5 * 1000);
    }

    private static void scheduleNodeUpdateTasks(int threadCount) {
        for (int i = 0; i < threadCount; i++) {
            var timer = new Timer();
            timer.schedule(new NodeUpdateTask(), 0, 1000);
        }
    }

    private static void createTreeStructure() {
        // primary nodes
        var primaryNode1 = new Node(15);
        var primaryNode2 = new Node(3);
        var primaryNode3 = new Node(7);

        primaryNodes.add(primaryNode1);
        primaryNodes.add(primaryNode2);
        primaryNodes.add(primaryNode3);

        // 2nd level secondary nodes
        var secondaryNode1 = new Node();
        primaryNode1.addChild(secondaryNode1);
        primaryNode2.addChild(secondaryNode1);

        var secondaryNode2 = new Node();
        primaryNode1.addChild(secondaryNode2);
        primaryNode3.addChild(secondaryNode2);

        // 3rd level secondary nodes
        var secondaryNode3 = new Node();
        var secondaryNode4 = new Node();
        secondaryNode2.addChild(secondaryNode3);
        secondaryNode2.addChild(secondaryNode4);
    }
}