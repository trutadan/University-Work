import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Handler {
    private final Queue<Integer> products = new LinkedList<>();
    private final Lock mutex = new ReentrantLock();
    private final int MAX_QUEUE_CAPACITY = 10;
    private final Condition notFullConditionalVariable = this.mutex.newCondition();
    private final Condition notEmptyConditionalVariable = this.mutex.newCondition();

    public Handler() {
    }

    public void collect(int product) {
        this.mutex.lock();

        try {
            while (products.size() == MAX_QUEUE_CAPACITY) {
                // Wait if the buffer is full
                notFullConditionalVariable.await();
            }
            this.products.add(product);
            // Signal that the buffer is not empty
            notEmptyConditionalVariable.signal();
        } catch (Exception exception) {
            System.out.println("Handler exception on collecting: " + exception.getMessage());
        } finally {
            this.mutex.unlock();
        }
    }

    public int transfer() {
        this.mutex.lock();

        try {
            while (products.isEmpty()) {
                // Wait if the buffer is empty
                notEmptyConditionalVariable.await();
            }
            // Signal that the buffer is not full
            notFullConditionalVariable.signal();
            return this.products.remove();
        } catch (Exception exception) {
            System.out.println("Handler exception on transferring: " + exception.getMessage());
        } finally {
            this.mutex.unlock();
        }

        return 0;
    }
}
