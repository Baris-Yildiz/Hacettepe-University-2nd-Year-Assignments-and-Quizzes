import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class SmallestCharacter {

    public static int f(String s) {
        char min = s.charAt(0);
        for(int i = 1; i < s.length(); i++) {
            if (s.charAt(i) < min) {
                min = s.charAt(i);
            }
        }

        int count = 0;
        for(int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == min) {
                count++;
            }
        }

        return count;
    }

    public static int[] numSmallerByFrequency(String[] queries, String[] words) {
        int[] answer = new int[queries.length];
        int[] fqueries = new int[queries.length];
        int[] fwords = new int[words.length];

        for(int i = 0; i < fqueries.length; i++) {
            fqueries[i] = f(queries[i]);
        }

        for(int j = 0; j < fwords.length; j++) {
            fwords[j] = f(words[j]);
        }

        for(int i = 0; i < fqueries.length; i++) {
            int count = 0;
            for (int j = 0; j < fwords.length; j++) {
                if (fqueries[i] < fwords[j]) {
                    count++;
                }
            }
            answer[i] = count;
        }

        return answer;
    }

    public static void main(String[] args) throws FileNotFoundException {
        String fileName = args[0];

        Scanner scanner = new Scanner(new File(fileName));
        String[] queries = scanner.nextLine().split(" ");
        String[] words = scanner.nextLine().split(" ");

        System.out.println(Arrays.toString(numSmallerByFrequency(queries, words)));


        // First command-line argument contains the path to the input file
        // Structured as below:
        // Line 0: <query-1> <query-2> <query-3> ...
        // Line 1: <word-1> <word-2> <word-3> ...

        // Your program should print to the standard output.
        // Your output should match the given format character-by-character.
        // For example for the sample input:
        // [1]
        // If there are more than one integer to print then:
        // [1,2,3,4,5]
    }
}
