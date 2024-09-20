public class SortingAlgorithms {

    public static void insertionSort(int[] arr) {
        for (int j = 1; j < arr.length; j++) {
            int key = arr[j];
            int i = j-1;

            while(i>=0 && arr[i] > key) {
                arr[i+1] = arr[i];
                i--;
            }

            arr[i+1] = key;
        }
    }

    public static int[] mergeSort(int[] arr) {
        if (arr.length <= 1) {
            return arr;
        }

        int[] left = new int[arr.length/2];
        System.arraycopy(arr, 0, left, 0, left.length);

        int[] right = new int[arr.length - arr.length/2];
        System.arraycopy(arr, arr.length/2, right, 0, right.length);

        left = mergeSort(left);
        right = mergeSort(right);
        return merge(left, right);
    }

    private static int[] merge(int[] left, int[] right) {
        int[] merged = new int[left.length + right.length];

        int leftPointer = 0, rightPointer = 0, mergedPointer = 0;

        while (leftPointer < left.length && rightPointer < right.length) {
            merged[mergedPointer++] = (left[leftPointer] < right[rightPointer]) ? left[leftPointer++] : right[rightPointer++];
        }

        while (leftPointer < left.length) {
            merged[mergedPointer++] = left[leftPointer++];
        }

        while(rightPointer < right.length) {
            merged[mergedPointer++] = right[rightPointer++];
        }

        return merged;
    }

    public static int[] countingSort(int[] arr) {
        int max = arr[0];

        for (int i = 1; i < arr.length; i++) {
            if (arr[i] > max) {
                max = arr[i];
            }
        }

        int[] countArr = new int[max+1];
        int[] outputArr = new int[arr.length];

        for (int i = 0; i < arr.length; i++) {
            countArr[arr[i]]++;
        }

        for (int i = 1; i < countArr.length; i++) {
            countArr[i] += countArr[i-1];
        }

        for (int i = arr.length-1; i > -1; i--) {
            int j = arr[i];
            countArr[j]--;
            outputArr[countArr[j]] = arr[i];
        }

        return outputArr;
    }

}
