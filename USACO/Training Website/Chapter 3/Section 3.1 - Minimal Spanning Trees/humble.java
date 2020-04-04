/*
ID: sunnyky1
LANG: JAVA
TASK: humble

Solution: Put the currently found humble numbers into a TreeSet. At each
humble number, generate new humble numbers from the factors in the set S.
Put these into the TreeSet, removing #s from the TreeSet when there are
more numbers than needed.

Runtime: O(NK * log(N)) - Might be a bit too slow... let's see.
*/

import java.util.*;
import java.io.*;

public class humble {
    int K, N;
    int[] factors;
    TreeSet<Integer> humbleNums;

    humble() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("humble.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        K = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        factors = new int[K];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < K; i++) factors[i] = Integer.parseInt(st.nextToken());
        fin.close();

        humbleNums = new TreeSet<>();
        for (int factor : factors) humbleNums.add(factor);
        int answer = 0;
        long maxNumToAdd = (long) Integer.MAX_VALUE + 1;
        for (int i = 0; i < N; i++) {
            int currNum = humbleNums.pollFirst();
            if (i == N - 1) {
                answer = currNum;
                break;
            }
            // Generate new humble numbers
            for (int j = 0; j < K; j++) {
                long newNum = (long) currNum * factors[j];
                if (newNum < maxNumToAdd) {
                    humbleNums.add((int) newNum);
                    // If more #s then needed, remove largest one
                    if (humbleNums.size() >= N - i) humbleNums.pollLast();
                }
            }

            // To save runtime, find max # that needs to be added
            if (humbleNums.size() == N - i - 1) maxNumToAdd = humbleNums.last();
        }

        PrintWriter fout = new PrintWriter("humble.out");
        fout.println(answer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new humble();
    }
}