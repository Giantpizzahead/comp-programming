/*
ID: sunnyky1
LANG: JAVA
TASK: inflate

Solution: Standard multiple Knapsack.
Runtime: O(MN)
*/

import java.util.*;
import java.io.*;

public class inflate {
    int M, N;
    int[] points, minutes;

    inflate() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("inflate.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        M = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        points = new int[N];
        minutes = new int[N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            points[i] = Integer.parseInt(st.nextToken());
            minutes[i] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        int[] dp = new int[M + 1];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= M; j++) {
                if (j - minutes[i] >= 0) dp[j] = Math.max(dp[j - minutes[i]] + points[i], dp[j]);
            }
        }

        PrintWriter fout = new PrintWriter("inflate.out");
        fout.println(dp[M]);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new inflate();
    }
}