import java.util.*;

public class G {
    final int INF = 9876543;
    int N, M;
    char[][] grid;
    int[] cx = {1, 0, -1, 0}, cy = {0, 1, 0, -1};

    G() {
        Scanner sc = new Scanner(System.in);
        N = sc.nextInt();
        M = sc.nextInt();
        sc.nextLine();
        grid = new char[N][];
        for (int i = 0; i < N; i++) grid[i] = sc.nextLine().toCharArray();
        // for (int i = 0; i < N; i++) System.out.println(Arrays.toString(grid[i]));

        // Start with borders
        PriorityQueue<State> pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State o1, State o2) {
                return o1.alt - o2.alt;
            }
        });
        boolean[][] explored = new boolean[N][M];
        int[][] minAlt = new int[N][M];
        for (int i = 0; i < N; i++) Arrays.fill(minAlt[i], INF);

        for (int i = 0; i < M; i++) {
            if (grid[0][i] == '.') {
                pq.add(new State(i, 0, 0));
                minAlt[0][i] = 0;
            } else {
                pq.add(new State(i, 0, 1));
                minAlt[0][i] = 1;
            }

            if (grid[N-1][i] == '.') {
                pq.add(new State(i, N-1, 0));
                minAlt[N-1][i] = 0;
            } else {
                pq.add(new State(i, N-1, 1));
                minAlt[N-1][i] = 1;
            }
        }

        for (int i = 0; i < N; i++) {
            if (grid[i][0] == '.') {
                pq.add(new State(0, i, 0));
                minAlt[i][0] = 0;
            } else {
                pq.add(new State(0, i, 1));
                minAlt[i][0] = 1;
            }

            if (grid[i][M-1] == '.') {
                pq.add(new State(M-1, i, 0));
                minAlt[i][M-1] = 0;
            } else {
                pq.add(new State(M-1, i, 1));
                minAlt[i][M-1] = 1;
            }
        }

        int maxAlt = 0;
        State c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            if (explored[c.y][c.x]) continue;
            explored[c.y][c.x] = true;
            maxAlt = Math.max(c.alt, maxAlt);

            int nx, ny;
            for (int i = 0; i < 4; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (nx >= 0 && nx < M && ny >= 0 && ny < N && !explored[ny][nx]) {
                    int nalt;
                    if (grid[ny][nx] == '.') nalt = c.alt;
                    else if (grid[c.y][c.x] == '#' || grid[c.y][c.x] == '*') nalt = c.alt;
                    else nalt = c.alt + 1;
                    if (nalt < minAlt[ny][nx]) {
                        minAlt[ny][nx] = nalt;
                        pq.add(new State(nx, ny, nalt));
                    }
                }
            }
        }

        System.out.println(maxAlt);
    }

    class State {
        int x, y, alt;
        State(int xx, int yy, int altt) {
            x = xx;
            y = yy;
            alt = altt;
        }
    }

    public static void main(String[] args) {
        new G();
    }
}
