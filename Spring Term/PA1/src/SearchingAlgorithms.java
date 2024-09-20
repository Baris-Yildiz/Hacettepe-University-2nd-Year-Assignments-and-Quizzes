public class SearchingAlgorithms {

    public static int linearSearch(int[] arr, int x) {
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == x) {
                return i;
            }
        }
        return -1;
    }

    public static int binarySearch(int[] arr, int x) {
        int low = 0;
        int high = arr.length-1;

        while (low <= high) {
            int mid = low + (high-low)/2;
            int midValue = arr[mid];

            if (midValue == x) {
                return mid;
            } else if (midValue < x) {
                low = mid+1;
            } else {
                high = mid-1;
            }
        }

        return -1;
    }
}
