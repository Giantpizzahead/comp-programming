/*
Solution: At each node, solve the problem separately (if this person is to be included, he/she
also must have even # of child nodes). Do DP on the tree, with the maximum possible efficiency with
even and odd numbers of nodes used for the workgroup.
Runtime: O(N)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class workgroup {
    final long INF = 9987654322345678L;
    int N;
    int[] efficiency;
    long[] bestOdd, bestEven;
    ArrayList<Integer>[] children;

    workgroup(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        efficiency = new int[N];
        children = new ArrayList[N];
        for (int i = 0; i < N; i++) children[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken());
            efficiency[i] = b;
            if (a != -2) children[a].add(i);
        }

        bestOdd = new long[N];
        bestEven = new long[N];
        solve(0);
        // System.out.println(Arrays.toString(bestOdd));
        // System.out.println(Arrays.toString(bestEven));
        out.println(Math.max(bestOdd[0], bestEven[0]));
    }

    void solve(int n) {
        int numChildren = children[n].size();
        if (numChildren == 0) {
            // Base case
            bestEven[n] = 0;
            bestOdd[n] = efficiency[n];
            return;
        }

        long bestOddSum = -INF, bestEvenSum = 0;
        long newOddSum, newEvenSum;
        for (int e : children[n]) {
            solve(e);
            newOddSum = Math.max(bestOddSum + bestEven[e], bestEvenSum + bestOdd[e]);
            newEvenSum = Math.max(bestEvenSum + bestEven[e], bestOddSum + bestOdd[e]);
            bestOddSum = newOddSum;
            bestEvenSum = newEvenSum;
        }

        // Try adding current node
        newOddSum = Math.max(bestEvenSum + efficiency[n], bestOddSum);
        bestOddSum = newOddSum;

        bestOdd[n] = bestOddSum;
        bestEven[n] = bestEvenSum;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new workgroup(in, out);
        in.close();
        out.close();
    }
}
