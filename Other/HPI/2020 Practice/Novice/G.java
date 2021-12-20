import java.util.*;
import java.io.*;

public class G {
    int N, M, K;
    int sx, sy, ex, ey;
    int[] cx, cy;
    boolean[][] grid;
    int[][] bestDist;
    final int INF = 987654321;

    G(BufferedReader in) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(in.readLine());
        grid = new boolean[N][M];
        for (int i = 0; i < N; i++) {
            String str = in.readLine();
            for (int j = 0; j < M; j++) {
                if (str.charAt(j) == 'X') grid[i][j] = false;
                else if (str.charAt(j) == '.') grid[i][j] = true;
                else if (str.charAt(j) == 'A') {
                    sx = j;
                    sy = i;
                    grid[i][j] = true;
                } else {
                    ex = j;
                    ey = i;
                    grid[i][j] = true;
                }
            }
        }
        cx = new int[K];
        cy = new int[K];
        for (int i = 0; i < K; i++) {
            st = new StringTokenizer(in.readLine());
            cx[i] = Integer.parseInt(st.nextToken());
            cy[i] = -Integer.parseInt(st.nextToken());
        }
        bfs();

        // Find shortest dist
        int minDist = INF, minMoves = INF;
        boolean[][] visited = new boolean[N][M];
        int[] cx2 = {1, 0, -1, 0}, cy2 = {0, 1, 0, -1};
        Queue<Point> q = new LinkedList<>();
        int currLeft = 1, nextLeft = 0, currCost = 0;
        q.add(new Point(ex, ey));
        visited[ey][ex] = true;

        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(bestDist[i]));

        Point c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            if (minDist < currCost) break;
            else if (bestDist[c.y][c.x] != INF) {
                minDist = currCost;
                minMoves = Math.min(bestDist[c.y][c.x], minMoves);
            }

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx2[i];
                ny = c.y + cy2[i];
                if (inBounds(nx, ny) && !visited[ny][nx]) {
                    q.add(new Point(nx, ny));
                    nextLeft++;
                }
            }
        }

        if (minDist == 0) {
            System.out.println("YES");
            System.out.println(minMoves);
        } else {
            System.out.println("NO");
            System.out.println(minDist + " " + minMoves);
        }
    }

    void bfs() {
        bestDist = new int[N][M];
        for (int i = 0; i < N; i++) Arrays.fill(bestDist[i], INF);
        bestDist[sy][sx] = 0;
        Queue<Point> q = new LinkedList<>();
        q.add(new Point(sx, sy));

        Point c;
        while (!q.isEmpty()) {
            c = q.poll();
            int nx, ny;
            for (int i = 0; i < K; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (inBounds(nx, ny) && grid[ny][nx] && bestDist[ny][nx] == INF) {
                    bestDist[ny][nx] = bestDist[c.y][c.x] + 1;
                    q.add(new Point(nx, ny));
                }
            }
        }
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < M && y >= 0 && y < N;
    }

    class Point {
        int x, y;
        Point(int xx, int yy) {
            x = xx;
            y = yy;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        new G(in);
    }
}
