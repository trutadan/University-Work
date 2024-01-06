import mpi.MPI;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

public class Main {

    public static void main(final String[] args) throws InterruptedException {
        Map<String, Object> variables = new ConcurrentHashMap<>();
        variables.put("a", 0);
        variables.put("b", 1);
        variables.put("c", 2);

        Map<String, Set<Integer>> subscribers = new ConcurrentHashMap<>();
        subscribers.put("a", new HashSet<>());
        subscribers.put("b", new HashSet<>());
        subscribers.put("c", new HashSet<>());

        DSM dsm = new DSM(variables, subscribers);

        MPI.Init(args);

        if (MPI.COMM_WORLD.Rank() == 0) {
            // a -> compare and exchange 0 to 3
            // b -> update variable to 4
            // c -> compare and exchange 2 to 5
            master(dsm);
        } else {
            // a -> compare and exchange 3 to 6
            // b -> compare and exchange 4 to 7
            // c -> compare and exchange 5 to 8
            worker(dsm);
        }

        MPI.Finalize();
    }

    private static void master(final DSM dsm) throws InterruptedException {
        // start a listener thread for the master process to handle all exchanged messages
        final Thread thread = new Thread(new Listener(dsm));
        thread.start();

        // rank 0 subscribes to all variables
        dsm.subscribeToVariable("a");
        dsm.subscribeToVariable("b");
        dsm.subscribeToVariable("c");

        Thread.sleep(1000);
        dsm.compareAndExchange("a", 0, 3);

        Thread.sleep(1000);
        dsm.compareAndExchange("c", 2, 5);

        Thread.sleep(1000);
        dsm.updateVariableAndSendMessage("b", 4);

        // be sure that all the threads finish their work before closing
        Thread.sleep(2000);
        System.out.printf("All ranks - final DSM subscribers state: %s...%n", dsm.subscribers());
        dsm.close();

        thread.join();
    }

    private static void worker(final DSM dsm) throws InterruptedException {
        // start a listener thread for each worker process to handle all exchanged messages
        final Thread thread = new Thread(new Listener(dsm));
        thread.start();

        int rank = MPI.COMM_WORLD.Rank();
        if (rank == 1) {
            // rank 1 subscribes only to a and c
            Thread.sleep(1000);
            dsm.subscribeToVariable("a");
            dsm.subscribeToVariable("c");

            Thread.sleep(2000);
            dsm.compareAndExchange("a", 3, 6);
            dsm.compareAndExchange("c", 5, 8);
        } else {
            // rank 2+ workers subscribe only to b
            Thread.sleep(2000);
            dsm.subscribeToVariable("b");

            Thread.sleep(2000);
            dsm.compareAndExchange("b", 4, 7);
        }

        thread.join();
    }
}