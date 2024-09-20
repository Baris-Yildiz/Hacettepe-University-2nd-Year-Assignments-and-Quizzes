import java.io.Serializable;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Station implements Serializable {
    static final long serialVersionUID = 55L;

    public Point coordinates; //coordinates of the station as a Point object.
    public String description; //name of the station

    public Station(Point coordinates, String description) {
        this.coordinates = coordinates;
        this.description = description;
    }

    /**
     * @return the line name of the station if it is a train line station, else null.
     */
    public String getLineName() {
        Matcher matcher = Pattern.compile(".+?(?=Station)").matcher(description);
        if (matcher.find()) {
            return matcher.group(0);
        } else return null;

    }

    public String toString() {
        return this.description;
    }

    @Override
    public boolean equals(Object obj) {
        if (obj.getClass() != getClass()) {
            return false;
        }
        Station stationObject = (Station) obj;
        return this.description.equals(stationObject.description);
    }
}
