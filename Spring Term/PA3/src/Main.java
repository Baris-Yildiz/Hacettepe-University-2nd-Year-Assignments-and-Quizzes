import java.io.FileNotFoundException;
import java.util.*;

// Main class for running the program
public class Main {
    public static void main(String[] args) {

        // Set the default locale to English
        Locale locale = new Locale("en_EN"); 
        Locale.setDefault(locale);

        // Start of Mission Genesis
        System.out.println("### MISSION GENESIS START ###");
        
        // Initialize MissionGenesis and read XML data
        MissionGenesis missionGenesis = new MissionGenesis();
        missionGenesis.readXML(args[0]);

        // Retrieve human and Vitales molecular data
        MolecularData humanData = missionGenesis.getMolecularDataHuman();
        MolecularData vitalesData = missionGenesis.getMolecularDataVitales();

        // Identify molecular structures for humans and Vitales
        List<MolecularStructure> molecularStructuresHuman = humanData.identifyMolecularStructures();
        List<MolecularStructure> molecularStructuresVitales = vitalesData.identifyMolecularStructures();

        // Print identified molecular structures for humans and Vitales
        humanData.printMolecularStructures(molecularStructuresHuman, "typical humans");
        vitalesData.printMolecularStructures(molecularStructuresVitales, "Vitales individuals");

        // Identify anomalies in human data compared to Vitales data
        ArrayList<MolecularStructure> anomalies = MolecularData.getVitalesAnomaly(molecularStructuresHuman, molecularStructuresVitales);
        humanData.printVitalesAnomaly(anomalies);

        // End of Mission Genesis
        System.out.println("### MISSION GENESIS END ###");


        // Start of Mission Synthesis
        System.out.println("### MISSION SYNTHESIS START ###");

        // Initialize MissionSynthesis with human molecular structures and anomalies
        MissionSynthesis missionSynthesis = new MissionSynthesis(molecularStructuresHuman, anomalies);
        
        // Synthesize bonds for the serum
        List<Bond> synthesis = missionSynthesis.synthesizeSerum();
        
        // Print the synthesized bonds
        missionSynthesis.printSynthesis(synthesis);
        
        // End of Mission Synthesis
        System.out.println("### MISSION SYNTHESIS END ###");
    }
}
