import java.util.*;
import java.io.*;

public class Quiz2 {
    public static void main(String[] args) throws IOException {

        Scanner scanner = new Scanner(new File(args[0]));
        int M = scanner.nextInt();
        int n = scanner.nextInt();

        int[] items = new int[n];
        int maxLoad = 0;

        for (int i = 0; i < n; i++) {
            items[i] = scanner.nextInt();
        }

        boolean[][] dp = new boolean[M+1][n+1];

        for (int i = 0; i <= n; i++) {
            dp[0][i] = true;
        }

        for (int i = 1; i <= M; i++) {
            dp[i][0] = false;
        }

        for (int i = 1; i <= M; i++) {
            for (int j = 1; j <= n; j++) {
                if (i - items[j-1] < 0) {
                    dp[i][j] = dp[i][j-1];
                } else {
                    dp[i][j] = dp[i][j-1] || dp[i-items[j-1]][j-1];
                }

                if (dp[i][j]) {
                    maxLoad = i;
                }

            }
        }

        System.out.println(maxLoad);

        for (int i = 0; i <= M; i++) {
            for (int j = 0; j <= n; j++) {
                System.out.print(dp[i][j] ? 1:0);
            }
            System.out.println();
        }
        // TODO: Use the first command line argument (args[0]) as the file to read the input from
        // TODO: Your code goes here
        // TODO: Print the solution to STDOUT
    }
}
