/*
Solution: 
*/

import java.util.*;
import java.io.*;

public class balanceTest {
    int start = 27, middle = 78, max = 143;
    double[] arr;

    balanceTest() throws IOException {
        arr = new double[max + 1];
        arr[middle] = 1;
        for (int i = 0; i < 100000; i++) {
            double nextToAdd = 0;
            for (int j = start + 1; j < max; j++) {
                arr[j-1] += arr[j] / 2;
                double temp = arr[j] / 2;
                arr[j] = nextToAdd;
                nextToAdd = temp;
            }
            arr[max] += nextToAdd;
        }
        System.out.println(Arrays.toString(arr));
    }

    public static void main(String[] args) throws IOException {
        new balanceTest();
    }
}
