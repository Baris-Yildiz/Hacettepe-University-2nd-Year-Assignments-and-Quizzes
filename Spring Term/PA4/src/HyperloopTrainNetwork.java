import java.io.File;
import java.io.FileNotFoundException;
import java.io.Serializable;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HyperloopTrainNetwork implements Serializable {
    static final long serialVersionUID = 11L;
    public double averageTrainSpeed;
    public final double averageWalkingSpeed = 1000 / 6.0;
    public int numTrainLines;
    public Station startPoint;
    public Station destinationPoint;
    public List<TrainLine> lines;

    /**
     * Method with a Regular Expression to extract integer numbers from the fileContent
     * @return the result as int
     */
    public int getIntVar(String varName, String fileContent) {
        Pattern p = Pattern.compile("[\\t ]*" + varName + "[\\t ]*=[\\t ]*([0-9]+)");
        Matcher m = p.matcher(fileContent);
        if (m.find()) {
            return Integer.parseInt(m.group(1));
        } else return 0;
    }

    /**
     * Write the necessary Regular Expression to extract string constants from the fileContent
     * @return the result as String
     */
    public String getStringVar(String varName, String fileContent) {
        Pattern p = Pattern.compile("\\s*" + varName + "\\s*=\\s*\"(.+?)\"");
        Matcher m = p.matcher(fileContent);
        if (m.find()) {
            return m.group(1);
        } else return null;
    }

    /**
     * Write the necessary Regular Expression to extract floating point numbers from the fileContent
     * Your regular expression should support floating point numbers with an arbitrary number of
     * decimals or without any (e.g. 5, 5.2, 5.02, 5.0002, etc.).
     * @return the result as Double
     */
    public Double getDoubleVar(String varName, String fileContent) {

        Pattern p = Pattern.compile("\\s*" + varName + "\\s*=\\s*([0-9]*(\\.[0-9]+)?)");
        Matcher m = p.matcher(fileContent);
        if (m.find()) {
            return Double.parseDouble(m.group(1));
        } else return null;

    }

    /**
     * Write the necessary Regular Expression to extract a Point object from the fileContent
     * points are given as an x and y coordinate pair surrounded by parentheses and separated by a comma
     * @return the result as a Point object
     */
    public Point getPointVar(String varName, String fileContent) {

        Pattern p = Pattern.compile("\\s*" + varName + "\\s*=\\s*\\(\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*\\)");
        Matcher m = p.matcher(fileContent);
        if (m.find()) {
            return new Point(Integer.parseInt(m.group(1)), Integer.parseInt(m.group(2)));
        } else return null;
    }

    /**
     * Function to extract the train lines from the fileContent by reading train line names and their 
     * respective stations.
     * @return List of TrainLine instances
     */
    public List<TrainLine> getTrainLines(String fileContent) {

        Pattern p = Pattern.compile("\"(.+?)\"\\s*.*?\\s*=(\\s*\\(\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*\\)\\s*)+");
        Matcher m = p.matcher(fileContent);

        List<TrainLine> trainLines = new ArrayList<>();
        while (m.find()) {
            trainLines.add(getTrainLine(m.group(1),m.group(0)));
        }
        return trainLines;
    }

    /**
     * Helper method for getTrainLines(). Gets the next train line from the text.
     * @return the next train line in the text as a TrainLine object.
     */
    private TrainLine getTrainLine(String lineName, String fileContent) {
        Pattern p = Pattern.compile("\\(\\s*([0-9]+)\\s*,\\s*([0-9]+)\\s*\\)");
        Matcher m = p.matcher(fileContent);

        int stationIndex = 1;
        List<Station> stations = new ArrayList<>();
        while (m.find()) {
            Station station = new Station(new Point(Integer.parseInt(m.group(1)), Integer.parseInt(m.group(2))),
                    lineName + " Line Station " + stationIndex);
            stationIndex++;
            stations.add(station);
        }

        return new TrainLine(lineName, stations);
    }

    /**
     * Function to populate the given instance variables of this class by calling the functions above.
     */
    public void readInput(String filename) {
        Scanner scanner;

        try {
            scanner = new Scanner(new File(filename));
        } catch (FileNotFoundException e){
            return;
        }

        StringBuilder stringBuilder = new StringBuilder();

        // Gathering the file content as a whole inside a StringBuilder object.
        while(scanner.hasNextLine()) {
            stringBuilder.append(scanner.nextLine()).append("\n");
        }

        // Populating variables
        numTrainLines = getIntVar("num_train_lines", stringBuilder.toString());
        averageTrainSpeed = getDoubleVar("average_train_speed", stringBuilder.toString()) * (1000/60.0);
        startPoint = new Station(getPointVar("starting_point", stringBuilder.toString()), "Starting Point");
        destinationPoint = new Station(getPointVar("destination_point", stringBuilder.toString()), "Final Destination");
        lines = getTrainLines(stringBuilder.toString());

    }
}