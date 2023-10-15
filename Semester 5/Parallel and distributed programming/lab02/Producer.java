import java.util.List;

public class Producer extends Thread {
    private final List<Integer> firstVector, secondVector;
    private final Handler handler;

    public Producer(Handler handler, List<Integer> firstVector, List<Integer> secondVector) {
        this.handler = handler;
        this.firstVector = firstVector;
        this.secondVector = secondVector;
    }

    public void sendProducts() {
        for(int index = 0; index < this.firstVector.size(); index++)
            handler.collect(this.firstVector.get(index) * this.secondVector.get(index));
    }

    @Override
    public void run() {
        try {
            System.out.println("Producer started running...");
            this.sendProducts();
        } catch (Exception exception) {
            System.out.println("Producer error: " + exception.getMessage());
        }
    }
}
