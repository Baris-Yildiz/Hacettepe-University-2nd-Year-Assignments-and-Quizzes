import java.io.File;
import java.io.IOException;
import java.util.*;

/**
 * Main class
 */
// FREE CODE HERE
public class Main {
    public static void main(String[] args) throws IOException {

        System.out.println("##MISSION POWER GRID OPTIMIZATION##");
        Scanner demandScanner = new Scanner(new File(args[0]));

        ArrayList<Integer> demands = new ArrayList<>();
        int sum = 0;
        while(demandScanner.hasNextInt()) {
            int demand = demandScanner.nextInt();
            demands.add(demand);
            sum += demand;
        }

        PowerGridOptimization powerGridOptimization = new PowerGridOptimization(demands);
        OptimalPowerGridSolution optimalPowerGridSolution = powerGridOptimization.getOptimalPowerGridSolutionDP();

        String listOfHours = optimalPowerGridSolution.getHoursToDischargeBatteriesForMaxEfficiency().toString();

        System.out.println("The total number of demanded gigawatts: " + sum +
                "\nMaximum number of satisfied gigawatts: " + optimalPowerGridSolution.getmaxNumberOfSatisfiedDemands() +
                "\nHours at which the battery bank should be discharged: " + listOfHours.substring(1, listOfHours.length()-1) +
                "\nThe number of unsatisfied gigawatts: " + (sum - optimalPowerGridSolution.getmaxNumberOfSatisfiedDemands()));
        System.out.println("##MISSION POWER GRID OPTIMIZATION COMPLETED##");

        System.out.println("##MISSION ECO-MAINTENANCE##");
        // TODO: Your code goes here

        Scanner ESVScanner = new Scanner(new File(args[1]));
        ArrayList<Integer> maintenanceTasks = new ArrayList<>();

        int n = ESVScanner.nextInt();
        int capacity = ESVScanner.nextInt();

        while (ESVScanner.hasNextInt()) {
            maintenanceTasks.add(ESVScanner.nextInt());
        }

        OptimalESVDeploymentGP optimalESVDeploymentGP = new OptimalESVDeploymentGP(maintenanceTasks);
        int minimumESVs = optimalESVDeploymentGP.getMinNumESVsToDeploy(n, capacity);

        if (minimumESVs == -1) {
            System.out.println("Warning: Mission Eco-Maintenance Failed.");
        } else {
            System.out.println("The minimum number of ESVs to deploy: " + minimumESVs);

            for (int i = 0; i < minimumESVs; i++) {
                System.out.println("ESV " + (i+1) + " tasks: " + optimalESVDeploymentGP.getMaintenanceTasksAssignedToESVs().get(i).toString());
            }
        }
        System.out.println("##MISSION ECO-MAINTENANCE COMPLETED##");
    }
}
