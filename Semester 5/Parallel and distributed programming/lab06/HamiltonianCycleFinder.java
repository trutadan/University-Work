import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

public class HamiltonianCycleFinder {
    public Graph graph;
    private static final Integer STARTING_NODE = 0;
    private static final Integer NUM_THREADS = 5;

    public HamiltonianCycleFinder(Graph graph) {
        this.graph = graph;
    }

    public void search() throws Exception {
        ArrayList<Integer> path = new ArrayList<>();

        // always start the search from the given node
        path.add(STARTING_NODE);
        findCycle(STARTING_NODE, path);
    }

    private void findCycle(int currentNode, ArrayList<Integer> path) throws Exception {
        // we can reach the first node from the current node and the path length so far is equal to the number of nodes
        if (graph.isDirectedEdge(currentNode, STARTING_NODE) && path.size() == graph.verticesCount()) {
            path.add(STARTING_NODE);
            System.out.println("Hamiltonian cycle found: " + convertPathToString(path));
            return;
        }

        // if we visited all nodes, and we can't go back to the first node, then there is no Hamiltonian cycle
        if (path.size() == graph.verticesCount()) {
            System.out.println("No Hamiltonian cycle found");
            return;
        }

        // check all possible edges
        for (int i = 0; i < graph.verticesCount(); i++) {
            // if there is an edge to the node, and we haven't already visited it,
            // we add it to the path and mark it as visited by temporarily removing it
            if (graph.isDirectedEdge(currentNode, i) && !(path.contains(i))) {
                path.add(i);
                graph.removeDirectedEdge(currentNode, i);

                ExecutorService executorService = Executors.newFixedThreadPool(NUM_THREADS);

                final Runnable task = getRunnable(path, i);

                // returns a Future representing the pending results of the task
                executorService.submit(task);

                // initiates an orderly shutdown in which previously submitted tasks are executed, but no new tasks will be accepted
                executorService.shutdown();

                // blocks until all tasks have completed execution after a shutdown request
                executorService.awaitTermination(50000, TimeUnit.MILLISECONDS);

                // add the removed edge back so the paths can be correctly used
                graph.addDirectedEdge(currentNode, i);

                // delete the path after it was checked
                path.removeLast();
            }
        }
    }

    private Runnable getRunnable(ArrayList<Integer> path, int i) {
        final int node = i;
        ArrayList<Integer> copiedPath = new ArrayList<>(path);

        return () -> {
            try {
                findCycle(node, copiedPath);
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        };
    }

    public static String convertPathToString(ArrayList<Integer> path) {
        StringBuilder stringBuilder = new StringBuilder();

        for (int i = 0; i < path.size(); i++) {
            stringBuilder.append(path.get(i));

            if (i < path.size() - 1) {
                stringBuilder.append(" -> ");
            }
        }

        return stringBuilder.toString();
    }
}