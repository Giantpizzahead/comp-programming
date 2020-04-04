/*
Solution: To understand the sort, implement it first.
*/

import java.util.*;
import java.io.*;

public class sortSimulation {
    int N;
    long workCounter;
    int[] arr;

    sortSimulation() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        N = Integer.parseInt(fin.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(fin.readLine());
        fin.close();
        workCounter = 0;
        quickishSort(0, N);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        fout.println(workCounter);
        fout.close();
    }

    void quickishSort(int s, int e) {
        System.out.println("quickishSort(" + Arrays.toString(Arrays.copyOfRange(arr, s, e)) + ")");
        if (e - s == 1) return;  // Length 1 array
        ArrayList<Integer> partitionPoints;
        do {
            workCounter += e - s;
            bubbleSortPass(s, e);
            partitionPoints = findPartitionPoints(s, e);
        } while (partitionPoints.size() == 0);
        // Recurse on each piece
        int lastI = s;
        for (int point : partitionPoints) {
            quickishSort(lastI, point);
            lastI = point;
        }
    }

    void bubbleSortPass(int s, int e) {
        for (int i = s; i < e - 1; i++) {
            if (arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
    }

    ArrayList<Integer> findPartitionPoints(int s, int e) {
        int[] greatestLeft = new int[e-s];
        int track = arr[0];
        for (int i = s; i < e; i++) {
            track = Math.max(arr[i], track);
            greatestLeft[i-s] = track;
        }
        int[] leastRight = new int[e-s];
        track = arr[e-1];
        for (int i = e-1; i >= s; i--) {
            track = Math.min(arr[i], track);
            leastRight[i-s] = track;
        }

        ArrayList<Integer> partitionPoints = new ArrayList<>();
        for (int i = s + 1; i < e; i++) {
            if (greatestLeft[i-s-1] <= leastRight[i-s]) partitionPoints.add(i);
        }

        return partitionPoints;
    }

    public static void main(String[] args) throws IOException {
        new sortSimulation();
    }
}
