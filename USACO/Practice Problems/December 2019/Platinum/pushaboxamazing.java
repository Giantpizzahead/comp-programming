/*
Solution: First, find all the articulation points. Then, label all the
'edges' in the implied graph with their component ID (based on the splitting
of those articulation points). Then, do a BFS, with the states being
(boxX, boxY, side of the box that Bessie is on). The transitions are either
pushing the box in the current direction, or Bessie moving to a different
side of the box (valid if the 2 edges connected to the box are in the same
component ID, meaning the box doesn't split the 2 sides up). Finally,
answer the queries by checking if the BFS reached that query location.
Runtime: O(16NM)

Note: Lots of small optimizations have been made here or there, since the time limit
for this problem is very mean to Java. ;(
*/

import java.io.*;
import java.util.StringTokenizer;

public class pushaboxamazing {
    final int INF = 987654321;
    final int MAXN = 1502;
    final int MAXM = 1502;
    int N, M, Q;
    boolean[][] grid = new boolean[MAXN][MAXM];
    int[][][] edgeID = new int[MAXN][MAXM][2];
    int bessieX, bessieY, boxX, boxY;
    int[] cx = {1, 0, -1, 0}, cy = {0, 1, 0, -1};
    int[] oppcx = {-1, 0, 1, 0}, oppcy = {0, -1, 0, 1}, oppDir = {2, 3, 0, 1};

    pushaboxamazing(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        // For easier implementation, put #s on the borders of the grid
        N += 2;
        M += 2;
        for (int y = 0; y < N; y++) {
            disc[y][0] = INF;
            disc[y][M-1] = INF;
        }
        for (int x = 0; x < M; x++) {
            disc[0][x] = INF;
            disc[N-1][x] = INF;
        }
        for (int y = 1; y < N - 1; y++) {
            char[] line = in.readLine().toCharArray();
            for (int x = 1; x < M - 1; x++) {
                char ch = line[x-1];
                // Remember starting locs, but treat it as an open square
                // for easier implementation
                if (ch == 'A') {
                    bessieX = x;
                    bessieY = y;
                } else if (ch == 'B') {
                    boxX = x;
                    boxY = y;
                }
                if (ch == '#') {
                    disc[y][x] = INF;
                } else {
                    grid[y][x] = true;
                }
            }
        }

        // Find articulation points & label edges with their ids
        // edgeID[y][x][d] = ID of the edge from (x, y) towards direction d
        // 0, 1 -> Right, down
        for (int i = 0; i < stack.length; i++) {
            stack[i] = new Triple();
        }
        findArtPoints(boxX, boxY, -1);

        // System.out.println(Arrays.deepToString(edgeID));
        
        // Find initial DFS states / start main DFS
        // (x, y, d) = boxX, boxY, direction the box would be
        // pushed in at Bessie's current location
        disc[bessieY][bessieX] = INF;
        initialDFS(bessieX, bessieY);

//        for (int y = 0; y < N; y++) {
//            for (int x = 0; x < M; x++) {
//                boolean canReach = false;
//                for (int d = 0; d < 4; d++) {
//                    canReach |= visited[y][x][d];
//                }
//                System.out.print(canReach + " ");
//            }
//            System.out.println();
//        }

        int a, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            boolean canReach = (a == boxY && b == boxX) || (visited[a][b] != 0);
            out.println(canReach ? "YES" : "NO");
        }
    }
    
    byte[][] visited = new byte[MAXN][MAXM];
    void initialDFS(int x, int y) {
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            nx = x + cx[i];
            ny = y + cy[i];
            if (disc[ny][nx] != INF) {
                disc[ny][nx] = INF;  // Visited marker
                if (boxX == nx && boxY == ny) {
                    // Starting state found
                    if ((visited[boxY][boxX] & (1 << i)) == 0) {
                        visited[boxY][boxX] += 1 << i;
                        dfs(boxX, boxY, i);
                    }
                } else initialDFS(nx, ny);
            }
        }
    }

    void dfs(int x, int y, int d) {
        // Do all transitions
        int nx = x + cx[d];
        int ny = y + cy[d];
        int e1, e2;
        if (d < 2) e1 = edgeID[y + oppcy[d]][x + oppcx[d]][d];
        else e1 = edgeID[y][x][oppDir[d]];
        for (int od = 0; od < 4; od++) {
            if (d == od) {
                // Move the box
                if ((visited[ny][nx] & (1 << d)) == 0 && grid[ny][nx]) {
                    visited[ny][nx] += 1 << d;
                    dfs(nx, ny, d);
                }
            } else {
                // Try moving to this side
                if (od < 2) e2 = edgeID[y + oppcy[od]][x + oppcx[od]][od];
                else e2 = edgeID[y][x][oppDir[od]];
                if (e1 == e2) {
                    // This transition works (box does not cutoff these 2 edges)
                    if ((visited[y][x] & (1 << od)) == 0) {
                        visited[y][x] += 1 << od;
                        // System.out.println("rotate " + x + " " + y + " " + d + " " + od);
                        dfs(x, y, od);
                    }
                }
            }
        }
    }

    Triple[] stack = new Triple[MAXN * MAXM * 2];
    int top = 0, currDisc = 1, currComp = 1;
    int[][] disc = new int[MAXN][MAXM];
    int[][] lowlink = new int[MAXN][MAXM];
    void findArtPoints(int x, int y, int d) {
        disc[y][x] = currDisc;
        lowlink[y][x] = currDisc++;
        int nx, ny, lastTop = -1;
        for (int i = 0; i < 4; i++) {
            nx = x + cx[i];
            ny = y + cy[i];
            if (!grid[ny][nx] || oppDir[i] == d) continue;
            if (i < 2) {
                if (edgeID[y][x][i] == 0) {
                    lastTop = top++;
                    stack[lastTop].x = x;
                    stack[lastTop].y = y;
                    stack[lastTop].d = i;
                    edgeID[y][x][i] = -1;
                }
            } else {
                if (edgeID[ny][nx][oppDir[i]] == 0) {
                    lastTop = top++;
                    stack[lastTop].x = nx;
                    stack[lastTop].y = ny;
                    stack[lastTop].d = oppDir[i];
                    edgeID[ny][nx][oppDir[i]] = -1;
                }
            }
            if (disc[ny][nx] != 0) {
                // Update lowlink
                lowlink[y][x] = Math.min(disc[ny][nx], lowlink[y][x]);
            } else {
                // Continue searching for articulation points
                findArtPoints(nx, ny, i);
                if (disc[y][x] <= lowlink[ny][nx]) {
                    // This subtree never escaped this node; this is an
                    // articulation point (at least for that subtree)
                    // Label those nodes
                    Triple ce;
                    while (top != lastTop) {
                        ce = stack[--top];
                        edgeID[ce.y][ce.x][ce.d] = currComp;
                    }
                    currComp++;
                }
                lowlink[y][x] = Math.min(lowlink[ny][nx], lowlink[y][x]);
            }
        }
    }

    static class Triple {
        int x, y, d;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("pushabox.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pushabox.out")));
        new pushaboxamazing(in, out);
        in.close();
        out.close();
    }
}