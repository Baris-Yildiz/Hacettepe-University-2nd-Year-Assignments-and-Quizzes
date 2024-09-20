import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Experiment {
    protected List<Integer> recordList = new ArrayList<>();
    protected List<int[]> dataList = new ArrayList<>();
    protected List<int[]> sortedDataList = new ArrayList<>();



    public Experiment(String fileName) throws FileNotFoundException {
        readRecords(fileName);
        initializeDataList();
    }

    public void initializeDataList() {
        int N = 500;
        for (int i = 0; i < 10; i++) {
            if (i == 9) N = 250000;

            int[] data = new int[N];
            for (int j = 0; j < N; j++) {
                data[j] = recordList.get(j);
            }

            dataList.add(data);
            N*=2;
        }
    }

    public void readRecords(String recordFile) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File(recordFile));
        scanner.nextLine();

        while(scanner.hasNextLine()) {
            String[] stringParts = scanner.nextLine().split(";");
            int record = Integer.parseInt(stringParts[6]);
            recordList.add(record);
        }
    }


    protected int[] createRandomArrayOfSize(int N, boolean sort, boolean reverse) {

        List<int[]> sourceList = (sort && !sortedDataList.isEmpty()) ? sortedDataList : dataList;

        int[] newArray = sourceList.get((int)Math.ceil(Math.log(N/500) / Math.log(2)));

        if (reverse) {
            for (int i = 0; i < N/2; i++) {
                int temp = newArray[i];
                newArray[i] = newArray[N-i-1];
                newArray[N-i-1] = temp;
            }
        }

        return newArray;
    }

    public List<int[]> getSortedDataList() {
        return sortedDataList;
    }

    public void setSortedDataList(List<int[]> sortedDataList) {
        this.sortedDataList = sortedDataList;
    }
}
