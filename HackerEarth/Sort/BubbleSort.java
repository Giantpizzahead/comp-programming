package Sort;

import java.io.*;

public class BubbleSort implements Sorter {
    long N = 0, numOperations = 0, numPasses = 0;

    @Override
    public void sort(int[] arr) {
        N = arr.length;
        for (int i = 0; i < arr.length; i++) {
            numOperations++;
            numPasses++;
            if (!bubbleSortPass(arr, i)) break;
        }
    }

    @Override
    public void printInfo(PrintWriter out) {
        out.println("Bubble Sort");
        out.println("bubbleSortPass(): " + numPasses);
        out.println("Worst case operations: " + (N * N / 2));
        out.println("Total operation count: " + numOperations);
    }

    boolean bubbleSortPass(int[] arr, int passNum) {
        numOperations += arr.length - 1;
        boolean changed = false;
        // No need to check the entire array, since some of the end part is already sorted
        for (int i = 1; i < arr.length - passNum; i++) {
            if (arr[i-1] > arr[i]) {
                // Swap the 2 elements
                swap(arr, i-1, i);
                changed = true;
            }
        }
        return changed;
    }

    void swap(int[] arr, int a, int b) {
        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}
