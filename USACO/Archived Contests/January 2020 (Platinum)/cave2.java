/*
Solution: Evaluate each component separately. For each component:
Keep a disjoint set with the currently connected empty squares (x 0 to M - 1).
When you come across an empty square, mark it as active, and union that square with its
left and right sets. When unioning, multiply the numWays for each set by the other one.
Default value for numWays should be 1. If you come across a filled square, do nothing.
At the end, take the numWays value for the first active set that you come across. Multiply
this value with the answer.

Runtime: O(NM)
*/

import java.io.*;
import java.util.*;

public class cave2 {
    int N, M;
    long answer;
    char[][] grid;
    int[][] compID;
    boolean[][] visited;
    int[] cx = {1, 0, -1, 0};
    int[] cy = {0, 1, 0, -1};
    final int INF = 1987654321;
    final int MOD = 1000000007;

    cave2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int y = 0; y < N; y++) {
            grid[y] = in.readLine().toCharArray();
        }

        // Do initial component search to find where to end certain components
        compID = new int[N][M];
        visited = new boolean[N][M];
        for (int y = N - 2; y >= 1; y--) {
            for (int x = 1; x < M - 1; x++) {
                if (grid[y][x] == '#' || visited[y][x]) continue;
                furthest = new Point(-1, INF);
                dfsComponent(x, y);
                compID[furthest.y][furthest.x] = -1;  // Signify that a component ends here
                System.out.println("comp end " + furthest.x + ' ' + furthest.y);
            }
        }

        // Evaluate all components at once
        int currComp = 1;
        HashSet<Integer> activeComps = new HashSet<>();
        int[] numWays = new int[N * M];
        answer = 1;
        for (int y = N - 2; y >= 1; y--) {
            for (int x = 1; x < M - 1; x++) {
                if (grid[y][x] == '#') continue;

                int newCompID;
                if (compID[y+1][x] == 0 && compID[y][x-1] == 0) {
                    // Start a new component
                    newCompID = currComp++;
                    activeComps.add(newCompID);
                    numWays[newCompID] = 1;
                } else if (compID[y][x-1] == 0) {
                    // Extend bottom component
                    newCompID = compID[y+1][x];
                } else if (compID[y+1][x] == 0) {
                    // Extend left component
                    newCompID = compID[y][x-1];
                } else {
                    // Two different components meet here; merge them with left component
                    newCompID = compID[y][x-1];
                    // To avoid overcounting (merging more than once)
                    if (activeComps.contains(compID[y+1][x])) {
                        System.out.println("merge " + newCompID + " " + compID[y+1][x]);
                        activeComps.remove(compID[y+1][x]);
                        numWays[newCompID] = numWays[newCompID] * numWays[compID[y+1][x]] % MOD;
                        System.out.println(numWays[newCompID]);
                    }
                }

                if (compID[y][x] == -1) {
                    // Component ends here
                    // Multiply # ways with answer (+1 for filling top)
                    answer = answer * (numWays[newCompID] + 1) % MOD;
                    activeComps.remove(newCompID);
                }

                compID[y][x] = newCompID;
            }

            for (int i = 0; i < N; i++) System.out.println(Arrays.toString(compID[i]));

            // Update all active comp ways
            for (int active : activeComps) {
                numWays[active]++;
                System.out.println(numWays[active]);
            }
            System.out.println("y " + y + ": " + activeComps);
        }
        out.println(answer);
    }

    Point furthest;
    void dfsComponent(int x, int y) {
        visited[y][x] = true;
        if (furthest.y > y) {
            furthest.x = x;
            furthest.y = y;
        } else if (furthest.x < x) {
            furthest.x = x;
        }
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            nx = x + cx[i];
            ny = y + cy[i];
            if (!visited[ny][nx] && grid[ny][nx] != '#') dfsComponent(nx, ny);
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("cave.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cave.out")));
        new cave2(in, out);
        in.close();
        out.close();
    }

    class Component {
        ArrayList<Point> points = new ArrayList<>(2);
        int minX = INF, maxX = -1;
        void addPoint(Point p) {
            minX = Math.min(p.x, minX);
            maxX = Math.max(p.x, maxX);
            points.add(p);
        }
        public String toString() {
            return "(" + points + ", " + minX + ", " + maxX + ")";
        }
    }

    class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }
}
