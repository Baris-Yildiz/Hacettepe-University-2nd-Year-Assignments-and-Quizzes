import java.io.Serializable;
import java.util.*;

public class TrainLine implements Serializable {
    static final long serialVersionUID = 77L;
    public String trainLineName;
    public List<Station> trainLineStations;
    public TrainLine(String trainLineName, List<Station> trainLineStations) {
        this.trainLineName = trainLineName;
        this.trainLineStations = trainLineStations;
    }
}