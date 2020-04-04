/*
Solution: First, BFS from the hives to figure out the latest time-step at which Mecho can
go to each grass cell. Then, binary search on the time that Mecho leaves the honeypot.
Runtime: O(N^2 * log(N^2))
*/

import java.util.*;
import java.io.*;

public class mecho {
    final int[] cx = {1, 0, -1, 0}, cy = {0, -1, 0, 1};
    int N, S;
    Point start, home;
    Queue<Point> q;
    boolean[][] grid, visited;
    int[][] blockTime;

    mecho(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        S = Integer.parseInt(st.nextToken());
        // Easier implementation - Make the whole border trees
        N += 2;
        grid = new boolean[N][N];
        visited = new boolean[N][N];
        q = new LinkedList<>();
        for (int y = 1; y < N - 1; y++) {
            char[] line = in.readLine().toCharArray();
            for (int x = 1; x < N - 1; x++) {
                char c = line[x-1];
                if (c == 'M') {
                    start = new Point(x, y);
                    grid[y][x] = true;
                } else if (c == 'D') {
                    home = new Point(x, y);
                    grid[y][x] = false;
                } else if (c == 'H') {
                    q.add(new Point(x, y));
                    visited[y][x] = true;
                    grid[y][x] = true;
                } else {
                    grid[y][x] = (c == 'G');
                }
            }
        }

        // Do initial BFS from hives
        findBlockTimes();
        // for (int y = 0; y < N; y++) System.out.println(Arrays.toString(blockTime[y]));

        // Binary search on Mecho's leaving time
        int low = 0, high = N * N;
        boolean worked = false;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            if (check(mid)) {
                low = mid;
                worked = true;
            } else {
                high = mid - 1;
            }
        }

        if (worked || check(low)) out.println(low);
        else out.println(-1);
    }

    boolean check(int leaveTime) {
        // System.out.println("leaveTime = " + leaveTime);
        int startingCost = leaveTime * S;
        if (startingCost >= blockTime[start.y][start.x]) return false; // Gets caught before leaving

        for (int y = 0; y < N; y++) Arrays.fill(visited[y], false);
        int currLeft = 1, nextLeft = 0, currCost = startingCost;
        q.clear();
        q.add(start);
        visited[start.y][start.x] = true;
        Point c;
        while (!q.isEmpty()) {
            c = q.poll();
            // System.out.println(c);
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (nx == home.x && ny == home.y) return true;
                if (blockTime[ny][nx] > currCost + 1 && !visited[ny][nx]) {
                    // This cell won't be blocked
                    visited[ny][nx] = true;
                    nextLeft++;
                    q.add(new Point(nx, ny));
                }
            }
        }

        return false;
    }

    void findBlockTimes() {
        int currLeft = q.size(), nextLeft = 0, currCost = 0;
        blockTime = new int[N][N];
        Point c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            blockTime[c.y][c.x] = currCost * S;

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (grid[ny][nx] && !visited[ny][nx]) {
                    visited[ny][nx] = true;
                    nextLeft++;
                    q.add(new Point(nx, ny));
                }
            }
        }
    }

    static class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("mecho.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mecho.out")));
        new mecho(in, out);
        in.close();
        out.close();
    }
}
