/*
Solution: Harvest the segment with the smallest remainder when moduloed by d.

Runtime: O(RC)
*/

import java.util.*;
import java.io.*;

public class potatoes {
    int T, R, C, D, passID;
    int[][] grid;
    PrintWriter fout;

    potatoes() throws IOException {
        Scanner fin = new Scanner(new FileReader("ipsc2012/h1.in"));
        fout = new PrintWriter("h.out");
        T = fin.nextInt();
        for (int i = 0; i < T; i++) {
            R = fin.nextInt();
            C = fin.nextInt();
            D = fin.nextInt();
            grid = new int[R][C];
            passID = 1;
            solve(0, 0, D);
            // Print grid
            for (int y = 0; y < R; y++) {
                for (int x = 0; x < C; x++) {
                    if (x != 0) fout.print(' ');
                    fout.print(grid[y][x]);
                }
                fout.println();
            }
            fout.println();
            fout.flush();
        }
        fin.close();
        fout.close();
    }

    void solve(int minX, int minY, int newD) {
        System.out.println("minX = " + minX + ", minY = " + minY + ", newD = " + newD);
        if (minX == C || minY == R) return;

        // Make as many horizontal segments as possible first
        int maxFilledX = minX - 1;
        if (C - minX >= R - minY) {
            for (int y = minY; y < R; y++) {
                for (int x = minX; x <= C - newD; x += newD) {
                    // Label all horizontal cells
                    for (int i = x; i < Math.min(C, x + newD); i++) grid[y][i] = passID;
                    passID++;
                    maxFilledX = Math.min(C, x + newD) - 1;
                }
            }
        }

        int newHorizontalD = (C - maxFilledX + 1) % newD;

        // Make as many vertical segments as possible
        int maxFilledY = minY - 1;
        if (R - minY > C - minX) {
            for (int x = maxFilledX + 1; x < C; x++) {
                for (int y = minY; y <= R - newD; y += newD) {
                    // Label all vertical cells
                    for (int i = y; i < Math.min(R, y + newD); i++) grid[i][x] = passID;
                    passID++;
                    maxFilledY = Math.min(R, y + newD) - 1;
                }
            }
        }

        int newVertD = (R - maxFilledY + 1) % newD;

        // Recurse
        solve(maxFilledX + 1, maxFilledY + 1, Math.max(newHorizontalD, newVertD));
    }

    public static void main(String[] args) throws IOException {
        new potatoes();
    }
}
