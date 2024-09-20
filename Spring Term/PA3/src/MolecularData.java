import java.util.*;

// Class representing molecular data
public class MolecularData {

    // Private fields
    private static class DirectedGraph {
        private final Map<String, List<Bond>> adjacencyList;  //adjacency list of the directed graph
        private final List<Molecule> molecules;   // list of molecules(vertices) in the graph

        // Constructor initializes the adjacency list.
        public DirectedGraph(List<Molecule> molecules) {
            adjacencyList = new HashMap<>();
            this.molecules = molecules;
        }

        // Constructs the graph using the list of molecules and the bonds of the molecules.
        public void constructAdjacencyList() {
            for(Molecule fromMolecule: molecules) {
                for(String bondID: fromMolecule.getBonds()) {
                    Molecule toMolecule = null;
                    for (Molecule other: molecules) {
                        if (other.getId().equals(bondID)) {
                            toMolecule = other;
                            break;
                        }
                    }

                    Bond bond = new Bond(toMolecule, fromMolecule, (double)toMolecule.getBondStrength());
                    addEdge(fromMolecule, bond);

                    bond = new Bond(fromMolecule, toMolecule, (double)fromMolecule.getBondStrength());
                    addEdge(toMolecule, bond);
                }

            }
        }

        // Used for forming bonds directed from molecule "a".
        private void addEdge(Molecule a, Bond bond) {
            if (adjacencyList.get(a.getId()) == null) {
                adjacencyList.put(a.getId(), new ArrayList<>());
            } else if(adjacencyList.get(a.getId()).contains(bond)) {
                return;
            }

            adjacencyList.get(a.getId()).add(bond);
        }

        // Getter for the molecule list.
        public List<Molecule> getMolecules() {
            return molecules;
        }

        // Getter for the adjacency list.
        public Map<String, List<Bond>> getAdjacencyList() {
            return adjacencyList;
        }
    }
    // Class that runs the DFS algorithm on a graph.
    private static class DFS {
        private final DirectedGraph directedGraph;  // graph on which the DFS algorithm will be executed.
        private final Set<String> visitedMolecules = new HashSet<>();   // set that contains the id of molecules visited by the DFS algorithm so far.

        // Constructor that initializes the graph.
        public DFS(DirectedGraph directedGraph) {
            this.directedGraph = directedGraph;
        }

        // Gets the connected components of the graph which represents molecular structures. Makes use of the DFS algorithm.
        public ArrayList<MolecularStructure> getConnectedComponents() {
            ArrayList<MolecularStructure> molecularStructures = new ArrayList<>();

            for (Molecule molecule: directedGraph.getMolecules()) {
                if (!visitedMolecules.contains(molecule.getId())) {
                    MolecularStructure molecularStructure = new MolecularStructure();
                    dfs(molecule, molecularStructure);
                    molecularStructures.add(molecularStructure);
                }
            }

            return molecularStructures;
        }

        // DFS algorithm : Visits a molecule and recursively visits other molecules that have bonds with it.
        private void dfs(Molecule molecule, MolecularStructure molecularStructure) {
            molecularStructure.addMolecule(molecule);
            visitedMolecules.add(molecule.getId());

            for(Bond bond: directedGraph.getAdjacencyList().get(molecule.getId())) {
                Molecule visitMolecule = bond.getTo();
                if (!visitedMolecules.contains(visitMolecule.getId())) {
                    dfs(visitMolecule,molecularStructure);
                }
            }
        }

    }
    private final List<Molecule> molecules; // List of molecules

    private final DirectedGraph moleculeGraph; // Graph of molecules

    // Constructor
    public MolecularData(List<Molecule> molecules) {
        this.molecules = molecules;
        moleculeGraph = new DirectedGraph(molecules);
        moleculeGraph.constructAdjacencyList();
    }

    // Getter for molecules
    public List<Molecule> getMolecules() {
        return molecules;
    }

    // Method to identify molecular structures
    // Return the list of different molecular structures identified from the input data
    public List<MolecularStructure> identifyMolecularStructures() {
        DFS dfs = new DFS(moleculeGraph);
        return dfs.getConnectedComponents();
    }

    // Method to print given molecular structures
    public void printMolecularStructures(List<MolecularStructure> molecularStructures, String species) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append(molecularStructures.size()).append(" molecular structures have been discovered in ")
                .append(species).append(".\n");

        for (int i = 0; i < molecularStructures.size(); i++) {
            stringBuilder.append("Molecules in Molecular Structure ").append(i+1).append(": ")
                    .append(molecularStructures.get(i)).append("\n");
        }

        System.out.print(stringBuilder);
    }

    // Method to identify anomalies given a source and target molecular structure
    // Returns a list of molecular structures unique to the targetStructure only
    public static ArrayList<MolecularStructure> getVitalesAnomaly(List<MolecularStructure> sourceStructures, List<MolecularStructure> targetStructures) {
        ArrayList<MolecularStructure> anomalyList = new ArrayList<>();

        for (MolecularStructure targetStructure : targetStructures) {
            boolean unique = true;
            for (MolecularStructure sourceStructure : sourceStructures) {
                if (targetStructure.equals(sourceStructure)) {
                    unique = false;
                    break;
                }
            }

            if (unique) {
                anomalyList.add(targetStructure);
            }
        }
        return anomalyList;
    }

    // Method to print Vitales anomalies
    public void printVitalesAnomaly(List<MolecularStructure> molecularStructures) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Molecular structures unique to Vitales individuals: \n");

        for (MolecularStructure molecularStructure : molecularStructures) {
            stringBuilder.append(molecularStructure).append("\n");
        }

        System.out.print(stringBuilder);
    }
}
