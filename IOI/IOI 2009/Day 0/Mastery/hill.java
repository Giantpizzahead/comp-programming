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
        return findPoint(0, N-1, 0, M-1);
    }

    Point findPoint(int x1, int x2, int y1, int y2) {
        if (x2 - x1 < y2 - y1) {
            // Cut horizontally
            int ymid = (y1 + y2) / 2;
            int maxLoc = -1, maxHeight = -1;
            for (int i = x1; i <= x2; i++) {
                int result = scan(i, ymid);
                if (result > maxHeight) {
                    maxHeight = result;
                    maxLoc = i;
                }
            }
            // Recurse on top or bottom?
            if (ymid != y1 && scan(maxLoc, ymid-1) > maxHeight) {
                // Recurse on top
                return findPoint(x1, x2, y1, ymid-1);
            } else if (ymid != y2 && scan(maxLoc, ymid+1) > maxHeight) {
                // Recurse on bottom
                return findPoint(x1, x2, ymid+1, y2);
            } else {
                // Top and bottom are both smaller; this is a hill
                return new Point(maxLoc+1, ymid+1);
            }
        } else {
            // Cut vertically
            int xmid = (x1 + x2) / 2;
            int maxLoc = -1, maxHeight = -1;
            for (int i = y1; i <= y2; i++) {
                int result = scan(xmid, i);
                if (result > maxHeight) {
                    maxHeight = result;
                    maxLoc = i;
                }
            }
            // Recurse on left or right?
            if (xmid != x1 && scan(xmid-1, maxLoc) > maxHeight) {
                // Recurse on left
                return findPoint(x1, xmid-1, y1, y2);
            } else if (xmid != x2 && scan(xmid+1, maxLoc) > maxHeight) {
                // Recurse on right
                return findPoint(xmid+1, x2, y1, y2);
            } else {
                // Left and right are both smaller; this is a hill
                return new Point(xmid+1, maxLoc+1);
            }
        }
    }

    int scan(int x, int y) {
        return grader.scan(x+1, y+1);
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
