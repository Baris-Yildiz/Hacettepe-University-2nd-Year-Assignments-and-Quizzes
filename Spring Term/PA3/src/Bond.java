import java.util.Comparator;

// Class representing a bond between two molecules
public class Bond {

    // Comparator for Bond type objects. Used in finding the MST of the serum graph.
    public static class BondComparator implements Comparator<Bond> {
        @Override
        public int compare(Bond o1, Bond o2) {
            if (o1.getWeight() - o2.getWeight() < 0) return -1;
            return o1.getWeight() - o2.getWeight() > 0 ? 1 : 0;
        }
    }

    // Private fields
    private Molecule to; // Molecule to which the bond is directed
    private Molecule from; // Molecule from which the bond originates
    private Double weight; // Weight or strength of the bond

    // Constructor
    public Bond(Molecule to, Molecule from, Double weight) {
        this.to = to;
        this.from = from;
        this.weight = weight;
    }

    // Getter for 'to' molecule
    public Molecule getTo() {
        return to;
    }

    // Getter for 'from' molecule
    public Molecule getFrom() {
        return from;
    }

    // Getter for bond weight
    public Double getWeight() {
        return weight;
    }

    // Check if two Bond type objects have the same fields. Used in constructing the initial molecule graph.
    @Override
    public boolean equals(Object obj) {
        Bond other = (Bond) obj;
        return (other.from.equals(from)) && (other.to.equals(to)) && (other.weight.equals(weight));
    }
}


