import java.util.*;

// Class representing the Mission Synthesis
public class MissionSynthesis {

    private static class UndirectedGraph {
        //Private fields
        private final Map<String, List<Molecule>> adjacencyList;
        private final List<Molecule> molecules;
        // Constructor
        public UndirectedGraph(List<Molecule> molecules) {
            adjacencyList = new HashMap<>();
            this.molecules = molecules;
        }
        // Adds edges so that every molecule is connected to every other molecule.
        public void constructGraph() {
            for(int i = 0; i < molecules.size(); i++) {
                for (int j = i+1; j < molecules.size(); j++) {
                    addEdge(molecules.get(i), molecules.get(j));
                    addEdge(molecules.get(j), molecules.get(i));
                }
            }
        }
        // Adds molecules a and b together.
        private void addEdge(Molecule a, Molecule b) {
            if (adjacencyList.get(a.getId()) == null) {
                adjacencyList.put(a.getId(), new ArrayList<>());
            }

            adjacencyList.get(a.getId()).add(b);
        }
        // Getter for adjacency list.
        public Map<String, List<Molecule>> getAdjacencyList() {
            return adjacencyList;
        }

        // Getter for the list of molecules in the graph.
        public List<Molecule> getMolecules() {
            return molecules;
        }
    }
    private static class MST {

        // Private fields
        private final UndirectedGraph graph;
        private final PriorityQueue<Bond> priorityQueue;
        private final List<Bond> mstBonds;
        private final HashSet<String> visitedMolecules = new HashSet<>();

        // Constructor initializes private fields and calls computeMST().
        public MST(UndirectedGraph graph) {
            this.graph = graph;
            priorityQueue = new PriorityQueue<>(new Bond.BondComparator());
            mstBonds = new ArrayList<>();
            computeMST();
        }

        // Finds a minimum spanning tree on the graph using Prim's Algorithm. The minimum spanning tree will represent the "serum".
        private void computeMST() {
            visitMolecule(graph.getMolecules().get(0));

            while(!priorityQueue.isEmpty()) {
                Bond bond = priorityQueue.poll();
                if (visitedMolecules.contains(bond.getTo().getId()) && visitedMolecules.contains(bond.getFrom().getId())) continue;
                mstBonds.add(bond);
                if (!visitedMolecules.contains(bond.getTo().getId())) visitMolecule(bond.getTo());
                if (!visitedMolecules.contains(bond.getFrom().getId())) visitMolecule(bond.getFrom());
            }
        }

        // Helper method for computeMST(). Visits a molecule, adding its bonds to the priority queue used in finding the MST.
        private void visitMolecule(Molecule molecule) {
            visitedMolecules.add(molecule.getId());

            for(Molecule other : graph.getAdjacencyList().get(molecule.getId())) {
                if (!visitedMolecules.contains(other.getId())) {
                    Bond bond = new Bond(other, molecule, (Math.abs((other.getBondStrength() + molecule.getBondStrength())/2.0)));
                    priorityQueue.add(bond);
                }
            }
        }
        // Getter method for the edges/bonds of the MST.
        public List<Bond> getMstBonds() {
            return mstBonds;
        }
    }

    // Private fields
    private final List<MolecularStructure> humanStructures; // Molecular structures for humans
    private final ArrayList<MolecularStructure> diffStructures; // Anomalies in Vitales structures compared to humans
    private final ArrayList<Molecule> serumMolecules = new ArrayList<>();

    // Constructor
    public MissionSynthesis(List<MolecularStructure> humanStructures, ArrayList<MolecularStructure> diffStructures) {
        this.humanStructures = humanStructures;
        this.diffStructures = diffStructures;
    }

    // Method to synthesize bonds for the serum
    public List<Bond> synthesizeSerum() {
        getSerumMolecules();
        UndirectedGraph serumGraph = new UndirectedGraph(serumMolecules);
        serumGraph.constructGraph();
        MST mst = new MST(serumGraph);
        return mst.getMstBonds();
    }

    // Selects the minimum-bond-strength molecule from both human and Vitales structures.
    private void getSerumMolecules() {
        getMinimumStrengthMolecule(humanStructures);
        getMinimumStrengthMolecule(diffStructures);
    }

    // Helper method for the getSerumMolecules method. Selects the molecule with the weakest bond strength from a molecular structure and adds it to the list of serum molecules.
    private void getMinimumStrengthMolecule(List<MolecularStructure> molecularStructures) {
        for (MolecularStructure molecularStructure: molecularStructures) {
            serumMolecules.add(molecularStructure.getMoleculeWithWeakestBondStrength());
        }
    }

    // Method to print the synthesized bonds
    public void printSynthesis(List<Bond> serum) {
        StringBuilder stringBuilder = new StringBuilder();
        stringBuilder.append("Typical human molecules selected for synthesis: ")
                .append(serumMolecules.subList(0,humanStructures.size()))
                .append("\nVitales molecules selected for synthesis: ")
                .append(serumMolecules.subList(humanStructures.size(), serumMolecules.size()))
                .append("\nSynthesizing the serum...\n");

        double totalStrength = 0;
        for(Bond bond: serum) {
            ArrayList<Molecule> sortedMolecules = new ArrayList<>();
            sortedMolecules.add(bond.getFrom());
            sortedMolecules.add(bond.getTo());
            Collections.sort(sortedMolecules);

            stringBuilder.append("Forming a bond between ").append(sortedMolecules.get(0)).append(" - ")
                    .append(sortedMolecules.get(1)).append(" with strength ")
                    .append(String.format("%.2f\n", bond.getWeight()));
            totalStrength += bond.getWeight();
        }

        stringBuilder.append(String.format("The total serum bond strength is %.2f\n", totalStrength));
        System.out.print(stringBuilder);

    }
}
