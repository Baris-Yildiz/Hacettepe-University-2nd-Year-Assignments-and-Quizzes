import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

// Class representing the mission of Genesis
public class MissionGenesis {

    // Private fields
    private MolecularData molecularDataHuman; // Molecular data for humans
    private MolecularData molecularDataVitales; // Molecular data for Vitales

    private final List<Molecule> humanMolecules = new ArrayList<>(); // Molecules that are present in humans
    private final List<Molecule> vitalesMolecules = new ArrayList<>(); // Molecules that are present in Vitales

    // Getter for human molecular data
    public MolecularData getMolecularDataHuman() {
        return molecularDataHuman;
    }

    // Getter for Vitales molecular data
    public MolecularData getMolecularDataVitales() {
        return molecularDataVitales;
    }

    // Method to read XML data from the specified filename
    // This method should populate molecularDataHuman and molecularDataVitales fields once called
    public void readXML(String filename) {

        Scanner scanner;
        try {
            scanner = new Scanner(new File(filename));
        } catch (FileNotFoundException exception) {
            throw new RuntimeException(exception);
        }

        while (scanner.hasNextLine()) {
            String nextLine = scanner.nextLine().trim();
            if (nextLine.equals("<HumanMolecularData>")) {
                readMolecularDataFromXML(scanner, true);
            } else if (nextLine.equals("<VitalesMolecularData>")) {
                readMolecularDataFromXML(scanner, false);
            }
        }

        molecularDataHuman = new MolecularData(humanMolecules);
        molecularDataVitales = new MolecularData(vitalesMolecules);
    }

    // Helper method for the readXML method. Reads the content in between the <HumanMolecularData> or <VitalesMolecularData> tags.
    private void readMolecularDataFromXML(Scanner scanner, boolean human) {
        while (true) {
            String nextLine = scanner.nextLine().trim();
            if (nextLine.equals("</HumanMolecularData>") || nextLine.equals("</VitalesMolecularData>")) return;

            if (nextLine.equals("<Molecule>")) {
                readMoleculeFromXML(scanner, human);
            }
        }
    }
    // Helper method for the readMolecularDataFromXML method. Reads the content in between the <Molecule> tags.
    private void readMoleculeFromXML(Scanner scanner, boolean human) {
        String nextLine = scanner.nextLine().trim();
        String moleculeID = nextLine.substring(4,nextLine.length()-5);

        nextLine = scanner.nextLine().trim();
        int bondStrength = Integer.parseInt(nextLine.substring(14, nextLine.length()-15));

        nextLine = scanner.nextLine().trim();
        List<String> bonds = new ArrayList<>();

        if (!nextLine.equals("<Bonds/>")) {
            while (true){
                nextLine = scanner.nextLine().trim();
                if (nextLine.equals("</Bonds>") ) break;
                String bondID = nextLine.substring(12,nextLine.length()-13);
                bonds.add(bondID);
            }
        }

        Molecule molecule = new Molecule(moleculeID, bondStrength, bonds);

        if (human){
            humanMolecules.add(molecule);
        } else {
            vitalesMolecules.add(molecule);
        }
    }
}
