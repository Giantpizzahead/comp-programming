/*
Solution: First, find all the 2-edge connected components (split the implied graph up by the bridges). Label each cell
in the grid with its component id.

Then, do an initial BFS to find the starting states for Bessie. The states are (boxX, boxY, bessieLoc), where bessieLoc
is from 0-3 indicating right, down, left, or up (total O(4NM) states). When evaluating a state, check if the other
locations have the same component ID. If they do, then allow the transition. Also, try moving the box in the current
direction.

At the end, just iterate through the queries, checking if any of the 4 states at the queried (x, y) position were
visited.

Runtime: O(20NM)
*/

import java.util.*;
import java.io.*;

public class pushabox {
    int rows, cols, queries;
    Point bessieStart, boxStart;
    char[][] grid;
    int[] cx = {1, 0, -1, 0, 1, 0, -1, 0};
    int[] cy = {0, 1, 0, -1, 0, 1, 0, -1};

    pushabox(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        // To optimize search (no need to check in bounds), add border of #s
        rows = Integer.parseInt(st.nextToken()) + 2;
        cols = Integer.parseInt(st.nextToken()) + 2;
        queries = Integer.parseInt(st.nextToken());
        grid = new char[rows + 2][cols + 2];
        for (int y = 1; y < rows - 1; y++) {
            String line = in.readLine();
            for (int x = 1; x < cols - 1; x++) {
                grid[y][x] = line.charAt(x-1);
                if (grid[y][x] == 'A') bessieStart = new Point(x, y);
                else if (grid[y][x] == 'B') boxStart = new Point(x, y);
            }
        }

        // Make border of #s
        for (int x = 0; x < cols; x++) {
            grid[0][x] = '#';
            grid[rows - 1][x] = '#';
        }
        for (int y = 0; y < rows; y++) {
            grid[y][0] = '#';
            grid[y][cols - 1] = '#';
        }

        // Find bridges / make components
        comp = new int[rows][cols];
        pre = new int[rows][cols];
        low = new int[rows][cols];
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                if (pre[y][x] == 0 && grid[y][x] != '#') {
                    findBridges(x, y, -1);
                    // Make new comp if needed
                    if (!currNodes.isEmpty()) {
                        Point p;
                        while (!currNodes.isEmpty()) {
                            p = currNodes.pop();
                            comp[p.y][p.x] = currComp;
                        }
                        currComp++;
                    }
                }
            }
        }

//        System.out.println("pre:");
//        for (int y = 0; y < rows; y++) System.out.println(Arrays.toString(pre[y]));
//        System.out.println("low:");
//        for (int y = 0; y < rows; y++) System.out.println(Arrays.toString(low[y]));
//        System.out.println("comp:");
//        for (int y = 0; y < rows; y++) System.out.println(Arrays.toString(comp[y]));

        visited = new boolean[rows][cols][4];
        singleVisited = new boolean[rows][cols];
        q = new Stack<>();
        initialDFS(bessieStart.x, bessieStart.y);
        
        mainSearch();

        /*
        // Reuse singleVisited for final check
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                singleVisited[y][x] = false;
                for (int i = 0; i < 4; i++) singleVisited[y][x] |= visited[y][x][i];
            }
        }
        singleVisited[boxStart.y][boxStart.x] = true;

        System.out.println("reach:");
        for (int y = 1; y < rows - 1; y++) {
            for (int x = 1; x < cols - 1; x++) {
                System.out.print(singleVisited[y][x] ? 1 : 0);
            }
            System.out.println();
        }
         */

        // Answer queries
        int x, y;
        for (int i = 0; i < queries; i++) {
            st = new StringTokenizer(in.readLine());
            y = Integer.parseInt(st.nextToken());
            x = Integer.parseInt(st.nextToken());
            boolean result = y == boxStart.y && x == boxStart.x;
            for (int j = 0; j < 4; j++) result |= visited[y][x][j];
            out.println(result ? "YES" : "NO");
        }
    }

    boolean[][][] visited;
    Stack<State> q;
    boolean[][] singleVisited;
    
    void mainSearch() {
        State c;
        while (!q.isEmpty()) {
            c = q.pop();
            // Try moving to different sides of the box
            int bx = c.x + cx[c.d], by = c.y + cy[c.d], nx, ny;
            for (int i = 0; i < 4; i++) {
                if (i == c.d) {
                    // Move box in opposite direction (if possible)
                    int mx = c.x + cx[c.d + 2];
                    int my = c.y + cy[c.d + 2];
                    if (!visited[my][mx][i] && grid[my][mx] != '#') {
                        // Can move this way
                        visited[my][mx][i] = true;
                        q.add(new State(mx, my, i));
                    }
                } else {
                    nx = c.x + cx[i];
                    ny = c.y + cy[i];
                    if (!visited[c.y][c.x][i] && comp[by][bx] == comp[ny][nx]) {
                        // In same component, so Bessie can reach it
                        visited[c.y][c.x][i] = true;
                        q.add(new State(c.x, c.y, i));
                    }
                }
            }
        }
    }
    
    void initialDFS(int x, int y) {
        singleVisited[y][x] = true;
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            nx = x + cx[i];
            ny = y + cy[i];
            if (!singleVisited[ny][nx] && grid[ny][nx] != '#') {
                if (grid[ny][nx] == 'B') {
                    // Box found; this is an initial state
                    q.add(new State(nx, ny, (i + 2) % 4));
                    visited[ny][nx][(i + 2) % 4] = true;
                } else initialDFS(nx, ny);
            }
        }
    }

    int currComp = 1, currPre = 1;
    int[][] comp, pre, low;
    Stack<Point> currNodes = new Stack<>();
    void findBridges(int x, int y, int from) {
        pre[y][x] = currPre++;
        low[y][x] = pre[y][x];
        currNodes.add(new Point(x, y));
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            if (i == from) continue;  // No going back
            nx = x + cx[i];
            ny = y + cy[i];
            if (grid[ny][nx] != '#') {
                if (pre[ny][nx] != 0) {
                    // Already visited
                    low[y][x] = Math.min(pre[ny][nx], low[y][x]);
                } else {
                    // DFS
                    findBridges(nx, ny, (i + 2) % 4);
                    low[y][x] = Math.min(low[ny][nx], low[y][x]);
                    if (pre[y][x] < low[ny][nx]) {
                        // This edge is a bridge (never came back to current component); make new comp
                        Point p = currNodes.pop();
                        while (p.x != nx || p.y != ny) {
                            comp[p.y][p.x] = currComp;
                            p = currNodes.pop();
                        }
                        comp[p.y][p.x] = currComp;
                        currComp++;
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("pushabox.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("pushabox.out")));
        new pushabox(in, out);
        in.close();
        out.close();
    }

    static class Point {
        int x, y;
        Point(int xx, int yy) {
            x = xx;
            y = yy;
        }
    }

    static class State {
        int x, y, d;
        State(int x, int y, int d) {
            this.x = x;
            this.y = y;
            this.d = d;
        }

        public String toString() {
            return String.format("(%d, %d, %d)", x, y, d);
        }
    }
}