public class Consumer extends Thread {
    int sum = 0;
    int vectorSize;
    Handler handler;

    public Consumer(Handler handler, int vectorSize) {
        this.handler = handler;
        this.vectorSize = vectorSize;
    }
    public void getProducts() {
        for(int index = 0; index < this.vectorSize; index++) {
            int product = this.handler.transfer();
            this.sum += product;
        }
    }

    @Override
    public void run() {
        try {
            System.out.println("Consumer started running...");
            this.getProducts();
            System.out.println("The scalar product of the vectors computed by threads is: " + this.sum);
        } catch (Exception exception) {
            System.out.println("Consumer error: " + exception.getMessage());
        }
    }
}
