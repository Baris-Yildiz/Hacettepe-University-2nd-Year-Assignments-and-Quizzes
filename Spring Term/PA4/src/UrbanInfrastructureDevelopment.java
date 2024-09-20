import java.io.File;
import java.io.FileNotFoundException;
import java.io.Serializable;
import java.util.*;

public class UrbanInfrastructureDevelopment implements Serializable {
    static final long serialVersionUID = 88L;

    /**
     * Given a list of Project objects, prints the schedule of each of them.
     * Uses getEarliestSchedule() and printSchedule() methods of the current project to print its schedule.
     * @param projectList a list of Project objects
     */
    public void printSchedule(List<Project> projectList) {

        for (Project project: projectList) {
            project.printSchedule(project.getEarliestSchedule());
        }
    }

    /**
     * Parse the input XML file and return a list of Project objects
     *
     * @param filename the input XML file
     * @return a list of Project objects
     */
    public List<Project> readXML(String filename) {

        List<Project> projectList = new ArrayList<>();
        Scanner scanner;

        try {
            scanner = new Scanner(new File(filename));
        } catch (FileNotFoundException e) {
            return null;
        }

        StringBuilder stringBuilder = new StringBuilder();
        while (scanner.hasNextLine()) {
            String nextLine = scanner.nextLine().trim();
            if (!nextLine.isEmpty()) {
                stringBuilder.append(nextLine).append("\n");
            }
        }

        scanner = new Scanner(stringBuilder.toString());

        while (scanner.hasNextLine()) {
            scanner.nextLine();
            scanner.nextLine();

            if (scanner.hasNextLine()) {
                projectList.add(readProject(scanner));
            }
        }

        return projectList;
    }

    /**
     * Helper method for readXML(). Reads in between the <Project> tags.
     * @return the corresponding Project object.
     */
    private Project readProject(Scanner scanner) {
        String nextLine = scanner.nextLine();
        String projectName = nextLine.substring(6,nextLine.length()-7);
        scanner.nextLine();

        List<Task> tasks = readTasks(scanner);

        return new Project(projectName, tasks);
    }

    /**
     * Helper method for readProject(). Reads in between the <Tasks> tags.
     * @return a list of corresponding Task objects.
     */
    private List<Task> readTasks(Scanner scanner) {
        List<Task> tasks = new ArrayList<>();

        String nextLine = scanner.nextLine();
        while (!nextLine.equals("</Tasks>")) {
            tasks.add(readTask(scanner));
            nextLine = scanner.nextLine();
        }

        return tasks;
    }


    /**
     * Helper method for readTasks(). Reads in between the <Task> tags
     * @return the corresponding Task object.
     */
    private Task readTask(Scanner scanner) {
        String nextLine = scanner.nextLine();
        int taskID = Integer.parseInt(nextLine.substring(8, nextLine.length()-9));

        nextLine = scanner.nextLine();
        String taskDescription = nextLine.substring(13, nextLine.length()-14);

        nextLine = scanner.nextLine();
        int taskDuration = Integer.parseInt(nextLine.substring(10, nextLine.length()-11));

        List<Integer> dependencies = new ArrayList<>();
        nextLine = scanner.nextLine();

        if (!nextLine.equals("<Dependencies></Dependencies>") && !nextLine.equals("<Dependencies/>")) {
            dependencies = readDependencies(scanner);
        }

        scanner.nextLine();
        return new Task(taskID, taskDescription, taskDuration, dependencies);
    }

    /**
     * Helper method for readTask(). Reads in between the <Dependencies> tags.
     * @return a list of corresponding ID's of dependencies.
     */
    private List<Integer> readDependencies(Scanner scanner) {
        List<Integer> dependencies = new ArrayList<>();
        String nextLine = scanner.nextLine();

        while(!nextLine.equals("</Dependencies>")) {
            dependencies.add(Integer.parseInt(nextLine.substring(17, nextLine.length()-18)));
            nextLine = scanner.nextLine();
        }
        return dependencies;
    }
}
