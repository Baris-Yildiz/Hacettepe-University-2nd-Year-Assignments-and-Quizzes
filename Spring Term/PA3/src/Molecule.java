import java.util.HashSet;
import java.util.List;

// Class representing a molecule
public class Molecule implements Comparable {
    
    // Private fields
    private final String id; // Unique identifier for the molecule
    private final int bondStrength; // Strength of the bonds in the molecule
    private final List<String> bonds; // List of molecule IDs that this molecule bonds with

    // Constructor
    public Molecule(String id, int bondStrength, List<String> bonds) {
        this.id = id;
        this.bondStrength = bondStrength;
        this.bonds = bonds;
    }

    // Getter for ID
    public String getId() {
        return id;
    }

    // Getter for bond strength
    public int getBondStrength() {
        return bondStrength;
    }

    // Getter for list of bonds
    public List<String> getBonds() {
        return bonds;
    }

    // Override equals method to compare molecules
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Molecule molecule = (Molecule) o;
        // Compare fields for equality
        return bondStrength == molecule.bondStrength &&
                id.equals(molecule.id) &&
                // Use sets to compare lists of bonds for equality, ignoring order
                new HashSet<>(bonds).equals(new HashSet<>(((Molecule) o).getBonds()));
    }

    // Override toString method to provide a string representation of the molecule
    @Override
    public String toString() {
        return id;
    }

    // Override compareTo method to compare molecules for sorting
    @Override
    public int compareTo(Object o) {
        // Convert IDs to integers for comparison
        Integer ownId = Integer.parseInt(this.getId().substring(1));
        Integer oId = Integer.parseInt(((Molecule) o).getId().substring(1));
        // Compare IDs
        return ownId.compareTo(oId);
    }
}
