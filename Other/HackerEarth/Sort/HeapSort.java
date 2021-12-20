package Sort;

import java.io.PrintWriter;
import java.util.*;

public class HeapSort implements Sorter {
    long N;
    double numOperations;

    @Override
    public void sort(int[] arr) {
        N = arr.length;
        PriorityQueue<Integer> pq = new PriorityQueue<>(arr.length);
        for (int i = 0; i < arr.length; i++) {
            numOperations += Math.log(i + 1) / Math.log(2);
            pq.add(arr[i]);
        }
        numOperations += arr.length;
        for (int i = 0; i < arr.length; i++) arr[i] = pq.poll();
    }

    @Override
    public void printInfo(PrintWriter out) {
        out.println("Heap Sort");
        out.println("Extra bytes taken: " + (N * Integer.BYTES));
        out.println("Approximate operation count: " + (long) numOperations);
    }
}
