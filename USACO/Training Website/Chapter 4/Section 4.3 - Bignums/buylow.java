/*
ID: sunnyky1
LANG: JAVA
TASK: buylow

Solution:
lds[i] = Length of longest decreasing sequence using elements [0, i]
ldsWays[i] = # of distinct LDSs using elements [0, i]

lds[i] = max from k -> 0...i-1: (lds[k] if arr[k] > arr[i]) + 1
ldsWays[i] = sum from k -> 0...i-1: (ldsWays[k] if arr[k] > arr[i] && lds[k]
+ 1 == lds[i] && first time seeing arr[k])

Runtime: O(N^2)
*/

import java.util.*;
import java.math.BigInteger;
import java.io.*;

public class buylow {
    int N;
    int[] arr;

    buylow(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            if (!st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
            arr[i] = Integer.parseInt(st.nextToken());
        }

        int[] lds = new int[N];
        BigInteger[] ldsWays = new BigInteger[N];
        HashSet<Integer> used = new HashSet<>();
        for (int i = 0; i < N; i++) {
            BigInteger ldsWaySum = BigInteger.ONE;
            used.clear();
            lds[i] = 1;
            for (int j = i - 1; j >= 0; j--) {
                if (arr[j] > arr[i]) {
                    if (lds[j] + 1 > lds[i]) {
                        lds[i] = lds[j] + 1;
                        // Reset count
                        ldsWaySum = ldsWays[j];
                    } else if (lds[j] + 1 == lds[i]) {
                        // Add to # ways if not seen before
                        if (!used.contains(arr[j])) {
                            ldsWaySum = ldsWaySum.add(ldsWays[j]);
                        }
                    }
                    used.add(arr[j]);
                }
            }
            ldsWays[i] = ldsWaySum;
        }

        // System.out.println(Arrays.toString(lds));
        // System.out.println(Arrays.toString(ldsWays));

        // Generate final result
        int longestLDS = 0;
        BigInteger totalWays = BigInteger.ZERO;
        used.clear();
        for (int i = N-1; i >= 0; i--) {
            if (lds[i] > longestLDS) {
                longestLDS = lds[i];
                totalWays = ldsWays[i];
            } else if (lds[i] == longestLDS && !used.contains(arr[i])) {
                totalWays = totalWays.add(ldsWays[i]);
            }
            used.add(arr[i]);
        }
        out.printf("%d %s\n", longestLDS, totalWays.toString());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("buylow.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("buylow.out")));
        new buylow(in, out);
        in.close();
        out.close();
    }
}