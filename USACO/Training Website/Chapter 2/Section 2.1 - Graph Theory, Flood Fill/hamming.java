/*
ID: sunnyky1
LANG: JAVA
TASK: hamming

Solution: Do a DFS on all possible sets of Hamming codes. This should
run in time, since the hamming distance makes lots of combinations
invalid; I don't know how to analyze the complexity of this though.

Runtime: O(no clue but hopefully fast enough...???)
*/

import java.util.*;
import java.io.*;

public class hamming {
    int N, B, D;
    ArrayList<Integer> nums;

    hamming() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("hamming.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        fin.close();

        // Try all possible hamming code sets
        nums = new ArrayList<>();
        if (!dfs(0)) System.out.println("Impossible!");;

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("hamming.out")));
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < N; i++) {
            sb.append(nums.get(i)).append(' ');
            if (i % 10 == 9) {
                // Split line
                fout.println(sb.substring(0, sb.length() - 1));
                sb = new StringBuilder();
            }
        }
        if (sb.length() != 0) fout.println(sb.substring(0, sb.length() - 1));
        fout.close();
    }

    boolean dfs(int curr) {
        if (nums.size() == N) return true;
        else if (curr > (1 << B)) return false;
        // Try adding current number to nums
        if (valid(curr)) {
            nums.add(curr);
            if (dfs(curr + 1)) return true;
            else nums.remove(nums.size() - 1);
        }
        // Try not adding current number
        return dfs(curr + 1);
    }

    boolean valid(int n) {
        for (int o : nums) {
            if (hammingDistance(n, o) < D) return false;
        }
        // System.out.println(n + " valid");
        return true;
    }

    int hammingDistance(int a, int b) {
        return Integer.bitCount(a ^ b);
    }

    public static void main(String[] args) throws IOException {
        new hamming();
    }
}