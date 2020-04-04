/*
Solution: If a # ever appears in another number's rectangle, the 1st # can't be painted first. Otherwise, everything is
ok. To track when this happens, make a prefix sum of # rects active (generated from min/max x and y for each rectangle).
Then, iterate through this prefix sum array, generating the actual array as you go. If # rects > 1, then the color at
the current cell covers the other rectangle(s) / cannot be first drawn.

Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class art {
    int N;
    int[][] grid, prefix;
    int[] minX, maxX, minY, maxY;
    final int INF = 987654321;

    art() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("art.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        minX = new int[N*N];
        Arrays.fill(minX, INF);
        maxX = new int[N*N];
        Arrays.fill(maxX, -INF);
        minY = new int[N*N];
        Arrays.fill(minY, INF);
        maxY = new int[N*N];
        Arrays.fill(maxY, -INF);
        grid = new int[N][N];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < N; x++) {
                int c = Integer.parseInt(st.nextToken()) - 1;
                if (c != -1) {
                    minX[c] = Math.min(x, minX[c]);
                    maxX[c] = Math.max(x, maxX[c]);
                    minY[c] = Math.min(y, minY[c]);
                    maxY[c] = Math.max(y, maxY[c]);
                }
                grid[y][x] = c;
            }
        }
        fin.close();

        // Prefix sum array
        prefix = new int[N+1][N+1];
        for (int i = 0; i < N*N; i++) {
            if (minY[i] != INF) {
                prefix[minY[i]][minX[i]]++;
                prefix[maxY[i]+1][minX[i]]--;
                prefix[minY[i]][maxX[i]+1]--;
                prefix[maxY[i]+1][maxX[i]+1]++;
            }
        }

        // for (int i = 0; i < N + 1; i++) System.out.println(Arrays.toString(prefix[i]));

        boolean[] cannotBeFirst = new boolean[N*N];
        for (int y = 0; y < N + 1; y++) {
            for (int x = 0; x < N + 1; x++) {
                // Generate correct prefix sum value
                prefix[y][x] += (y == 0) ? 0 : prefix[y-1][x];
                prefix[y][x] += (x == 0) ? 0 : prefix[y][x-1];
                prefix[y][x] -= (x == 0 || y == 0) ? 0 : prefix[y-1][x-1];
                if (y == N || x == N) continue;
                if (prefix[y][x] > 1 && grid[y][x] != -1) {
                    // This rectangle cannot be painted first
                    cannotBeFirst[grid[y][x]] = true;
                }
            }
        }

        int answer = 0;
        for (boolean b : cannotBeFirst) answer += b ? 0 : 1;

        // Special case; if only 1 rectangle, that color cannot be painted first
        int numRects = 0;
        for (int i = 0; i < N * N; i++) if (minX[i] != INF) numRects++;

        PrintWriter fout = new PrintWriter("art.out");
        fout.println((numRects == 1) ? answer - 1 : answer);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new art();
    }
}
