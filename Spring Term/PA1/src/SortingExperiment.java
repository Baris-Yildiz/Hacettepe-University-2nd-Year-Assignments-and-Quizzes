import java.io.FileNotFoundException;
import java.util.*;

public class SortingExperiment extends Experiment {

    public SortingExperiment(String fileName) throws FileNotFoundException {
        super(fileName);
    }

    public double[][] testSortingAlgorithms(boolean sort, boolean reverse) {
        int N = 500;
        double insertionTime, mergeTime, countingTime;
        double[][] executionTimes = new double[3][10];

        int[] testArray = new int[0];

        for (int i = 0; i < 10; i++) {
            insertionTime = mergeTime = countingTime = 0;
            if (i == 9) N = 250000;

            for (int j = 0; j < 10; j++) {
                testArray = createRandomArrayOfSize(N, sort, reverse);
                mergeTime += testMergeSort(testArray);
                countingTime += testCountingSort(testArray);
                insertionTime += testInsertionSort(testArray);
            }

            System.out.println("Input Size: " + N + "\n\nInsertion Sort: " + insertionTime/10.0 + "ms.\nMerge Sort: "
                    + mergeTime/10.0 + "ms.\nCounting Sort: " + countingTime/10.0 + "ms.\n");

            executionTimes[0][i] = insertionTime/10.0;
            executionTimes[1][i] = mergeTime/10.0;
            executionTimes[2][i] = countingTime/10.0;

            if (sortedDataList.size() < 10) {
                sortedDataList.add(testArray);
            }

            N *=2;
        }



        return executionTimes;
    }

    private long testInsertionSort(int[] arr) {
        long startTime = System.nanoTime();
        SortingAlgorithms.insertionSort(arr);
        return (System.nanoTime() - startTime) / 1000000;
    }

    private long testMergeSort(int[] arr) {
        long startTime = System.nanoTime();
        SortingAlgorithms.mergeSort(arr);
        return (System.nanoTime() - startTime) / 1000000;
    }

    private long testCountingSort(int[] arr) {
        long startTime = System.nanoTime();
        SortingAlgorithms.countingSort(arr);
        return (System.nanoTime() - startTime) / 1000000;
    }
}
