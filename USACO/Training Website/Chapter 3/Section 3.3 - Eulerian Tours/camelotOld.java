/*
ID: sunnyky1
LANG: JAVA
TASK: camelot

Solution: First, do a BFS from every square to fill the adjacency matrix for all cells. Then, try every possible
meeting location for the pieces. For each of these locations, try all locations where the king could be. If the king's
location has a knight on it already (or it's the target square), the cost is just sum(knight costs) + king movement cost.
Else, try using all the knights to pick up the king. In this case, the cost is:
sum(knight costs) + king movement cost - cost(knight, meet square) + cost(knight, king) + cost(king, meet square).

Runtime: O((RC)^3 / 4) - Should fit within the time limit...?
*/

import java.util.*;
import java.io.*;

public class camelotOld {
    final int INF = 987654321;
    final int[] cx = {2, 1, -1, -2, -2, -1, 1, 2};
    final int[] cy = {-1, -2, -2, -1, 1, 2, 2, 1};
    int R, C;
    Point initKingLoc;
    int[][] adj;
    boolean[] hasKnight;
    ArrayList<Integer> knights = new ArrayList<>();

    camelotOld(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        hasKnight = new boolean[R*C];
        String line = in.readLine();
        while (line != null) {
            st = new StringTokenizer(line);
            while (st.hasMoreTokens()) {
                int col = st.nextToken().charAt(0) - 'A';
                int row = Integer.parseInt(st.nextToken()) - 1;
                if (initKingLoc == null) initKingLoc = new Point(col, row);
                else {
                    int hash = hash(col, row);
                    hasKnight[hash] = true;
                    knights.add(hash);
                }
            }
            line = in.readLine();
        }

        // Fill adjacency matrix
        adj = new int[R*C][];
        for (int i = 0; i < R*C; i++) adj[i] = bfs(i);

        // Try all meeting points
        int answer = INF;
        for (int i = 0; i < R*C; i++) {
            answer = Math.min(tryMeetingAt(i), answer);
        }
        out.println(answer);
    }

    int tryMeetingAt(int n) {
        int nx = getX(n), ny = getY(n), minCost = INF, knightCostSum = 0;
        // Calculate knight cost sum
        for (int i : knights) {
            if (adj[i][n] == INF) return INF;
            knightCostSum += adj[i][n];
        }

        // Now, try every possible location for the king
        int kx, ky;
        for (int i = 0; i < R*C; i++) {
            kx = getX(i);
            ky = getY(i);
            int kingMovementCost = Math.max(Math.abs(kx-initKingLoc.x), Math.abs(ky-initKingLoc.y));
            if (hasKnight[i] || (i == n)) {
                // King will be carried no matter what (or it's at the right square)
                minCost = Math.min(knightCostSum + kingMovementCost, minCost);
            } else {
                // King must be carried by another knight; try all of them
                for (int j : knights) {
                    if (adj[j][i] == INF || adj[i][n] == INF) continue;
                    int cost = knightCostSum + kingMovementCost - adj[j][n] + adj[j][i] + adj[i][n];
                    minCost = Math.min(cost, minCost);
                }
            }
        }
        return minCost;
    }

    int hash(int x, int y) {
        return y * C + x;
    }

    int getX(int hash) {
        return hash % C;
    }

    int getY(int hash) {
        return hash / C;
    }

    int[] bfs(int s) {
        boolean[] visited = new boolean[R*C];
        visited[s] = true;
        int[] dists = new int[R*C];
        Arrays.fill(dists, INF);
        dists[s] = 0;
        Queue<Point> q = new LinkedList<>();
        q.add(new Point(s));
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

            int nx, ny, hash;
            for (int i = 0; i < 8; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (nx >= 0 && nx < C && ny >= 0 && ny < R) {
                    hash = hash(nx, ny);
                    if (!visited[hash]) {
                        visited[hash] = true;
                        dists[hash] = currCost + 1;
                        nextLeft++;
                        q.add(new Point(nx, ny));
                    }
                }
            }
        }
        return dists;
    }

    class Point {
        int x, y;
        Point(int hash) {
            x = getX(hash);
            y = getY(hash);
        }
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("camelot.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("camelot.out")));
        new camelotOld(in, out);
        in.close();
        out.close();
    }
}
