/*
ID: sunnyky1
LANG: JAVA
TASK: sprime

Solution: Build the superprime from the bottom up, only checking additions to existing
superprimes to minimize redundancy.
*/

import java.util.*;
import java.io.*;
import java.util.stream.IntStream;

public class sprime {
    int N;
    ArrayList<Integer> superprimes;

    sprime() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        fin.close();

        // Hardcode superprimes for N=1 to get rid of edge '2' case
        superprimes = new ArrayList<Integer>();
        Collections.addAll(superprimes, 2, 3, 5, 7);

        // Generate 1 length longer superprimes from existing ones
        for (int i = 2; i <= N; i++) {
            ArrayList<Integer> newSuperprimes = new ArrayList<>();
            // Only test odd numbers
            for (int oldSuperprime : superprimes) {
                for (int toTest = 1; toTest < 10; toTest += 2) {
                    int newSuperprime = oldSuperprime * 10 + toTest;
                    if (test(newSuperprime)) {
                        newSuperprimes.add(newSuperprime);
                    }
                }
            }
            superprimes = newSuperprimes;
        }

        // Superprimes are already sorted
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sprime.out")));
        for (int sp : superprimes) fout.println(sp);
        fout.close();
    }

    boolean test(int n) {
        for (int d = 2; d <= Math.sqrt(n); d++) {
            if (n % d == 0) return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        new sprime();
    }
}