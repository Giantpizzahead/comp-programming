/*
Solution: Relies on the fact that if points are chosen in a \-like line (no two points exist where
x1 < x2 and y1 < y2), then the min cut grass amount must be at either the max y coordinate or the
max x coordinate point.

Sweep through points by x coordinate. Keep a segment tree of max numFlowers for a given range 0 to Y.
Also keep a TreeSet[][] array, where [][0] is sorted by max Y, and [][1] by max X.

Keep a val array containing the minimum amount of cut grass at each point.

At each point: Query the segment tree to determine correct # of flowers
Query 2 treesets to find the edge points (max Y = p.y, max X = p.x)
val[point] = Min of 2 calced values
Add # flowers + 1 to segment tree from range 0 to Y
Add point to 2 treesets (index # flowers + 1), creating them if necessary

Answer: val[N-1]

Runtime: O(N * log(N))
*/

import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class mowingsmart2 {
    int N, T;
    long[] val;
    Point[] flowers;
    HashMap<Integer, Integer> xti, yti;
    final long INF = 1_000_000_000_000_000L;

    mowingsmart2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("mowing.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        flowers = new Point[N+2];
        flowers[0] = new Point(0, 0, -1);
        int x, y;
        for (int i = 1; i < N+1; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            flowers[i] = new Point(x, y, -1);
        }
        flowers[N+1] = new Point(T, T, -1);
        fin.close();

        N += 2;

        // Generate xToIndex and yToIndex
        yti = new HashMap<>(N+3, 1);
        Arrays.sort(flowers, Comparator.comparingInt(a -> a.y));
        for (int i = 0; i < N; i++) {
            yti.put(flowers[i].y, i);
        }

        xti = new HashMap<>(N+3, 1);
        Arrays.sort(flowers, Comparator.comparingInt(a -> a.x));
        for (int i = 0; i < N; i++) {
            xti.put(flowers[i].x, i);
        }

        long answer = sweepFlowers();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mowing.out")));
        fout.println(answer);
        fout.close();
    }

    long sweepFlowers() {
        // N is total number of points, including (0, 0) and (T, T)
        SegmentTree stNumFlowers = new SegmentTree(N+2);
        val = new long[N];
        for (int i = 0; i < N; i++) val[i] = INF;
        val[0] = 0;
        ArrayList<Integer>[] points = new ArrayList[N];

        // Treat (0, 0) as a base case
        points[0] = new ArrayList<>(2);
        points[0].add(0);

        Point curr, flower;
        for (int i = 1; i < N; i++) {
            curr = flowers[i];
            // System.out.println(curr.x + ", " + curr.y);
            // Query to determine correct # of flowers
            int numFlowers = stNumFlowers.query(0, yti.get(curr.y));
            // System.out.println(numFlowers);
            // Query ArrayList to find the right flowers
            for (int p : points[numFlowers]) {
                flower = flowers[p];
                if (flower.y > curr.y) continue;
                val[i] = Math.min(val[p] + (curr.x - flowers[p].x) * (curr.y - flowers[p].y), val[i]);
            }
            // Add new numFlowers to segment tree
            stNumFlowers.update(yti.get(curr.y), numFlowers + 1);
            // Add point to ArrayList
            if (points[numFlowers+1] == null) {
                points[numFlowers+1] = new ArrayList<>(2);
            }
            points[numFlowers+1].add(i);
        }

        // System.out.println(Arrays.toString(val));
        return val[N-1];
    }

    public static void main(String[] args) throws IOException {
        new mowingsmart2();
    }

    static class SegmentTree {
        int size;
        int[] lb, rb;
        int[] vals;

        SegmentTree(int size) {
            this.size = size;
            this.lb = new int[size * 4 + 1];
            this.rb = new int[size * 4 + 1];
            this.vals = new int[size * 4 + 1];
            initTree(0, size - 1, 1);
            /*
            System.out.println(Arrays.toString(lb));
            System.out.println(Arrays.toString(rb));
            System.out.println(Arrays.toString(vals));
             */
        }

        /*
        Updates (sets) an index to a new value. Only updates the value if it has a higher value.
         */
        void update(int i, int v) {
            recUpdate(1, i, v);
        }

        void recUpdate(int node, int i, int v) {
            if (lb[node] > i || rb[node] < i) {
            }
            else if (lb[node] == i && rb[node] == i) {
                // Found node
                vals[node] = Math.max(v, vals[node]);
            } else {
                // Recurse on two lower nodes, and update this node too
                recUpdate(node * 2, i, v);
                recUpdate(node * 2 + 1, i, v);
                vals[node] = Math.max(v, vals[node]);
            }
        }

        /*
        Queries a range from min to max.
         */
        int query(int min, int max) {
            return recQuery(1, min, max);
        }

        int recQuery(int node, int min, int max) {
            // System.out.println("node = " + node + ", min = " + min + ", max = " + max);
            // System.out.println("lb " + lb[node] + " rb " + rb[node]);
            if (lb[node] > max || rb[node] < min) return -1;
            else if (lb[node] >= min && rb[node] <= max) {
                // Node completely inside range of query; return it's value
                return vals[node];
            } else {
                // Recurse on two lower nodes, and return highest answer
                return Math.max(recQuery(node * 2, min, max), recQuery(node * 2 + 1, min, max));
            }
        }

        /*
        Initializes the tree by setting lb (left bound) and rb (right bound) for all nodes.
         */
        void initTree(int left, int right, int node) {
            // System.out.println("left = " + left + ", right = " + right + ", node = " + node);
            lb[node] = left;
            rb[node] = right;
            if (left == right) return;
            initTree(left, (left + right) / 2, node * 2);
            initTree((left + right) / 2 + 1, right, node * 2 + 1);
        }
    }

    static class Point {
        int x, y, i;
        Point(int x, int y, int i) {
            this.x = x;
            this.y = y;
            this.i = i;
        }
    }
}
