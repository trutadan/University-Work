import java.util.TimerTask;
import java.util.concurrent.ThreadLocalRandom;

public class NodeUpdateTask extends TimerTask {

    @Override
    public void run() {
        Main.primaryNodes.forEach(primaryNode -> {
            // update the nodes with a random value between -10 and 10
            var value = ThreadLocalRandom.current().nextInt(-10, 10);
            primaryNode.updateValue(value);
        });

        System.out.println("Updated primary nodes with new values...");
    }
}