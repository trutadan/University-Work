import mpi.MPI;

import java.util.Map;
import java.util.Set;

public record DSM(Map<String, Object> variables, Map<String, Set<Integer>> subscribers) {

    public synchronized void setVariable(final String variable, final Object value) {
        if (variables.containsKey(variable)) {
            variables.put(variable, value);
        }
    }

    private void sendMessageToAll(final Message message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() != i || message.getType().equals(MessageType.QUIT)) {
                MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
            }
        }
    }

    public void subscribeToVariable(final String variable) {
        int rank = MPI.COMM_WORLD.Rank();
        subscribers.get(variable).add(rank);

        final Message message = new Message(MessageType.SUBSCRIBE);
        message.setVariable(variable);
        message.setRank(rank);

        sendMessageToAll(message);
    }

    public void sendMessageToSubscribers(final String variable, final Message message) {
        for (int i = 0; i < MPI.COMM_WORLD.Size(); i++) {
            if (MPI.COMM_WORLD.Rank() != i && subscribers.get(variable).contains(i)) {
                MPI.COMM_WORLD.Send(new Object[]{message}, 0, 1, MPI.OBJECT, i, 0);
            }
        }
    }

    public void addSubscription(final String variable, final int rank) {
        subscribers.get(variable).add(rank);
    }

    public synchronized void updateVariableAndSendMessage(final String variable, final Object value) {
        setVariable(variable, value);

        final Message message = new Message(MessageType.UPDATE);
        message.setVariable(variable);
        message.setValue(value);

        sendMessageToSubscribers(variable, message);
    }

    public synchronized void compareAndExchange(final String variable, final Object oldValue, final Object newValue) {
        if (oldValue.equals(variables.get(variable))) {
            updateVariableAndSendMessage(variable, newValue);
        }
    }

    public void close() {
        sendMessageToAll(new Message(MessageType.QUIT));
    }
}