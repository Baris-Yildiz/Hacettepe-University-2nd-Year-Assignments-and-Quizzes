import java.io.Serializable;

public class Point implements Serializable {
    static final long serialVersionUID = 22L;
    
    public int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Calculates the distance between two Point objects and returns the result.
     */
    public static double calculateDistance(Point a, Point b) {
        return Math.sqrt(Math.pow(Math.abs(a.x - b.x), 2) + Math.pow(Math.abs(a.y - b.y), 2));
    }

}
