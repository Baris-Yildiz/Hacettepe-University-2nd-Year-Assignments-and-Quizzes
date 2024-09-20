import java.io.Serializable;

public class RouteDirection implements Serializable {
    static final long serialVersionUID = 44L;
    public String startStationName; // description of the starting station.
    public String endStationName; //description of the destination station.
    public double duration; //duration of the route
    boolean trainRide; // true if it's a ride on train, false if it's a walk.

    public RouteDirection(String startStationName, String endStationName, double duration, boolean trainRide) {
        this.startStationName = startStationName;
        this.endStationName = endStationName;
        this.duration = duration;
        this.trainRide = trainRide;
    }

} 