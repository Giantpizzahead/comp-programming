/*
Solution: Let's solve it the official way. A valley is only non-holey if # outside turns - # inside turns
= 4. So, sort the heights of the cells, and iterate through them in increasing order. At each cell, create
a new valley, and merge (union-find structure) all adjacent valleys. Finally, update the # of outside and
inside turns in the 3x3 box of cells surrounding the current cell (no other cells will be updated). Only
add the # of cells in the valley to the answer if the valley is non-holey after the turn update.

Runtime: O(10^6 [counting sort] + 36 * N^2 [iterate through cells & update turns in 3x3 box])
*/

import java.util.*;
import java.io.*;

public class valleys {
    int N;
    int[][] grid, turnCount;
    Point[] points;
    int[] cx = {0, 1, 0, -1}, cy = {-1, 0, 1, 0}, cx8 = {0, 1, 1, 1, 0, -1, -1, -1}, cy8 = {-1, -1, 0, 1, 1, 1, 0, -1};
    DisjointSet ds;
    final int INF = 987654321;

    valleys() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("valleys.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new int[N][N];
        Point[] sort = new Point[1000001];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < N; x++) {
                grid[y][x] = Integer.parseInt(st.nextToken());
                sort[grid[y][x]] = new Point(x, y, grid[y][x]);
            }
        }
        fin.close();

        points = new Point[N * N];
        for (int i = 0, pi = 0; i < 1000001; i++) {
            if (sort[i] != null) points[pi++] = sort[i];
        }

        long answer = solve();
        PrintWriter fout = new PrintWriter("valleys.out");
        fout.println(answer);
        fout.close();
    }

    long solve() {
        ds = new DisjointSet(N * N);
        turnCount = new int[N][N];
        long answer = 0;

        for (Point p : points) {
            // First, merge this point with its adjacent valleys
            ds.markActive(p.x, p.y);
            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = p.x + cx[i];
                ny = p.y + cy[i];
                if (inBounds(nx, ny) && ds.isActive(nx, ny)) ds.union(p.x, p.y, nx, ny);
            }

            // Now, update the turn count of the neighboring cells
            for (int sx = -1; sx <= 1; sx++) {
                for (int sy = -1; sy <= 1; sy++) {
                    if (inBounds(p.x + sx, p.y + sy) && ds.isActive(p.x + sx, p.y + sy)) updateTurns(p.x + sx, p.y + sy);
                }
            }

            // Finally, add to the answer if allowed
            // System.out.println("Point " + p.x + " " + p.y + " turnSum=" + ds.getTurnSum(p.x, p.y));
            if (ds.getTurnSum(p.x, p.y) == 4) answer += ds.getSetSize(p.x, p.y);
        }

        return answer;
    }

    void updateTurns(int x, int y) {
        int turns = 0;
        // Outside turns
        int n = ds.query(x, y);
        int nx1, ny1, nx2, ny2, nx3, ny3;
        for (int i = 0; i < 8; i += 2) {
            nx1 = x + cx8[i];
            ny1 = y + cy8[i];
            nx2 = x + cx8[(i + 1) % 8];
            ny2 = y + cy8[(i + 1) % 8];
            nx3 = x + cx8[(i + 2) % 8];
            ny3 = y + cy8[(i + 2) % 8];

            // Outside turn
            if ((!inBounds(nx1, ny1) || !ds.isActive(nx1, ny1)) && (!inBounds(nx3, ny3) || !ds.isActive(nx3, ny3))) turns++;
            // Inside turn
            if (inBounds(nx1, ny1) && ds.isActive(nx1, ny1) && inBounds(nx3, ny3) && ds.isActive(nx3, ny3) &&
               (!inBounds(nx2, ny2) || !ds.isActive(nx2, ny2))) turns--;
        }

        // Update turn count of target valleys
        int turnChange = turns - turnCount[y][x];
        turnCount[y][x] = turns;
        ds.updateTurnSum(n, turnChange);
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    int hashCoords(int x, int y) {
        return x * N + y;
    }

    public static void main(String[] args) throws IOException {
        new valleys();
    }

    class DisjointSet {
        int size;
        int[] vals, turnSum;
        boolean[] active;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
            turnSum = new int[size];
            active = new boolean[size];
        }

        int union(int x1, int y1, int x2, int y2) {
            int a = hashCoords(x1, y1);
            int b = hashCoords(x2, y2);
            if (!active[a] || !active[b]) return a;

            a = query(a);
            b = query(b);
            if (a == b) return a;

            // Merge into the set with more elements
            if (vals[a] < vals[b]) {
                // Merge into set a
                vals[a] += vals[b];
                turnSum[a] += turnSum[b];
                vals[b] = a;
                return a;
            } else {
                // Merge into set b
                vals[b] += vals[a];
                turnSum[b] += turnSum[a];
                vals[a] = b;
                return b;
            }
        }

        int query(int x, int y) {
            return query(hashCoords(x, y));
        }

        int query(int n) {
            if (!active[n]) return -1;
            if (vals[n] < 0) return n;
            else {
                vals[n] = query(vals[n]);  // Backpropagation
                return vals[n];
            }
        }

        int getSetSize(int x, int y) {
            return -vals[query(x, y)];
        }

        int getTurnSum(int x, int y) {
            return turnSum[query(x, y)];
        }

        void updateTurnSum(int n, int v) {
            turnSum[n] += v;
        }

        boolean isActive(int x, int y) {
            return active[hashCoords(x, y)];
        }

        void markActive(int x, int y) {
            active[hashCoords(x, y)] = true;
        }
    }

    class Point {
        int x, y, v;
        Point(int x, int y, int v) {
            this.x = x;
            this.y = y;
            this.v = v;
        }
    }
}
