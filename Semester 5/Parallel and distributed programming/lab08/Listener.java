import mpi.MPI;

public class Listener implements Runnable {
    private final DSM dsm;
    private volatile boolean isRunning = true;

    public Listener(DSM dsm) {
        this.dsm = dsm;
    }

    public void stop() {
        isRunning = false;
    }

    @Override
    public void run() {
        int rank = MPI.COMM_WORLD.Rank();
        System.out.printf("Rank %s - started...%n", rank);

        while (isRunning) {
            final Object[] messageBuffer = new Object[1];

            MPI.COMM_WORLD.Recv(messageBuffer, 0, 1, MPI.OBJECT, MPI.ANY_SOURCE, MPI.ANY_TAG);
            final Message message = (Message) messageBuffer[0];

            processMessage(rank, message);
        }
    }

    private void processMessage(int rank, Message message) {
        MessageType messageType = message.getType();

        if (messageType.equals(MessageType.QUIT)) {
            System.out.printf("Rank %s - received QUIT message (final DSM variables state: %s...)%n", rank, dsm.variables());
            stop();
        } else if (messageType.equals(MessageType.SUBSCRIBE)) {
            System.out.printf("Rank %s - received SUBSCRIBE message (rank %s -> variable %s)...%n", rank, message.getRank(), message.getVariable());
            dsm.addSubscription(message.getVariable(), message.getRank());
        } else if (messageType.equals(MessageType.UPDATE)) {
            System.out.printf("Rank %s - received UPDATE message (variable %s -> value %s)...%n", rank, message.getVariable(), message.getValue());
            dsm.setVariable(message.getVariable(), message.getValue());
        }
    }
}