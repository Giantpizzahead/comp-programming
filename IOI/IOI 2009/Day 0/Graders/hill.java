/*
grader.scan(x, y) - Returns value at (x, y), one-indexed.
Return a Point with the location of a peak.
Fill in the run() function.
 */

import java.util.*;
import java.io.*;

public class hill {
    int N, M;
    Grader grader;

    hill(Grader grader) {
        this.grader = grader;
        this.N = grader.N;
        this.M = grader.M;
    }

    Point run() {
        // Your code goes here
        return new Point(1, 1);
    }

    // --- Grader code ---

    public static void main(String[] args) throws IOException {
        for (int i = 1; i <= 4; i++) {
            BufferedReader in = new BufferedReader(new FileReader("hill" + i + ".in"));
            new Grader(in, i);
            in.close();
        }
    }

    static class Grader {
        int N, M, numScans = 0;
        int[][] grid;

        Grader(BufferedReader in, int testNum) throws IOException {
            StringTokenizer st = new StringTokenizer(in.readLine());
            N = Integer.parseInt(st.nextToken());
            M = Integer.parseInt(st.nextToken());
            grid = new int[M][N];
            for (int y = 0; y < M; y++) {
                st = new StringTokenizer(in.readLine());
                for (int x = 0; x < N; x++) {
                    grid[y][x] = Integer.parseInt(st.nextToken());
                }
            }

            // Test program
            Point p = (new hill(this)).run();
            boolean isPeak = true;
            int pval = grid[p.y - 1][p.x - 1];

            // System.out.println("Peak found: " + p + " = " + pval);
            // System.out.println("Number scans: " + numScans);

            int left = (p.x == 1) ? -1 : grid[p.y - 1][p.x - 2];
            int right = (p.x == N) ? -1 : grid[p.y - 1][p.x];
            int top = (p.y == 1) ? -1 : grid[p.y - 2][p.x - 1];
            int bot = (p.y == M) ? -1 : grid[p.y][p.x - 1];
            if (pval > left && pval > right && pval > top && pval > bot && numScans <= 3050) {
                System.out.println("Test " + testNum + ": AC!");
            } else {
                System.out.println("Test " + testNum + ": WA ;(");
            }
        }

        int scan(int x, int y) {
            numScans++;
            return grid[y-1][x-1];
        }
    }

    static class Point {
        int x, y;
        Point(int xx, int yy) {
            x = xx;
            y = yy;
        }
        public String toString() {
            return String.format("(%d, %d)", x, y);
        }
    }
}
