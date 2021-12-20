package Sort;

import java.io.PrintWriter;

public class SelectionSort implements Sorter {
    int N;
    long numOperations;

    @Override
    public void sort(int[] arr) {
        N = arr.length;
        for (int i = 0; i < arr.length; i++) {
            // Find minimum in arr[i...N]
            int minimum = i;
            for (int j = i + 1; j < arr.length; j++) {
                numOperations++;
                if (arr[j] < arr[minimum]) minimum = j;
            }
            // Swap minimum element
            numOperations++;
            int temp = arr[i];
            arr[i] = arr[minimum];
            arr[minimum] = temp;
        }
    }

    @Override
    public void printInfo(PrintWriter out) {
        out.println("Selection Sort");
        out.println("Num operations: " + numOperations);
    }
}
