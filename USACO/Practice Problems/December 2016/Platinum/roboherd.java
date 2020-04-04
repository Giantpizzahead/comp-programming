/*
USACO 2016 December Contest (Platinum)
Problem 3. Robotic Cow Herd
By Giantpizzahead

Solution: Binary search for the minimum cost such that there are less than K cows with a cost
less than that minimum cost. Answer would be the sum of all those less than K cows + the found cost
times the # of cows not accounted for.
Do this by first sorting each individual controller in increasing order, and changing the cost of the
1st controller in each group to 0 (to make code easier to implement).
Binary search on the cost. Lower is 0, upper is the sum of the most expensive controller in each group.
This alone would be an O(N^2 * log(P)) algorithm (N^2 to evaluate given cost, log(P) for binary search),
but it can be optimized more.

Sort all the controllers in order of increasing differences (A controller group with 3 4 would be before
4 6, which is before 9 12, so on). This ensures that if there is no split in the DFS at one stage, there
won't be any more splits later on, allowing you to safely say that there is only one cow in that branch
without having to go down the whole thing. This gives an O(N * log(N) + N * log(P)) algorithm (N * log(N)
for sorting, N to evaluate given cost, log(P) for binary search), which runs in time!
*/

import java.util.*;
import java.io.*;

public class roboherd {
    int N, K;
    int[][] controllers;
    long baseCost, low, high;

    roboherd() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("roboherd.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        controllers = new int[N][];
        baseCost = 0;
        low = 0;
        high = 0;
        int numConts;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            numConts = Integer.parseInt(st.nextToken());
            controllers[i] = new int[numConts];
            for (int j = 0; j < numConts; j++) {
                controllers[i][j] = Integer.parseInt(st.nextToken());
            }
            // Sort controllers in increasing order
            Arrays.sort(controllers[i]);
            // Set first controller cost to 0, and adjust other controllers
            baseCost += controllers[i][0];
            for (int j = numConts - 1; j >= 0; j--) {
                controllers[i][j] -= controllers[i][0];
            }
            high += controllers[i][numConts-1];
        }
        fin.close();

        // Sort controller groups in order of increasing differences
        /*
        Arrays.sort(controllers, (a, b) -> {
            if (a.length > 1 && b.length > 1) return a[1] - b[1];
            else return 0;
        });
         */

        Arrays.sort(controllers, (a, b) -> {
            if (a.length == 1 && b.length == 1) return 0;
            else if (a.length == 1) return 1;
            else if (b.length == 1) return -1;
            int c = Math.min(a.length, b.length);
            for (int i = 1; i < c; i++) {
                if (a[i] != b[i]) return a[i] - b[i];
            }
            return a.length - b.length;
        });

        // Binary search for the minimum cost
        while (low < high) {
            long mid = (low + high + 1) / 2;
            numCows = 0;
            if (check(0, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        // Find the minimum total cost
        // System.out.println(low);
        numCows = 0;
        savings = 0;
        findSavings(0, low);
        // System.out.println(numCows);
        long answer = low * K - savings;
        answer += K * baseCost;
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("roboherd.out")));
        fout.println(answer);
        fout.close();
    }

    long savings;
    void findSavings(int i, long costLeft) {
        if (i == N) {
            // Reached end; add to final answer
            numCows++;
            savings += costLeft;
            // System.out.println("Savings now " + savings);
            return;
        }

        // Optimization: If next part is higher price than possible, the only way to get
        // everything is to take all the 0s, so just add those savings and return
        if (controllers[i].length == 1 || costLeft - controllers[i][1] <= 0) {
            numCows++;
            savings += costLeft;
            return;
        }

        for (int next : controllers[i]) {
            if (costLeft - next > 0) {
                findSavings(i + 1, costLeft - next);
            }
        }
    }

    int numCows;
    boolean check(int i, long costLeft) {
        // Only check if needed
        if (numCows >= K) return false;

        if (i == N) {
            // Reached end of cows
            numCows++;
            return numCows < K;
        }

        // Optimization: If next part is higher price than possible, the only way to get
        // everything is to take all the 0s, so just add 1 and return
        if (controllers[i].length == 1 || costLeft - controllers[i][1] <= 0) {
            numCows++;
            return numCows < K;
        }

        for (int next : controllers[i]) {
            if (costLeft - next > 0) {
                check(i + 1, costLeft - next);
                if (numCows >= K) return false;
            } else break;
        }

        return true;
    }

    public static void main(String[] args) throws IOException {
        new roboherd();
    }
}
