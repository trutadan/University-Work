public class Graph {

    private final int[][] adjacencyMatrix;

    public Graph(int verticesCount) {
        this.adjacencyMatrix = new int[verticesCount][verticesCount];
    }

    public void addDirectedEdge(int source, int destination) {
        this.adjacencyMatrix[source][destination] = 1;
    }

    public void removeDirectedEdge(int source, int destination) {
        this.adjacencyMatrix[source][destination] = 0;
    }

    public boolean isDirectedEdge(int source, int destination) {
        return this.adjacencyMatrix[source][destination] == 1;
    }

    public int verticesCount() {
        return this.adjacencyMatrix.length;
    }

    @Override
    public String toString() {
        StringBuilder graphString = new StringBuilder();
        for (int[] matrix : adjacencyMatrix) {
            for (int i : matrix) {
                graphString.append(i);
                graphString.append(" ");
            }
            graphString.append("\n");
        }
        return graphString.toString();
    }
}
