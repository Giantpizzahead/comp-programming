/*
ID: sunnyky1
LANG: JAVA
TASK: camelot

Solution: Modified Dijkstra, with a boolean state tracking whether the current knight has
picked up the king or not. At every node, try adding a new state with the king picked up
with cost = distance to the king (have the king move to the knight). Track the sum of all
moves needed to gather all evaluated knights in each square, and take the min of these at
the end.
Runtime: O((2RC)^2 * log(16RC))
*/

import java.util.*;
import java.io.*;

public class camelot {
    final int INF = 987654321;
    final int[] cx = {2, 1, -1, -2, -2, -1, 1, 2}, cy = {1, 2, 2, 1, -1, -2, -2, -1};
    int R, C, kingX = -1, kingY = -1;
    int[][] currMoveSum, minAddedCost;
    boolean[][] board;

    camelot(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        board = new boolean[R][C];

        String line = in.readLine();
        while (line != null) {
            st = new StringTokenizer(line);
            while (st.hasMoreTokens()) {
                int col = st.nextToken().charAt(0) - 'A';
                int row = Integer.parseInt(st.nextToken()) - 1;
                if (kingX == -1) {
                    kingX = col;
                    kingY = row;
                } else {
                    board[row][col] = true;
                }
            }
            line = in.readLine();
        }

        // Process each knight
        currMoveSum = new int[R][C];
        minAddedCost = new int[R][C];
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                minAddedCost[y][x] = Math.max(Math.abs(kingX - x), Math.abs(kingY - y));
            }
        }
        bestDist = new int[R][C];
        bestPickupDist = new int[R][C];
        pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State o1, State o2) {
                return o1.c - o2.c;
            }
        });
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                if (board[y][x]) processKnight(x, y);
            }
        }

        // Find the best gathering square
        int answer = INF;
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                answer = Math.min(currMoveSum[y][x] + minAddedCost[y][x], answer);
            }
        }
        out.println(answer);
    }

    int[][] bestDist;
    int[][] bestPickupDist;
    PriorityQueue<State> pq;
    void processKnight(int sx, int sy) {
        for (int i = 0; i < R; i++) {
            Arrays.fill(bestDist[i], INF);
            Arrays.fill(bestPickupDist[i], INF);
        }
        bestDist[sy][sx] = 0;
        pq.clear();
        pq.add(new State(sx, sy, 0, false));

        State c;
        while (!pq.isEmpty()) {
            c = pq.poll();
            // Add pickup state if needed
            if (!c.kingPickedUp) {
                int pickupCost = Math.max(Math.abs(kingX - c.x), Math.abs(kingY - c.y));
                if (c.c + pickupCost < bestPickupDist[c.y][c.x]) {
                    bestPickupDist[c.y][c.x] = c.c + pickupCost;
                    pq.add(new State(c.x, c.y, c.c + pickupCost, true));
                }
            }
            // Jump to new squares
            int nx, ny;
            for (int i = 0; i < 8; i++) {
                nx = c.x + cx[i];
                ny = c.y + cy[i];
                if (nx >= 0 && nx < C && ny >= 0 && ny < R) {
                    if (!c.kingPickedUp) {
                        if (c.c + 1 < bestDist[ny][nx]) {
                            bestDist[ny][nx] = c.c + 1;
                            pq.add(new State(nx, ny, c.c + 1, false));
                        }
                    } else if (c.c + 1 < bestPickupDist[ny][nx]) {
                        bestPickupDist[ny][nx] = c.c + 1;
                        pq.add(new State(nx, ny, c.c + 1, true));
                    }
                }
            }
        }

        // Update sums and added costs
        for (int y = 0; y < R; y++) {
            for (int x = 0; x < C; x++) {
                if (bestDist[y][x] == INF) {
                    currMoveSum[y][x] = INF;
                } else {
                    if (currMoveSum[y][x] != INF) currMoveSum[y][x] += bestDist[y][x];
                    if (bestPickupDist[y][x] - bestDist[y][x] < minAddedCost[y][x]) {
                        minAddedCost[y][x] = bestPickupDist[y][x] - bestDist[y][x];
                    }
                }
            }
        }
    }

    static class State {
        int x, y, c;
        boolean kingPickedUp;
        State(int x, int y, int c, boolean k) {
            this.x = x;
            this.y = y;
            this.c = c;
            kingPickedUp = k;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("camelot.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("camelot.out")));
        new camelot(in, out);
        in.close();
        out.close();
    }
}
