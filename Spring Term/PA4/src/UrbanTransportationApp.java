import java.io.Serializable;
import java.util.*;

class UrbanTransportationApp implements Serializable {
    static final long serialVersionUID = 99L;

    // DirectedStationGraph is a graph that has stations as vertices and RouteDirection objects as edges.
    static class DirectedStationGraph {
        HyperloopTrainNetwork hyperloopTrainNetwork;  //HyperloopTrainNetwork object that the graph works on.
        List<Station> stations = new ArrayList<>();  //List of Stations (vertices)
        HashMap<String, HashSet<RouteDirection>> adjacencyList = new HashMap<>();  //Adjacency list of graph.

        // Constructor initializes vertices and edges.
        public DirectedStationGraph(HyperloopTrainNetwork hyperloopTrainNetwork) {
            this.hyperloopTrainNetwork = hyperloopTrainNetwork;

            stations.add(hyperloopTrainNetwork.startPoint);

            for (TrainLine trainLine: hyperloopTrainNetwork.lines) {
                for (Station station: trainLine.trainLineStations) {
                    stations.add(station);
                }
            }

            stations.add(hyperloopTrainNetwork.destinationPoint);
            addDirections();
        }

        /**
         * Adds edges between vertices where they make sense.
         */
        private void addDirections() {

            for (int i = 1; i < stations.size(); i++) {
                addTwoWayEdgeBetween(stations.get(0), stations.get(i));
            }

            for (int i = 1; i < stations.size()-2; i++) {
                Station currentStation = stations.get(i);

                if (stations.get(i+1).getLineName().equals(currentStation.getLineName())) {
                    addTwoWayEdgeBetween(currentStation, stations.get(i+1));
                }

                for (int j = i+1; j < stations.size()-1; j++) {
                    if (!stations.get(j).getLineName().equals(currentStation.getLineName())) {
                        addTwoWayEdgeBetween(currentStation, stations.get(j));
                    }
                }
            }

            for (int i = 0; i < stations.size()-1; i++) {
                addTwoWayEdgeBetween(stations.get(i), stations.get(stations.size()-1));
            }

        }

        /**
         * Adds a two-way edge between two stations.
         */
        private void addTwoWayEdgeBetween(Station from, Station to) {
            addDirectionBetween(from, to);
            addDirectionBetween(to, from);
        }

        /**
         * Adds a directed edge from Station <b>from</b> to Station <b>to</b> and populates the adjacency list.
         */
        private void addDirectionBetween(Station from, Station to) {

            if (adjacencyList.get(from.toString()) == null) {
                adjacencyList.put(from.toString(), new HashSet<>());
            }

            boolean trainRide;

            if (to.getLineName() == null || from.getLineName() == null) {
                trainRide = false;
            } else {
                trainRide = to.getLineName().equals(from.getLineName());
            }

            double distance = Point.calculateDistance(to.coordinates, from.coordinates);
            double duration = distance / (trainRide ? hyperloopTrainNetwork.averageTrainSpeed : hyperloopTrainNetwork.averageWalkingSpeed);
            RouteDirection routeDirection = new RouteDirection(from.description, to.description, duration, trainRide);

            adjacencyList.get(from.toString()).add(routeDirection);
        }
    }

    // Class that finds the Shortest Paths Tree (SPT) in a given DirectedStationGraph object.
    static class ShortestPath {

        DirectedStationGraph directedStationGraph; // Graph that is worked on.
        HashMap<String, Double> distTo = new HashMap<>();  // Holds station names as keys and their shortest distance from Starting Point as values.
        HashMap<String, RouteDirection> edgeTo = new HashMap<>(); // Holds station names as keys and the nearest edge to them in the shortest path from Starting Point to them as values.
        Set<String> visitedStations = new HashSet<>(); // Keeps track of the visited stations.
        List<RouteDirection> shortestPath = new ArrayList<>(); // Edges in the shortest path from Starting Point to Destination Point.

        public ShortestPath(DirectedStationGraph directedStationGraph) {
            this.directedStationGraph = directedStationGraph;
        }

