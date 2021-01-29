/*
Solution: All breeders with <= dist to exit than you can & will fight with you.
Runtime: O(RC)
*/

import java.util.*;
import java.io.*;

public class forest {
    final int[] cx = {1, 0, -1, 0}, cy = {0, 1, 0, -1};
    int R, C;
    Point start, exit;
    int[][] grid;

    forest(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        R += 2;
        C += 2;
        grid = new int[R][C];
        for (int y = 1; y < R - 1; y++) {
            char[] chars = in.readLine().toCharArray();
            for (int x = 1; x < C - 1; x++) {
                char c = chars[x-1];
                if (c == 'S') {
                    start = new Point(x, y);
                    grid[y][x] = 0;
                } else if (c == 'E') {
                    exit = new Point(x, y);
                    grid[y][x] = 0;
                } else if (c == 'T') grid[y][x] = -1;
                else grid[y][x] = c - '0';
            }
        }
        // Make border
        for (int x = 0; x < C; x++) {
            grid[0][x] = -1;
            grid[R-1][x] = -1;
        }
        for (int y = 0; y < R; y++) {
            grid[y][0] = -1;
            grid[y][C-1] = -1;
        }
        // BFS
        out.println(bfs());
    }

    int bfs() {
        Queue<Point> toEval = new LinkedList<>();
        toEval.add(exit);
        int currLeft = 1, nextLeft = 0, currDist = 0;
        int answer = 0;
        boolean[][] visited = new boolean[R][C];
        visited[exit.y][exit.x] = true;
        boolean startFound = false;

        Point c;
        while (!toEval.isEmpty()) {
            c = toEval.poll();

            if (currLeft == 0) {
                if (startFound) return answer;  // Done
                currLeft = nextLeft;
                nextLeft = 0;
                currDist++;
            }
            currLeft--;

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (!visited[ny][nx] && grid[ny][nx] != -1) {
                    if (nx == start.x && ny == start.y) startFound = true;
                    nextLeft++;
                    visited[ny][nx] = true;
                    answer += grid[ny][nx];
                    toEval.add(new Point(nx, ny));
                }
            }
        }
        return -1;
    }

    static class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("forest.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("forest.out")));
        new forest(in, out);
        in.close();
        out.close();
    }
}
