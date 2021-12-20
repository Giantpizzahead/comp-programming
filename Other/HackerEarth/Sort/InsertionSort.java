package Sort;

import java.io.PrintWriter;

public class InsertionSort implements Sorter {
    int N;
    long numOperations;

    @Override
    public void sort(int[] arr) {
        N = arr.length;
        for (int i = 0; i < arr.length; i++) {
            numOperations++;
            // Sort the current element by effectively moving it as far left as needed
            int currElement = arr[i];
            int j = i;
            while (j > 0 && currElement < arr[j-1]) {
                numOperations++;
                arr[j] = arr[j-1];
                j--;
            }
            // Move curr element to correct position
            arr[j] = currElement;
        }
    }

    @Override
    public void printInfo(PrintWriter out) {
        out.println("Insertion Sort");
        out.println("Worst case operations: " + (long) N * N);
        out.println("Num operations: " + numOperations);
    }
}
