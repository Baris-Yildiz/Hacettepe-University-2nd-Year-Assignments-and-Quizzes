import java.util.ArrayList;

/**
 * This class accomplishes Mission POWER GRID OPTIMIZATION
 */
public class PowerGridOptimization {
    private ArrayList<Integer> amountOfEnergyDemandsArrivingPerHour;

    public PowerGridOptimization(ArrayList<Integer> amountOfEnergyDemandsArrivingPerHour){
        this.amountOfEnergyDemandsArrivingPerHour = amountOfEnergyDemandsArrivingPerHour;
    }

    public ArrayList<Integer> getAmountOfEnergyDemandsArrivingPerHour() {
        return amountOfEnergyDemandsArrivingPerHour;
    }
    /**
     *     Function to implement the given dynamic programming algorithm
     *     SOL(0) <- 0
     *     HOURS(0) <- [ ]
     *     For{j <- 1...N}
     *         SOL(j) <- max_{0<=i<j} [ (SOL(i) + min[ E(j), P(j − i) ] ]
     *         HOURS(j) <- [HOURS(i), j]
     *     EndFor
     *
     * @return OptimalPowerGridSolution
     */
    public OptimalPowerGridSolution getOptimalPowerGridSolutionDP(){
        OptimalPowerGridSolution[] dp = new OptimalPowerGridSolution[amountOfEnergyDemandsArrivingPerHour.size()+1];
        dp[0] = new OptimalPowerGridSolution();

        for (int j = 1; j < dp.length; j++) {

            int maxSolution = Math.min(amountOfEnergyDemandsArrivingPerHour.get(j-1), (j*j));
            int maxHoursIndex = 0;

            for (int i = 1; i < j; i++) {
                int nextSolution = dp[i].getmaxNumberOfSatisfiedDemands() +
                        Math.min(amountOfEnergyDemandsArrivingPerHour.get(j-1), ((j-i)*(j-i)));

                if (nextSolution > maxSolution) {
                    maxSolution = nextSolution;
                    maxHoursIndex = i;
                }
            }

            ArrayList<Integer> maxHours = new ArrayList<>();
            for(int hour: dp[maxHoursIndex].getHoursToDischargeBatteriesForMaxEfficiency()) {
                maxHours.add(hour);
            }
            maxHours.add(j);

            dp[j] = new OptimalPowerGridSolution(maxSolution, maxHours);
        }
        return dp[dp.length-1];
    }
}
