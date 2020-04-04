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
import java.util.ArrayList;
import java.util.StringTokenizer;

public class cave3 {
    int N, M, numComps;
    long answer;
    char[][] grid;
    int[][] compID, setID;
    Component[] components;
    int[] cx = {1, 0, -1, 0};
    int[] cy = {0, 1, 0, -1};
    final int INF = 1987654321;
    final int MOD = 1000000007;

    cave3(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int y = 0; y < N; y++) {
            grid[y] = in.readLine().toCharArray();
        }

        // Do initial component search, making sure found components are evaluated in order
        // from bottom to top, and left to right
        compID = new int[N][M];
        setID = new int[N][M];
        numComps = 1;
        for (int y = N - 2; y >= 1; y--) {
            for (int x = 1; x < M - 1; x++) {
                if (grid[y][x] == '#' || compID[y][x] != 0) continue;
                dfsComponent(x, y);
                numComps++;
            }
        }
        numComps--;

        // Now generate components
        components = new Component[numComps];
        for (int i = 0; i < numComps; i++) components[i] = new Component();
        for (int y = N - 2; y >= 1; y--) {
            for (int x = 1; x < M - 1; x++) {
                if (grid[y][x] == '#') continue;
                setID[y][x] = components[compID[y][x] - 1].points.size();
                components[compID[y][x] - 1].addPoint(new Point(x, y));
            }
        }

        // System.out.println(Arrays.toString(components));

        // Evaluate each component separately
        answer = 1;
        for (Component comp : components) evalComponent(comp);
        out.println(answer);
    }

    void evalComponent(Component comp) {
        int dsSize = comp.maxX - comp.minX + 2;
        DisjointSet ds = new DisjointSet(comp.points.size());
        int lastY = -1;
        for (Point p : comp.points) {
            if (lastY != p.y) {
                // Moved up a row; add 1 to all current sets
                for (int i = 0; i < ds.size; i++) ds.numWays[i]++;
            }
            // Merge with sides
            ds.setActive(setID[p.y][p.x]);
            if (grid[p.y][p.x-1] != '#') ds.union(setID[p.y][p.x-1], setID[p.y][p.x]);
            if (grid[p.y][p.x+1] != '#') ds.union(setID[p.y][p.x+1], setID[p.y][p.x]);
            if (grid[p.y-1][p.x] != '#') ds.union(setID[p.y-1][p.x], setID[p.y][p.x]);
            if (grid[p.y+1][p.x] != '#') ds.union(setID[p.y+1][p.x], setID[p.y][p.x]);
            lastY = p.y;
        }

        // Off-by-one (top row filled)
        // Get final answer
        Point finalP = comp.points.get(0);
        long compWays = ds.numWays[ds.find(setID[finalP.y][finalP.x])] + 1;
        answer = (answer * compWays) % MOD;
    }

    void dfsComponent(int x, int y) {
        compID[y][x] = numComps;
        int nx, ny;
        for (int i = 0; i < 4; i++) {
            nx = x + cx[i];
            ny = y + cy[i];
            if (compID[ny][nx] == 0 && grid[ny][nx] != '#') dfsComponent(nx, ny);
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("cave.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cave.out")));
        new cave3(in, out);
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

    class DisjointSet {
        int size;
        int[] vals;
        long[] numWays;
        boolean[] active;

        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            numWays = new long[size];
            active = new boolean[size];
        }

        // Unions the 2 sets, and returns the set they were unioned into.
        int union(int a, int b) {
            if (!active[a] || !active[b]) return -1;
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return setA;
            // Merge into larger set
            if (vals[setA] < vals[setB]) {
                // Merge into set A
                vals[setA] += vals[setB];
                vals[setB] = setA;
                numWays[setA] = (numWays[setA] * numWays[setB]) % MOD;
                // System.out.println("New numways: " + numWays[setA]);
                numWays[setB] = 0;
                return setA;
            } else {
                // Merge into set B
                vals[setB] += vals[setA];
                vals[setA] = setB;
                numWays[setB] = (numWays[setA] * numWays[setB]) % MOD;
                // System.out.println("New numways: " + numWays[setA]);
                numWays[setA] = 0;
                return setB;
            }
        }

        int find(int i) {
            if (!active[i]) return -1;
            else if (vals[i] < 0) return i;
            else {
                int result = find(vals[i]);
                // Path compression
                vals[i] = result;
                return result;
            }
        }

        void setActive(int i) {
            if (!active[i]) {
                active[i] = true;
                vals[i] = -1;
                numWays[i] = 1;
            }
        }
    }
}
