public class Main {
    public static void main(String[] args) throws Exception {
        runCycleFinder(createDirectedGraphWithoutHamiltonianCycle());
        runCycleFinder(createDirectedGraphWithHamiltonianCycle());
    }

    public static void runCycleFinder(Graph graph) throws Exception {
        System.out.print("The graph representation:\n" + graph.toString());

        long startTime = System.currentTimeMillis();

        HamiltonianCycleFinder cycleFinder = new HamiltonianCycleFinder(graph);
        cycleFinder.search();

        long endTime = System.currentTimeMillis();
        long duration = endTime - startTime;

        System.out.println("The search took " + duration + "ms\n");
    }

    private static Graph createDirectedGraphWithoutHamiltonianCycle() {
        Graph graph = new Graph(6);

        graph.addDirectedEdge(0, 1);
        graph.addDirectedEdge(1, 3);
        graph.addDirectedEdge(3, 1);
        graph.addDirectedEdge(3, 2);
        graph.addDirectedEdge(3, 4);
        graph.addDirectedEdge(3, 5);
        graph.addDirectedEdge(4, 0);
        graph.addDirectedEdge(4, 5);
        graph.addDirectedEdge(5, 2);

        return graph;
    }

    private static Graph createDirectedGraphWithHamiltonianCycle() {
        Graph graph = new Graph(6);

        graph.addDirectedEdge(0, 1);
        graph.addDirectedEdge(2, 0);
        graph.addDirectedEdge(1, 3);
        graph.addDirectedEdge(3, 1);
        graph.addDirectedEdge(3, 2);
        graph.addDirectedEdge(3, 4);
        graph.addDirectedEdge(3, 5);
        graph.addDirectedEdge(4, 0);
        graph.addDirectedEdge(4, 5);
        graph.addDirectedEdge(5, 2);

        return graph;
    }
}