        /**
         * Runs Dijkstra's Algorithm on the given DirectedStationGraph. Populates every instance variable.
          */
        private void findShortestPath() {

            for (int i = 1; i < directedStationGraph.stations.size(); i++) {
                distTo.put(directedStationGraph.stations.get(i).toString(),Double.POSITIVE_INFINITY);
                edgeTo.put(directedStationGraph.stations.get(i).toString(), null);
            }
            distTo.put(directedStationGraph.stations.get(0).toString(), 0.0);

            for (int i = 0; i < directedStationGraph.stations.size(); i++) {
                double minDistance = Double.POSITIVE_INFINITY;
                String minDistanceStation = "";

                for (String key: distTo.keySet()) {
                    if (visitedStations.contains(key)) continue;
                    if (distTo.get(key) < minDistance) {
                        minDistanceStation = key;
                        minDistance = distTo.get(key);
                    }
                }

                visitedStations.add(minDistanceStation);

                for(RouteDirection routeDirection: directedStationGraph.adjacencyList.get(minDistanceStation)) {
                    relax(routeDirection);
                }
            }

            Stack<RouteDirection> shortestPath = new Stack<>();
            String currentStation = directedStationGraph.stations.get(directedStationGraph.stations.size()-1).toString();

            while (!currentStation.equals("Starting Point")) {
                RouteDirection direction = edgeTo.get(currentStation);
                shortestPath.add(direction);
                currentStation = direction.startStationName;
            }


            while(!shortestPath.empty()) {
                this.shortestPath.add(shortestPath.pop());
            }

        }

        /**
         * Relaxes a RouteDirection object (an edge). Relaxing means checking if there exists a better path from the Starting Point to the
         * vertex pointed from the RouteDirection object. If there exists a better path, changes to distTo value of the station.
         * @param routeDirection
         */
        private void relax(RouteDirection routeDirection) {
            String from = routeDirection.startStationName;
            String to = routeDirection.endStationName;

            if (distTo.get(to) > distTo.get(from) + routeDirection.duration) {
                distTo.put(to, distTo.get(from) + routeDirection.duration);
                edgeTo.put(to, routeDirection);
            }
        }

        public List<RouteDirection> getShortestPath() {
            return shortestPath;
        }
    }

    public HyperloopTrainNetwork readHyperloopTrainNetwork(String filename) {
        HyperloopTrainNetwork hyperloopTrainNetwork = new HyperloopTrainNetwork();
        hyperloopTrainNetwork.readInput(filename);
        return hyperloopTrainNetwork;
    }

    /**
     * Function calculate the fastest route from the user's desired starting point to 
     * the desired destination point, taking into consideration the hyperloop train
     * network. 
     * @return List of RouteDirection instances
     */
    public List<RouteDirection> getFastestRouteDirections(HyperloopTrainNetwork network) {
        DirectedStationGraph directedStationGraph = new DirectedStationGraph(network);
        ShortestPath shortestPath = new ShortestPath(directedStationGraph);
        shortestPath.findShortestPath();
        return shortestPath.getShortestPath();
    }

    /**
     * Function to print the route directions to STDOUT
     */
    public void printRouteDirections(List<RouteDirection> directions) {
        double duration = 0.0;
        for (RouteDirection direction : directions) {
            duration += direction.duration;
        }

        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("The fastest route takes ").append(Math.round(duration)).append(" minute(s).\n").append("Directions\n----------\n");

        for (int i = 0; i < directions.size(); i++) {
            RouteDirection routeDirection = directions.get(i);
            stringBuilder.append(i+1).append(". ");

            stringBuilder.append(routeDirection.trainRide? "Get on the train" : "Walk").append(" from \"")
                    .append(routeDirection.startStationName).append("\" to \"").append(routeDirection.endStationName).append("\" for ")
                    .append(String.format("%.2f", routeDirection.duration)).append(" minutes.\n");
        }

        System.out.println(stringBuilder.toString().trim());

    }
}