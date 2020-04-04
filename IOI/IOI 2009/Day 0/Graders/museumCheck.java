/*
Checks all 5 answers for museum.
*/

import java.util.*;
import java.io.*;

public class museumCheck {
    int N;
    int[] arr, numToLoc;

    museumCheck(BufferedReader in, int testNum) throws IOException {
        ArrayList<Integer> listArr = new ArrayList<>(2);
        while (in.ready()) {
            listArr.add(Integer.parseInt(in.readLine()));
        }
        N = listArr.size();
        arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = listArr.get(i);
        numToLoc = new int[N + 1];
        for (int i = 0; i < N; i++) numToLoc[arr[i]] = i;
        // Check every pair for correctness
        for (int a = 1; a <= N; a++) {
            for (int b = a + 2; b <= N; b += 2) {
                int t = (a + b) / 2;
                if ((numToLoc[t] > numToLoc[a]) != (numToLoc[t] > numToLoc[b])) {
                    // Target within a to b, so this is invalid
                    System.out.println("Test " + testNum + ": WA ;(");
                    return;
                }
            }
        }

        System.out.println("Test " + testNum + ": AC!");
    }

    public static void main(String[] args) throws IOException {
        for (int i = 1; i <= 5; i++) {
            BufferedReader in = new BufferedReader(new FileReader("museum." + i + ".out"));
            new museumCheck(in, i);
            in.close();
        }
    }
}
