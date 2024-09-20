import java.util.*;
import java.io.*;

public class Quiz1 {

    private static class Keyword implements Comparable<Keyword>{
        String sentence;
        String keyword;
        int index;
        int sentenceIndex;

        public Keyword(String sentence, String keyword, int index, int sentenceIndex) {
            this.sentence = sentence;
            this.keyword = keyword;
            this.index = index;
            this.sentenceIndex = sentenceIndex;
        }

        @Override
        public int compareTo(Keyword o) {
            int compareValue = keyword.compareTo(o.keyword);

            if (compareValue > 0) {
                return 1;
            } else if (compareValue == 0) {

                if (sentenceIndex == o.sentenceIndex) {

                    if (index > o.index) {
                        return 1;
                    } else if (index == o.index) {
                        return 0;
                    } else return -1;

                }

                return (sentenceIndex > o.sentenceIndex) ? 1: -1;

            } else return -1;

        }

        @Override
        public String toString() {
            return sentence.substring(0, index) + keyword.toUpperCase() + sentence.substring(index + keyword.length());
        }
    }

    private static Keyword[] mergeSort(Keyword[] arr) {
        if (arr.length <= 1) {
            return arr;
        }

        Keyword[] left = new Keyword[arr.length/2];

        for (int i = 0; i < left.length; i++) {
            left[i] = arr[i];
        }

        Keyword[] right = new Keyword[arr.length - left.length];

        for (int i = left.length; i < arr.length; i++) {
            right[i-left.length] = arr[i];
        }

        left = mergeSort(left);
        right = mergeSort(right);
        return merge(left, right);

    }

    private static Keyword[] merge(Keyword[] left, Keyword[] right) {
        Keyword[] merged = new Keyword[left.length + right.length];

        int leftPointer = 0, rightPointer = 0, mergedPointer = 0;

        while (leftPointer < left.length && rightPointer < right.length) {
            merged[mergedPointer++] = (left[leftPointer].compareTo(right[rightPointer]) < 0) ? left[leftPointer++] : right[rightPointer++];
        }

        while (leftPointer < left.length) {
            merged[mergedPointer++] = left[leftPointer++];
        }

        while(rightPointer < right.length) {
            merged[mergedPointer++] = right[rightPointer++];
        }

        return merged;
    }


    public static void main(String[] args) throws IOException {
        String fileName = args[0];
        Scanner scanner = new Scanner(new File(fileName));

        HashSet<String> ignoreWords = new HashSet<>();
        List<Keyword> keywords = new ArrayList<>();

        boolean ignore = true;
        int index = 0;

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine().trim();

            if (line.equals("...")) {
                ignore = false;
                continue;
            }

            if (line.isEmpty()) {
                continue;
            }

            if (ignore) {
                ignoreWords.add(line.toLowerCase());
            } else {
                String[] words = line.split("\\s+");
                String sentence = line.toLowerCase();
                int totalIndex = 0;
                for (String word : words) {
                    String wordToStore = word.toLowerCase();
                    if (!ignoreWords.contains(wordToStore)) {
                        keywords.add(new Keyword(sentence, wordToStore, totalIndex, index));
                    }
                    totalIndex+=word.length()+1;

                }
                index++;
            }
        }


        Keyword[] keywordsToSort = new Keyword[keywords.size()];
        for (int i = 0; i < keywordsToSort.length; i++) {
            keywordsToSort[i] = keywords.get(i);
        }

        keywordsToSort = mergeSort(keywordsToSort);

        for(Keyword k: keywordsToSort) {
            System.out.println(k);
        }

    }

        
        // TODO: Use the first command line argument (args[0]) as the file to read the input from
        // TODO: Your code goes here
        // TODO: Print the solution to STDOUT
}
