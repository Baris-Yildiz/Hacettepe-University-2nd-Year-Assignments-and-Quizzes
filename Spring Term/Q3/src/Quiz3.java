import java.util.*;
import java.io.*;

class Edge {
    private double weight;
    private int v;
    private int w;

    public Edge(double weight, int v, int w) {
        this.weight = weight;
        this.v = v;
        this.w = w;
    }

    public int getV() {
        return v;
    }

    public int getW() {
        return w;
    }

    public double getWeight() {
        return weight;
    }
}

class EdgeComparator implements Comparator<Edge> {

    @Override
    public int compare(Edge o1, Edge o2) {
        if (o1.getWeight() > o2.getWeight()) {
            return 1;
        } else {
            return (o1.getWeight() < o2.getWeight()) ? -1: 0;
        }

    }
}

class Vertex {
    private int x;
    private int y;
    private int id;

    public Vertex(int x, int y, int id) {
        this.x = x;
        this.y = y;
        this.id = id;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public int getId() {
        return id;
    }
}

class UndirectedGraph {

    private int V;
    private List<Edge>[] adjList;
    private Vertex[] vertexList;

    public UndirectedGraph(int vertices) {
        adjList = new ArrayList[vertices];
        for (int i = 0; i < vertices; i++) {
            adjList[i] = new ArrayList<>();
        }

        vertexList = new Vertex[vertices];
        V = vertices;
    }

    public void addVertex(Vertex vertex) {
        vertexList[vertex.getId()] = vertex;
    }

    public void addEdges() {
        for (int i = 0; i < vertexList.length; i++) {

            for (int j = i+1; j < vertexList.length; j++) {
                double distance = Math.sqrt(Math.pow(vertexList[i].getX() - vertexList[j].getX(), 2) +
                Math.pow(vertexList[i].getY() - vertexList[j].getY(), 2));

                Edge edge = new Edge(distance, i, j);
                adjList[i].add(edge);
                adjList[j].add(edge);
            }
        }
    }

    public List<Edge> edgesOf(int vertexID) {
        return adjList[vertexID];
    }

    public int getV() {
        return V;
    }
}

class MST {
    List<Edge> edgeList = new ArrayList<>();
    PriorityQueue<Edge> priorityQueue = new PriorityQueue<>(new EdgeComparator());
    UndirectedGraph graph;
    boolean[] marked;
    public MST(UndirectedGraph graph) {
        this.graph = graph;
        marked = new boolean[graph.getV()];
        computeMST();
    }

    private void computeMST() {
        visit(0);

        while(!priorityQueue.isEmpty()) {
            Edge edge = priorityQueue.poll();
            if (marked[edge.getV()] && marked[edge.getW()]) continue;
            edgeList.add(edge);
            if (!marked[edge.getW()]) visit(edge.getW());
            if (!marked[edge.getV()]) visit(edge.getV());
        }

    }

    private void visit(int vertexIndex) {
        marked[vertexIndex] = true;

        for(Edge edge: graph.edgesOf(vertexIndex)) {
            if (!marked[edge.getV()] || !marked[edge.getW()]) {
                priorityQueue.add(edge);
            }
        }
    }

    public double maxWeight(int S) {
        edgeList.sort(new EdgeComparator());
        return Math.round(edgeList.get(edgeList.size()-S).getWeight() * 100) / 100.0;
    }


}

public class Quiz3 {
    public static void main(String[] args) throws IOException {
        Scanner scanner = new Scanner(new File(args[0]));
        int t = scanner.nextInt();

        for (int i = 0; i < t; i++) {
            int S = scanner.nextInt();
            int P = scanner.nextInt();

            UndirectedGraph undirectedGraph = new UndirectedGraph(P);

            for (int j = 0; j < P; j++) {
                int x = scanner.nextInt();
                int y = scanner.nextInt();

                Vertex vertex = new Vertex(x, y, j);
                undirectedGraph.addVertex(vertex);
            }

            undirectedGraph.addEdges();
            MST mst = new MST(undirectedGraph);
            System.out.printf("%.2f\n", mst.maxWeight(S));
        }

        // TODO: Use the first command line argument (args[0]) as the file to read the input from
        // TODO: Your code goes here
        // TODO: Print the solution to STDOUT
    }
}
