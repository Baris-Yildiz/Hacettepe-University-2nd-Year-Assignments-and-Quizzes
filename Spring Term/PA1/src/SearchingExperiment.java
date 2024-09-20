import java.io.FileNotFoundException;
import java.util.concurrent.ThreadLocalRandom;

public class SearchingExperiment extends Experiment{
    public SearchingExperiment(String fileName) throws FileNotFoundException {
        super(fileName);
    }

    public double[][] testSearchingAlgorithms() {
        int N = 500;
        double linearTime, binaryTime;
        double[][] executionTimes = new double[3][10];

        for (int i = 0; i < 10; i++) {
            linearTime = binaryTime = 0;
            if (i == 9) N = 250000;
            System.out.println("Input Size: " + N);
            int[] testArray = createRandomArrayOfSize(N, false, false);

            for (int j = 0; j < 1000; j++) {
                int searchIndex = ThreadLocalRandom.current().nextInt(0, N);
                linearTime += testLinearSearch(testArray, testArray[searchIndex]);
            }

            linearTime /= 1000.0;
            System.out.println("\nLinear Search on Random Data: " + linearTime + "ns.");
            executionTimes[0][i] = linearTime;

            linearTime = 0;
            testArray = createRandomArrayOfSize(N, true, false);
            for (int j = 0; j < 1000; j++) {
                int searchIndex = ThreadLocalRandom.current().nextInt(0, N);
                linearTime += testLinearSearch(testArray, testArray[searchIndex]);
                binaryTime += testBinarySearch(testArray, testArray[searchIndex]);
            }

            linearTime /= 1000.0;
            binaryTime /= 1000.0;

            System.out.println("Linear Search on Sorted Data: " + linearTime + "ns.\nBinary Search (sorted data): "
                    + binaryTime + "ns.\n");

            executionTimes[1][i] = linearTime;
            executionTimes[2][i] = binaryTime;

            N *=2;
        }

        return executionTimes;
    }

    private long testLinearSearch(int[] arr, int data) {
        long startTime = System.nanoTime();
        SearchingAlgorithms.linearSearch(arr, data);
        return (System.nanoTime() - startTime);
    }

    private long testBinarySearch(int[] arr, int data) {
        long startTime = System.nanoTime();
        SearchingAlgorithms.binarySearch(arr, data);
        return (System.nanoTime() - startTime);
    }
}
