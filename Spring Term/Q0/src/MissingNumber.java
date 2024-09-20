import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

class MissingNumber {

    public static void main(String[] args) throws FileNotFoundException {
        int n = Integer.parseInt(args[0]);
        String fileName = args[1];
        
        Scanner scanner = new Scanner(new File(fileName));
        int[] arr = new int[n];

        for (int i = 0; i < n; i++) {
            arr[i] = scanner.nextInt();
        }

        int sum = (n * (n+1)) / 2;
        for (int i = 0; i < n; i++) {
            sum -= arr[i];
        }

        System.out.println(sum);

        // First command-line argument refers to the number of integers
        // Second command-line argument contains the path to the input file
        // Your program should only print a single integer to the standard output
        // For the sample input, your output should be:
        // 2
    }

}