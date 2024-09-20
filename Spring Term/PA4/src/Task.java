import java.io.Serializable;
import java.util.List;

public class Task implements Serializable {
    static final long serialVersionUID = 66L;
    private final int taskID; // ID of the task. The tasks in a project always start with id 0 and end with id n-1, n being the number of tasks.
    private final String description; // Name of the task.
    private final int duration; //Duration of the task.
    private final List<Integer> dependencies; // Tasks that need to be finished before starting this task.

    public Task(int taskID, String description, int duration, List<Integer> dependencies) {
        this.taskID = taskID;
        this.description = description;
        this.duration = duration;
        this.dependencies = dependencies;
    }

    public int getTaskID() {
        return taskID;
    }

    public String getDescription() {
        return description;
    }

    public int getDuration() {
        return duration;
    }

    public List<Integer> getDependencies() {
        return dependencies;
    }

    /**
     * @return true if Object o as a Task is equal to this task.
     */
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Task task = (Task) o;
        return taskID == task.taskID && duration == task.duration && description.equals(task.description) && dependencies.equals(task.dependencies);
    }
}
