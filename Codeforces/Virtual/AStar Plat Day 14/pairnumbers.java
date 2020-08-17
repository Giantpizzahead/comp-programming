/*
Solution: First, prime factorize all the numbers. Then, do binary search on the maximum value of
r-l.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class pairnumbers {
    final int MAX_NUM = 1000001;
    int N, numPrimes = 0;
    boolean[] isPrime;
    int[] arr;
    int[][] primeCount;
    ArrayList<Integer> primes;

    pairnumbers(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        primes = new ArrayList<>(2);
        isPrime = new boolean[1000];
        Arrays.fill(isPrime, true);
        isPrime[0] = false;
        isPrime[1] = false;
        for (int i = 2; i < 1000; i++) {
            if (isPrime[i]) {
                numPrimes++;
                primes.add(i);
                for (int j = i * 2; j < 1000; j += i) isPrime[j] = false;
            }
        }

        System.out.println(Arrays.toString(isPrime));

        primeCount = new int[numPrimes][N];
        for (int i = 0; i < N; i++) {
            int currNum = arr[i];
            for (int j = 0; j < primes.size(); j++) {
                int p = primes.get(j);
                while (currNum != 0 && currNum % p == 0) {
                    currNum /= p;
                    primeCount[j][i]++;
                }
                if (currNum == 0) break;
            }
        }

        ArrayList<Integer> startLocs = new ArrayList<>(2);
        int l = 0, bestRange = 0, minNum = arr[0];
        for (int r = 1; r < N; r++) {
            // Try adding current number
            if (arr[r] % minNum == 0) {
                // Everything will work
            } else if (arr[r] < minNum && minNum % arr[r] == 0) {
                // New minNum!
                minNum = arr[r];
            } else {
                // Current # ruins the window; reset it
                if (r-l > bestRange) {
                    bestRange = r-l;
                    startLocs.clear();
                    startLocs.add(l);
                } else if (r-l == bestRange) {
                    startLocs.add(l);
                }
                l = r;
                minNum = arr[r];
            }

            System.out.println(l + " " + r);
        }

        // Off-by-one
        if (N-1-l > bestRange) {
            bestRange = N-1-l;
            startLocs.clear();
            startLocs.add(l);
        } else if (N-1-l == bestRange) {
            startLocs.add(l);
        }

        out.printf("%d %d\n", startLocs.size(), bestRange);
        for (int i = 0; i < startLocs.size(); i++) {
            if (i != 0) out.print(' ');
            out.print(startLocs.get(i));
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new pairnumbers(in, out);
        in.close();
        out.close();
    }
}
