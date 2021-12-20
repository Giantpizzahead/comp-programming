package Sort;

import java.io.*;

public class QuickSort implements Sorter {
    int N, numQuicksort = 0, numPartition = 0, numOperations = 0;

    @Override
    public void sort(int[] arr) {
        N = arr.length;
        quicksort(arr, 0, arr.length - 1);
    }

    @Override
    public void printInfo(PrintWriter out) {
        out.println("Quick Sort");
        out.println("quicksort(): " + numQuicksort);
        out.println("partition(): " + numPartition);
        out.println("Best case operations: " + (int) (N * Math.log(N) / Math.log(2)));
        out.println("Total operation count: " + numOperations);
    }

    // Runs quicksort on the given array from start to end (inclusive on both endpoints).
    private void quicksort(int[] arr, int start, int end) {
        // System.out.println("quicksort() arr = " + Arrays.toString(arr) + ", start = " + start + ", end = " + end);
        numQuicksort++;
        numOperations++;
        if (start >= end) return;

        int partLoc = partition(arr, start, end);
        // Recurse around partition point
        quicksort(arr, start, partLoc - 1);
        quicksort(arr, partLoc + 1, end);
    }

    // Partitions the given array around a randomly chosen pivot point.
    private int partition(int[] arr, int start, int end) {
        // System.out.println("partition() arr = " + Arrays.toString(arr) + ", start = " + start + ", end = " + end);
        numPartition++;
        numOperations += end - start + 1;
        // Choose a random pivot as the 1st array element, and just move it to the start of the array
        int pivLoc = (int) (Math.random() * (end - start + 1));
        swap(arr, start, start + pivLoc);
        int piv = arr[start];
        int first = start + 1;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] < piv) {
                // Goes on the left of pivot
                swap(arr, first++, i);
            } else if (arr[i] == piv && Math.random() < 0.5) {
                // Swap half of the time if values are the same
                // NOTE: This is required to ensure average case N log(N) behavior if the
                // array contains lots of duplicates!
                swap(arr, first++, i);
            }
        }

        // Reposition pivot
        swap(arr, start, first - 1);
        return first - 1;
    }

    private void swap(int[] arr, int i, int j) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
