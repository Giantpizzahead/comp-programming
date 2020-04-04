import java.util.*;

public class F {
    int N;
    Point comp1, comp2, comp3;
    int[][] grid;
    final int INF = 98765432;

    F() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        grid = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = sc.nextInt();
                if (grid[i][j] == 2) {
                    if (comp1 == null) {
                        comp1 = new Point(j, i);
                    } else if (comp2 == null) {
                        comp2 = new Point(j, i);
                        grid[i][j] = 3;
                    } else {
                        comp3 = new Point(j, i);
                        grid[i][j] = 4;
                    }
                }
            }
        }

        int[] dist1 = bfs(0, 0, 1);
        int[][] dist2 = new int[3][];
        dist2[0] = bfs(comp1.x, comp1.y, 2);
        dist2[1] = bfs(comp2.x, comp2.y, 2);
        dist2[2] = bfs(comp3.x, comp3.y, 2);
        int[][] dist3 = new int[3][];
        dist3[0] = bfs(comp1.x, comp1.y, 3);
        dist3[1] = bfs(comp2.x, comp2.y, 3);
        dist3[2] = bfs(comp3.x, comp3.y, 3);

        // Try all orders
        int minTime = INF;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;
                int k = 3 - i - j;
                int currTime = dist1[i] + dist2[i][j] + dist3[j][k];
                minTime = Math.min(minTime, currTime);
            }
        }
        System.out.println(minTime);
    }

    int[] cx1 = {1, 0, -1, 0}, cy1 = {0, 1, 0, -1};
    int[] cx2 = {1, 1, -1, -1}, cy2 = {1, -1, 1, -1};
    int[] bfs(int sx, int sy, int stage) {
        int[] dists = new int[3];
        Arrays.fill(dists, INF);
        boolean[][] visited = new boolean[N][N];
        visited[sy][sx] = true;

        Queue<Point> q = new LinkedList<>();
        q.add(new Point(sx, sy));
        int currLeft = 1, nextLeft = 0, currCost = 0;

        Point c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            if (grid[c.y][c.x] >= 2) {
                if (grid[c.y][c.x] == 2) dists[0] = currCost;
                else if (grid[c.y][c.x] == 3) dists[1] = currCost;
                else dists[2] = currCost;
            }

            // Stage 1
            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx1[i];
                ny = c.y + cy1[i];
                if (inBounds(nx, ny) && !visited[ny][nx] && grid[ny][nx] != 1) {
                    visited[ny][nx] = true;
                    q.add(new Point(nx, ny));
                    nextLeft++;
                }
            }

            // Stage 2
            if (stage >= 2) {
                for (int i = 0; i < 4; i++) {
                    nx = c.x + cx2[i];
                    ny = c.y + cy2[i];
                    if (inBounds(nx, ny) && !visited[ny][nx] && grid[ny][nx] != 1) {
                        visited[ny][nx] = true;
                        q.add(new Point(nx, ny));
                        nextLeft++;
                    }
                }
            }

            // Stage 3
            if (stage == 3) {
                int mx, my;
                for (int i = 0; i < 4; i++) {
                    mx = c.x + cx1[i];
                    my = c.y + cy1[i];
                    nx = c.x + cx1[i] * 2;
                    ny = c.y + cy1[i] * 2;
                    if (inBounds(nx, ny) && !visited[ny][nx] && grid[ny][nx] != 1 && grid[my][mx] == 1) {
                        // Jump!
                        visited[ny][nx] = true;
                        q.add(new Point(nx, ny));
                        nextLeft++;
                    }
                }
            }
        }
        return dists;
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    class Point {
        int x, y;
        Point(int xx, int yy) {
            x = xx;
            y = yy;
        }
    }

    public static void main(String[] args) {
        new F();
    }
}
