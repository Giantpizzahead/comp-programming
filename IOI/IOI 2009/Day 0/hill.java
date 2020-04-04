/*
Solution: Do a binary-search like procedure on the grid, 'cutting' it in half at each step.
Scan a line through the grid to find the maximum element. Check the other neighbors of that
max element. If either of them is greater, cut the grid in that direction and recurse. Else,
the peak is just that element.

Runtime: O(N) if you draw the shortest line possible (horizontal or vertical)
*/

import java.util.*;
import java.io.*;

public class hill {
    Grader grader;

    Point run(Grader grader) {
        this.grader = grader;
        return solve(0, grader.N - 1, 0, grader.M - 1);
    }

    Point solve(int minX, int maxX, int minY, int maxY) {
        if (maxX - minX < maxY - minY) {
            // Split horizontally
            int splitY = (minY + maxY) / 2;
            int maxLoc = minX, maxAmount = -1;
            for (int x = minX; x <= maxX; x++) {
                int scanRes = scan(x, splitY);
                if (scanRes > maxAmount) {
                    // New highest
                    maxLoc = x;
                    maxAmount = scanRes;
                }
            }
            // Check top and bottom of max amount
            int top = (splitY == minY) ? -1 : scan(maxLoc, splitY - 1);
            int bot = (splitY == maxY) ? -1 : scan(maxLoc, splitY + 1);
            if (top > maxAmount) {
                // Recurse on top
                return solve(minX, maxX, minY, splitY - 1);
            } else if (bot > maxAmount) {
                // Recurse on bottom
                return solve(minX, maxX, splitY + 1, maxY);
            } else {
                // Peak found!
                return new Point(maxLoc + 1, splitY + 1);
            }
        } else {
            // Split vertically
            int splitX = (minX + maxX) / 2;
            int maxLoc = minY, maxAmount = -1;
            for (int y = minY; y <= maxY; y++) {
                int scanRes = scan(splitX, y);
                if (scanRes > maxAmount) {
                    // New highest
                    maxLoc = y;
                    maxAmount = scanRes;
                }
            }
            // Check left and right of max amount
            int left = (splitX == minX) ? -1 : scan(splitX - 1, maxLoc);
            int right = (splitX == maxX) ? -1 : scan(splitX + 1, maxLoc);
            if (left > maxAmount) {
                // Recurse on left
                return solve(minX, splitX - 1, minY, maxY);
            } else if (right > maxAmount) {
                // Recurse on right
                return solve(splitX + 1, maxX, minY, maxY);
            } else {
                // Peak found!
                return new Point(splitX + 1, maxLoc + 1);
            }
        }
    }

    int scan(int x, int y) {
        return grader.scan(x + 1, y + 1);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("hill.in"));
        new Grader(in);
        in.close();
    }

    static class Grader {
        int N, M, numScans = 0;
        int[][] grid;

        Grader(BufferedReader in) throws IOException {
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
            Point p = (new hill()).run(this);
            boolean isPeak = true;
            int pval = grid[p.y - 1][p.x - 1];

            System.out.println("Peak found: " + p + " = " + pval);
            System.out.println("Number scans: " + numScans);

            int left = (p.x == 1) ? -1 : grid[p.y - 1][p.x - 2];
            int right = (p.x == N) ? -1 : grid[p.y - 1][p.x];
            int top = (p.y == 1) ? -1 : grid[p.y - 2][p.x - 1];
            int bot = (p.y == M) ? -1 : grid[p.y][p.x - 1];
            if (pval > left && pval > right && pval > top && pval > bot) {
                System.out.println("Valid peak! :)");
            } else {
                System.out.println("...but it's an invalid peak ;(");
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
