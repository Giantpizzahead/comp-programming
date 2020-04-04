/*
If N = 5, one 4 is an issue, two 3s is also an issue, three 2s, etc...
3 2 0 X X
one 3, one 2 is not an issue
3 2 3 2 0 -> 3 2 3 is an issue
3 2 2 1 1 -> two 2s and one 3 is an issue
3 2 1 0 0 -> No issues no matter what order
Issue if # of numbers >= x is at least N - x
As soon as issue occurs, stop, and output answer

Say you're binary searching
Add all #s into structure, check if issue or not
Add #s into treeset, then iterate through, counting # of nums seen
so far & min # also
Runtime: O(N * log(N)^2)
 */

import java.util.*;
import java.io.*;

public class greedy {
    int N;
    int[] cows;
    TreeMap<Integer, Integer> nums = new TreeMap<>();

    greedy() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("greedy.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        cows = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) cows[i] = Integer.parseInt(st.nextToken());
        fin.close();

        // Binary search
        int low = 0, high = N;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        // System.out.println(low);

        PrintWriter fout = new PrintWriter("greedy.out");
        fout.println(N - low);
        fout.close();
    }

    // Check if the first numCows cows causes any issues.
    boolean check(int numCows) {
        nums.clear();
        for (int i = 0; i < numCows; i++) {
            update(nums, cows[i]);
        }

        // Iterate through to see if any issues arise
        int numSoFar = 0;
        for (Map.Entry<Integer, Integer> entry : nums.descendingMap().entrySet()) {
            numSoFar += entry.getValue();
            if (numSoFar >= N - entry.getKey()) return true;
        }

        // Got to the end; no issues
        return false;
    }

    void update(TreeMap<Integer, Integer> map, int n) {
        map.put(n, map.getOrDefault(n, 0) + 1);
    }

    public static void main(String[] args) throws IOException {
        new greedy();
    }
}