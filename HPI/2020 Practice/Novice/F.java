import java.util.*;
import java.io.*;

public class F {
    int N;
    Point[] computers;
    int[] cx1 = {1, 0, -1, 0}, cy1 = {0, 1, 0, -1};
    int[] cx2 = {1, -1, -1, 1}, cy2 = {1, -1, 1, -1};
    int[] cx3 = {2, 0, -2, 0}, cy3 = {0, 2, 0, -2};
    int[][] grid;

    F(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new int[N][N];
        computers = new Point[3];
        int currComp = 0;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < N; j++) {
                grid[i][j] = Integer.parseInt(st.nextToken());
                if (grid[i][j] == 2) {
                    computers[currComp++] = new Point(j, i);
                    grid[i][j] = currComp + 1;
                }
            }
        }

        // Try all combinations
        int answer = bfs();
        out.println(answer);
    }

    int bfs() {
        boolean[][][][][] visited = new boolean[N][N][2][2][2];
        Queue<State> q = new LinkedList<>();
        q.add(new State(0, 0, 0, 0, 0));
        visited[0][0][0][0][0] = true;

        int currLeft = 1, nextLeft = 0, currCost = 0, minTime = 987654321;

        State c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            if (grid[c.y][c.x] >= 2) {
                // Computer visited!
                int compID = grid[c.y][c.x] - 2;
                if (compID == 0 && c.c1 == 0) {
                    visited[c.y][c.x][1][c.c2][c.c3] = true;
                    q.add(new State(c.x, c.y, 1, c.c2, c.c3));
                } else if (compID == 1 && c.c2 == 0) {
                    visited[c.y][c.x][c.c1][1][c.c3] = true;
                    q.add(new State(c.x, c.y, c.c1, 1, c.c3));
                } else if (c.c3 == 0) {
                    visited[c.y][c.x][c.c1][c.c2][1] = true;
                    q.add(new State(c.x, c.y, c.c1, c.c2, 1));
                }
            }

            int cv = c.c1 + c.c2 + c.c3, nx, ny;
            if (cv == 3) {
                // All computers hacked!
                minTime = Math.min(currCost, minTime);
                continue;
            }

            for (int i = 0; i < 4; i++) {
                nx = c.x + cx1[i];
                ny = c.y + cy1[i];
                if (inBounds(nx, ny) && !visited[ny][nx][c.c1][c.c2][c.c3] && grid[ny][nx] != 1) {
                    q.add(new State(nx, ny, c.c1, c.c2, c.c3));
                    visited[ny][nx][c.c1][c.c2][c.c3] = true;
                    nextLeft++;
                }
            }

            // Stage 2
            if (cv >= 1) {
                for (int i = 0; i < 4; i++) {
                    nx = c.x + cx2[i];
                    ny = c.y + cy2[i];
                    if (inBounds(nx, ny) && !visited[ny][nx][c.c1][c.c2][c.c3] && grid[ny][nx] != 1) {
                        q.add(new State(nx, ny, c.c1, c.c2, c.c3));
                        visited[ny][nx][c.c1][c.c2][c.c3] = true;
                        nextLeft++;
                    }
                }
            }

            // Stage 3
            if (cv >= 2) {
                for (int i = 0; i < 4; i++) {
                    nx = c.x + cx3[i];
                    ny = c.y + cy3[i];
                    if (inBounds(nx, ny) && !visited[ny][nx][c.c1][c.c2][c.c3] && grid[ny][nx] != 1) {
                        q.add(new State(nx, ny, c.c1, c.c2, c.c3));
                        visited[ny][nx][c.c1][c.c2][c.c3] = true;
                        nextLeft++;
                    }
                }
            }
        }
        return minTime;
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    class State {
        int x, y;
        int c1, c2, c3;
        State(int xx, int yy, int c11, int c22, int c33) {
            x = xx;
            y = yy;
            c1 = c11;
            c2 = c22;
            c3 = c33;
        }
    }

    class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new F(in, out);
        in.close();
        out.close();
    }
}