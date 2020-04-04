/*
Solution: For now, just simulate it.
Runtime: O(N^2)
 */

import java.util.*;
import java.io.*;

public class sort {
    int N;
    int[] arr;

    sort() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        N = Integer.parseInt(fin.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(fin.readLine());
        }
        fin.close();

        arr = new int[] {2, 3, 6, 5, 4, 1, 8, 7};
        N = arr.length;

        // Simulate Bessie's method
        int answer = 0;
        boolean sorted = false;
        int temp;
        System.out.println("Starting:");
        System.out.println(Arrays.toString(arr));
        while (!sorted) {
            System.out.println("Iteration " + answer);
            sorted = true;
            answer++;
            for (int i = 0; i < N-1; i++) {
                if (arr[i+1] < arr[i]) {
                    temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
            }
            System.out.println(Arrays.toString(arr));
            for (int i = N-2; i >= 0; i--) {
                if (arr[i+1] < arr[i]) {
                    temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
            }
            System.out.println(Arrays.toString(arr));
            for (int i = 0; i < N-1; i++) {
                if (arr[i+1] < arr[i]) {
                    sorted = false;
                }
            }
        }

        System.out.println("Answer: " + answer);
        System.out.println(Arrays.toString(arr));

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        fout.println(answer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new sort();
    }

    static class Point {
        int a, b;
        Point(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}
