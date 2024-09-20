import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 * This class accomplishes Mission Eco-Maintenance
 */
public class OptimalESVDeploymentGP
{
    private ArrayList<Integer> maintenanceTaskEnergyDemands;

    /*
     * Should include tasks assigned to ESVs.
     * For the sample input:
     * 8 100
     * 20 50 40 70 10 30 80 100 10
     * 
     * The list should look like this:
     * [[100], [80, 20], [70, 30], [50, 40, 10], [10]]
     * 
     * It is expected to be filled after getMinNumESVsToDeploy() is called.
     */
    private ArrayList<ArrayList<Integer>> maintenanceTasksAssignedToESVs = new ArrayList<>();

    ArrayList<ArrayList<Integer>> getMaintenanceTasksAssignedToESVs() {
        return maintenanceTasksAssignedToESVs;
    }

    public OptimalESVDeploymentGP(ArrayList<Integer> maintenanceTaskEnergyDemands) {
        this.maintenanceTaskEnergyDemands = maintenanceTaskEnergyDemands;
    }

    public ArrayList<Integer> getMaintenanceTaskEnergyDemands() {
        return maintenanceTaskEnergyDemands;
    }

    /**
     *
     * @param maxNumberOfAvailableESVs the maximum number of available ESVs to be deployed
     * @param maxESVCapacity the maximum capacity of ESVs
     * @return the minimum number of ESVs required using first fit approach over reversely sorted items.
     * Must return -1 if all tasks can't be satisfied by the available ESVs
     */
    public int getMinNumESVsToDeploy(int maxNumberOfAvailableESVs, int maxESVCapacity)
    {
        if(maxNumberOfAvailableESVs == 0 || maintenanceTaskEnergyDemands.size() == 0) {
            return -1;
        }

        Collections.sort(maintenanceTaskEnergyDemands);
        Collections.reverse(maintenanceTaskEnergyDemands);
        if (maintenanceTaskEnergyDemands.get(0) > maxESVCapacity) {
            return -1;
        }

        int ESVs = 0;
        ArrayList<Integer> ESVList = new ArrayList<>();

        for (Integer maintenanceTaskEnergyDemand : maintenanceTaskEnergyDemands) {
            boolean assigned = false;

            for (int i = 0; i < ESVList.size(); i++) {

                if (ESVList.get(i) + maintenanceTaskEnergyDemand <= maxESVCapacity) {
                    maintenanceTasksAssignedToESVs.get(i).add(maintenanceTaskEnergyDemand);
                    ESVList.set(i, ESVList.get(i)+maintenanceTaskEnergyDemand);
                    assigned = true;
                    break;
                }
            }

            if (!assigned) {
                if (ESVs == maxNumberOfAvailableESVs) {
                    return -1;
                }
                maintenanceTasksAssignedToESVs.add(new ArrayList<>(Arrays.asList(maintenanceTaskEnergyDemand)));
                ESVList.add(maintenanceTaskEnergyDemand);
                ESVs++;
            }
        }

        return ESVs;
    }

}
