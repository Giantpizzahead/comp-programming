/*
Solution: First, find the maximum possible # of flowers before each flower that could be visited by Ella and Bella. Do
this using a segment tree sorted by compressed y coordinate. (# of flowers will be called level below) O(N * log(N))

Then, do a divide-and-conquer DP, based on the fact that if you iterate through the flowers in [i] from left to
right, then the optimal flower to come from will never go from a flower [i-1][j] to [i-1][j+1]. Go through each level
separately. O(N * log(N))

Runtime: O(N * log(N))
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;

public class mowing2 {
    int N, T;
    int[] validFlowersS, validFlowersE;
    ArrayList<ArrayList<Point>> flowers;
    Point[] xFlowers, yFlowers;
    final long INF = 1_000_000_000_000_000L;

    mowing2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("mowing.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        xFlowers = new Point[T + 1];
        yFlowers = new Point[T + 1];
        int x, y;
        Point flower;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            flower = new Point(x, y);
            xFlowers[flower.x] = flower;
            yFlowers[flower.y] = flower;
        }
        fin.close();
        flower = new Point(0, 0);
        flower.c = 0;
        xFlowers[0] = flower;
        yFlowers[0] = flower;
        flower = new Point(T, T);
        xFlowers[T] = flower;
        yFlowers[T] = flower;
        N = N + 2;

        // Find max # of flowers before each flower
        findNumBefore();
        // System.out.println(flowers);

        // Do divide-and-conquer DP
        for (int i = 1; i < flowers.size(); i++) {
            // Figure out valid range of valid flowers for each in the current level
            findValidRanges(i);
            /*
            System.out.println("Conquering " + i);
            System.out.println(Arrays.toString(validFlowersS));
            System.out.println(Arrays.toString(validFlowersE));
             */
            divideAndConquer(i, i, 0, flowers.get(i).size() - 1, 0, flowers.get(i - 1).size() - 1);
        }

        // System.out.println(flowers);
        long answer = xFlowers[T].c;
        PrintWriter fout = new PrintWriter("mowing.out");
        fout.println(answer);
        fout.close();
    }

    void findValidRanges(int i) {
        int numCurrFlowers = flowers.get(i).size();
        int numPrevFlowers = flowers.get(i - 1).size();
        validFlowersS = new int[numCurrFlowers];
        validFlowersE = new int[numCurrFlowers];

        // Use a pointer approach to find valid ranges
        int backValid = 0;
        int frontValid = 0;
        Point curr;
        for (int j = 0; j < numCurrFlowers; j++) {
            curr = flowers.get(i).get(j);

            // Remove from back pointer
            while (flowers.get(i - 1).get(backValid).y > curr.y) {
                backValid++;
            }

            // Add to front pointer
            while (frontValid != numPrevFlowers - 1 && flowers.get(i - 1).get(frontValid + 1).x < curr.x) {
                frontValid++;
            }

            // Record range
            validFlowersS[j] = backValid;
            validFlowersE[j] = frontValid;
        }
    }

    void divideAndConquer(int i, int prevMid, int start, int end, int min, int max) {
        if (start > end) return;
        int mid = (start + end) / 2;
        int bestLoc = -1;
        long bestCost = INF;

        // Adjust range to only valid flowers
        min = Math.max(validFlowersS[mid], min);
        max = Math.min(validFlowersE[mid], max);

        // Make range bigger if new valid points have been found that might affect the best cost
        if (prevMid > mid) {
            // Range is 0 size, and this point is to the left of the previous one; set min to right value
            min = validFlowersS[mid];
        } else if (prevMid < mid) {
            // Range is 0 size, and this point is to the right of the previous one; set max to right value
            max = validFlowersE[mid];
        }
        // System.out.println("i = " + i + ", start = " + start + ", end = " + end + ", min = " + min + ", max = " + max);

        Point curr = flowers.get(i).get(mid), other;
        for (int j = min; j <= max; j++) {
            other = flowers.get(i - 1).get(j);
            // Test this flower
            long newCost = other.c + calcCost(other, curr);
            if (newCost < bestCost) {
                bestLoc = j;
                bestCost = newCost;
            }
        }

        // Divide and conquer! :)
        curr.c = bestCost;
        divideAndConquer(i, mid, start, mid - 1, bestLoc, max);
        divideAndConquer(i, mid, mid + 1, end, min, bestLoc);
    }

    long calcCost(Point a, Point b) {
        return (long) (b.x - a.x) * (b.y - a.y);
    }

    void findNumBefore() {
        // Do y coordinate compression
        HashMap<Integer, Integer> yToIndex = new HashMap<>(N);
        int i = 0;
        for (int y = 0; y < T + 1; y++) {
            if (yFlowers[y] != null) yToIndex.put(y, i++);
        }

        // Run sweep
        flowers = new ArrayList<>(1);
        SegmentTree flowersUnder = new SegmentTree(N);
        int maxNumUnder = -1;
        Point f;
        for (int x = 0; x < T + 1; x++) {
            if (xFlowers[x] == null) continue;
            f = xFlowers[x];
            int currUnder = flowersUnder.query(0, yToIndex.get(f.y));
            if (currUnder > maxNumUnder) {
                // Make new arraylist
                maxNumUnder = currUnder;
                flowers.add(new ArrayList<>(1));
            }
            flowers.get(currUnder).add(f);
            flowersUnder.update(yToIndex.get(f.y), flowersUnder.size - 1, currUnder + 1);
        }
    }

    public static void main(String[] args) throws IOException {
        new mowing2();
    }

    class SegmentTree {
        int size;
        int[] lb, ub, vals, delta;
        int MAX_SIZE;
        // Value returned when query node is out of range; set this to the appropriate value for the calcValue() function
        final int NULL_VAL = -1000000007;

        SegmentTree(int size) {
            MAX_SIZE = size * 4 + 1;
            this.size = size;
            lb = new int[MAX_SIZE];
            ub = new int[MAX_SIZE];
            vals = new int[MAX_SIZE];
            delta = new int[MAX_SIZE];
            initTree(1, 0, size - 1);
        }

        /**
         * Modify this function to change the operation that the segment tree does. Make sure that the operation is
         * segment tree friendly / works with lazy propagation!
         */
        int calcValue(int a, int b) {
            return Math.max(a, b);
        }

        void update(int low, int high, int value) {
            update(1, low, high, value);
        }

        void update(int node, int low, int high, int value) {
            if (lb[node] > high || ub[node] < low) return;  // Node not in update range
            else if (lb[node] >= low && ub[node] <= high) {
                // This node is covered in entire update range; no need to go down further
                delta[node] = calcValue(value, delta[node]);
                return;
            }

            // Partially covered; recursively update lower nodes
            vals[node] = calcValue(value, vals[node]);
            update(node * 2, low, high, value);
            update(node * 2 + 1, low, high, value);
        }

        int query(int index) {
            return query(1, index, index);
        }

        int query(int low, int high) {
            return query(1, low, high);
        }

        int query(int node, int low, int high) {
            // Propagate changes
            if (lb[node] != ub[node]) {
                delta[node * 2] = calcValue(delta[node], delta[node * 2]);
                delta[node * 2 + 1] = calcValue(delta[node], delta[node * 2 + 1]);
            }
            vals[node] = calcValue(delta[node], vals[node]);
            delta[node] = 0;

            if (lb[node] > high || ub[node] < low) return NULL_VAL;  // Node not in update range
            else if (lb[node] >= low && ub[node] <= high) {
                // This node is covered in entire update range; no need to go down further
                return vals[node];
            }

            // Partially covered; Recursively query lower nodes
            return calcValue(query(node * 2, low, high), query(node * 2 + 1, low, high));
        }

        void initTree(int node, int low, int high) {
            lb[node] = low;
            ub[node] = high;
            if (low != high) {
                // Recursively init lower nodes
                initTree(node * 2, low, (low + high) / 2);
                initTree(node * 2 + 1, (low + high) / 2 + 1, high);
            }
        }
    }

    class Point {
        int x, y;
        long c;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public String toString() {
            return "(" + x + ", " + y + ", " + c + ")";
        }
    }
}