/*
Solution: Binary search on the minimum # of days needed.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class microtransactions {
    final int MAX_TIME = 200001;
    int N, M, sumCopies = 0;
    int[] numCopies;
    ArrayList<Integer>[] offers;

    microtransactions(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        numCopies = new int[N];
        for (int i = 0; i < N; i++) {
            numCopies[i] = Integer.parseInt(st.nextToken());
            sumCopies += numCopies[i];
        }

        offers = new ArrayList[MAX_TIME];
        for (int i = 0; i < MAX_TIME; i++) offers[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken()) - 1;
            offers[a].add(b);
        }

        int low = 1, high = MAX_TIME * 2;
        while (low < high) {
            int mid = (low+high)/2;
            // System.out.println(mid);
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        out.println(low);
    }

    int[] copiesLeft;
    boolean check(int finalDay) {
        int specialsUsed = 0;
        copiesLeft = new int[N];
        for (int i = 0; i < N; i++) copiesLeft[i] = numCopies[i];

        int numBuries = finalDay;
        for (int i = finalDay; i > 0; i--) {
            if (i < MAX_TIME) {
                // Take offers as you can
                for (int offer : offers[i]) {
                    while (copiesLeft[offer] != 0 && numBuries > 0) {
                        numBuries--;
                        copiesLeft[offer]--;
                        specialsUsed++;
                    }
                }
            }
            numBuries = Math.min(numBuries, i-1);
        }

        // System.out.println(Arrays.toString(copiesLeft));
        // Were enough specials used?
        int totalCost = sumCopies * 2 - specialsUsed;
        if (totalCost <= finalDay) return true;
        else return false;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new microtransactions(in, out);
        in.close();
        out.close();
    }
}
