/*
ID: sunnyky1
LANG: JAVA
TASK: numtri

Solution: dp[i][j] = Highest sum from top of triangle to jth number in
row i (both zero-indexed)
dp[0][0] = arr[0][0]
dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + arr[i][j]
arr is stored as a right triangle with legs on the left and bottom

Answer = max(dp[R-1][0...R-1])

Runtime: O(R^2)
 */

import java.util.*;
import java.io.*;

public class numtri {
    int N;
    byte[][] arr;

    numtri() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("numtri.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new byte[N][N];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x <= y; x++) {
                arr[y][x] = Byte.parseByte(st.nextToken());
            }
        }
        fin.close();

        // DP
        int[][] dp = new int[N][N];
        for (int y = 0; y < N; y++) {
            for (int x = 0; x <= y; x++) {
                int a = (inBounds(x-1, y-1)) ? dp[y-1][x-1] : 0;
                int b = (inBounds(x, y-1)) ? dp[y-1][x] : 0;
                dp[y][x] = Math.max(a, b) + arr[y][x];
            }
        }

        int answer = 0;
        for (int x = 0; x < N; x++) answer = Math.max(dp[N-1][x], answer);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("numtri.out")));
        fout.println(answer);
        fout.close();
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x <= y && y >= 0 && y < N;
    }

    public static void main(String[] args) throws IOException {
        new numtri();
    }
}
