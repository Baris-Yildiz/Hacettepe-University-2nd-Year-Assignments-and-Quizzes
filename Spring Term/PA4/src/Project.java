import java.io.Serializable;
import java.util.*;

public class Project implements Serializable {
    static final long serialVersionUID = 33L;

    // The DirectedGraph class represents a class that has Tasks as vertices and edges representing dependency. Used to get a topological order for doing tasks.
    private static class DirectedGraph {
        List<Integer>[] adjacencyList;

        public DirectedGraph(int V) {
            adjacencyList = new ArrayList[V];
            for (int i = 0; i < V; i++) {
                adjacencyList[i] = new ArrayList<>();
            }
        }

        public void addDirectedEdge(int from, int to) {
            adjacencyList[from].add(to);
        }
    }

    // The DFS class is a class that runs DFS on an input graph and gets the topological order of it.
    private static class DFS {

        DirectedGraph directedGraph;
        HashSet<Integer> visitedVertices = new HashSet<>();
        Stack<Integer> postOrder = new Stack<>();
        List<Integer> topologicalOrder = new ArrayList<>();


        public DFS(DirectedGraph directedGraph) {
            this.directedGraph = directedGraph;
        }

        public void topologicalSort() {
            dfs(0);

            while (!postOrder.empty()){
                topologicalOrder.add(postOrder.pop());
            }
        }

        private void dfs(int vertex) {
            visitedVertices.add(vertex);
            for(Integer v: directedGraph.adjacencyList[vertex]) {
                if (!visitedVertices.contains(v)) {
                    dfs(v);
                }
            }
            postOrder.push(vertex);
        }

        public List<Integer> getTopologicalOrder() {
            return topologicalOrder;
        }

    }

    public DirectedGraph taskGraph; //graph with tasks as vertices and edges as dependencies.
    public DFS dfs; //instance of the DFS class
    private final String name; //name of the project
    private final List<Task> tasks; //tasks to do in order to complete the project.

    // Constructor initializes name and tasks instance variables.
    public Project(String name, List<Task> tasks) {
        this.name = name;
        this.tasks = tasks;
    }

    /**
     * Adds Edges to the DirectedGraph object. The Edges are from the dependencies to the dependee.
     */
    private void createEdges() {
        for (Task task: tasks) {
            for (Integer dependentTaskID: task.getDependencies()) {
                taskGraph.addDirectedEdge(dependentTaskID, task.getTaskID());
            }
        }
    }

    /**
     * @return the total duration of the project in days
     */
    public int getProjectDuration() {
        int[] schedule = getEarliestSchedule();
        return tasks.get(schedule.length-1).getDuration() + schedule[schedule.length-1];
    }

    /**
     * Schedule all tasks within this project such that they will be completed as early as possible.
     *
     * @return An integer array consisting of the earliest start days for each task.
     */
    public int[] getEarliestSchedule() {
        taskGraph = new DirectedGraph(tasks.size());
        createEdges();

        dfs = new DFS(taskGraph);
        dfs.topologicalSort();

        List<Integer> topologicalOrder = dfs.getTopologicalOrder();
        int[] schedule = new int[tasks.size()];

        schedule[0] = 0;

        for (int i = 1; i < topologicalOrder.size(); i++) {
            Task currentTask = tasks.get(topologicalOrder.get(i));
            int maxEndTime = 0;
            for (int j = i-1; j > -1; j--) {
                Task otherTask = tasks.get(topologicalOrder.get(j));
                if (currentTask.getDependencies().contains(otherTask.getTaskID())) {
                    maxEndTime = Math.max(maxEndTime, schedule[otherTask.getTaskID()] + otherTask.getDuration());
                }

                schedule[currentTask.getTaskID()] = maxEndTime;
            }
        }

        return schedule;
    }

    public static void printlnDash(int limit, char symbol) {
        for (int i = 0; i < limit; i++) System.out.print(symbol);
        System.out.println();
    }

    /**
     * Some free code here. YAAAY! 
     */
    public void printSchedule(int[] schedule) {
        int limit = 65;
        char symbol = '-';
        printlnDash(limit, symbol);
        System.out.println(String.format("Project name: %s", name));
        printlnDash(limit, symbol);

        // Print header
        System.out.println(String.format("%-10s%-45s%-7s%-5s","Task ID","Description","Start","End"));
        printlnDash(limit, symbol);
        for (int i = 0; i < schedule.length; i++) {
            Task t = tasks.get(i);
            System.out.println(String.format("%-10d%-45s%-7d%-5d", i, t.getDescription(), schedule[i], schedule[i]+t.getDuration()));
        }
        printlnDash(limit, symbol);
        System.out.println(String.format("Project will be completed in %d days.", tasks.get(schedule.length-1).getDuration() + schedule[schedule.length-1]));
        printlnDash(limit, symbol);
    }

    /**
     * @return true if object O as a project is equal to this project.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Project project = (Project) o;

        int equal = 0;

        for (Task otherTask : ((Project) o).tasks) {
            if (tasks.stream().anyMatch(t -> t.equals(otherTask))) {
                equal++;
            }
        }

        return name.equals(project.name) && equal == tasks.size();
    }

}
