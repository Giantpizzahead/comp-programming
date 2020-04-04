/*
Solution:
Each valley should store its maximum value (max needed to count as adding another valley). This could
just be done using an array.

Sort all values in increasing order. Iterate through the values, putting new values into
a disjoint set containing all the valleys. If a value connects to an existing valley, add it to
that valley in the set. If it connects to 2 or more valleys, merge them all in the disjoint set,
maxing the maximum value in each.
After each of these steps, if the current value is greater than or equal to the maximum value in the
valley, add the size of the valley to the current answer. Else, don't add anything to the answer.

To handle the holey case, when a new value joins a valley to itself at least 2 times (2 of itself in
top, right, bottom, and left), check if the following cases have occurred: (* = Valley, V = value location)
(These can be rotated all 4 directions)
**- **-
*V- *V-
--- **-
So basically, if two adjacent edgewise sides have valleys, but the diagonal one also has a valley, then
it doesn't count toward the holey case. This is to prevent checking for holes in a rectangle pattern.

If this case did not occur, do a BFS on all neighbors (including pointwise) to look for the hole. Only
BFS once for each open location. Do this by going in clockwise order when checking neighbors, and only
starting a new BFS once a valley has appeared, then dissappeared. To optimize this for small holes, do
all the BFSs needed at the same time, and stop once a hole has been found. Track whether or not the BFS
has reached the edge of the grid (stop if it has). Also track the maximum value the BFS finds.

If the BFS never reaches the end of the grid, that means a hole exists in that direction. Set the maximum
value in the current valley to be the max of the BFS.

(Theoretical) runtime: O(N^2 * log(N) [sorting] + ????? [BFS] + N^2 [iteration])
So I have no clue if this will work. Let's try it...
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class valleys {
    DisjointSet ds;
    Point[] points;
    int[] maxValueInSet, cx, cy;
    int[][] grid;
    boolean[][] inSet;
    int N;

    valleys() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowdate.in"));
        N = Integer.parseInt(fin.readLine());
        grid = new int[N][N];
        inSet = new boolean[N][N];
        points = new Point[N * N];
        for (int y = 0; y < N; y++) {
            StringTokenizer st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < N; x++) {
                grid[y][x] = Integer.parseInt(st.nextToken());
                points[y*N+x] = new Point(x, y, grid[y][x]);
            }
        }
        fin.close();

        // Sort points
        Arrays.sort(points, (a, b) -> { return a.v - b.v; });

        // Solve
        long answer = solve();
        PrintWriter fout = new PrintWriter("valleys.out");
        fout.println(answer);
        fout.close();
    }

    long solve() {
        // Make a disjoint set to store all the points
        ds = new DisjointSet(N * N);
        maxValueInSet = new int[N * N];
        long answer = 0;
        cx = new int[] {0, 1, 1, 1, 0, -1, -1, -1, 0, 1, 1, 1};
        cy = new int[] {-1, -1, 0, 1, 1, 1, 0, -1, -1, -1, 0, 1};
        int[] nbValleys = new int[5];
        int nx, ny;
        ArrayList<Point> toBFS = new ArrayList<>(2);
        for (Point p : points) {
            // System.out.printf("Adding point (%d, %d, %d)\n", p.x, p.y, p.v);

            // Check if point is next to any valleys (edgewise only)
            toBFS.clear();
            // Loop 1 extra to make BFS check easier to implement
            for (int i = 0; i < 5; i++) {
                nx = p.x + cx[i*2];
                ny = p.y + cy[i*2];
                if (inBounds(nx, ny) && inSet[ny][nx]) {
                    // Point is next to a valley
                    nbValleys[i] = queryCoords(nx, ny);
                    
                    // Check if previous valley was the same; if it was, check if BFS needs to be done
                    if (i != 0 && nbValleys[i-1] == nbValleys[i]) {
                        // Check diagonal to see if BFS needs to be done
                        nx = p.x + cx[i*2-1];
                        ny = p.y + cy[i*2-1];
                        if (inBounds(nx, ny) && queryCoords(nx, ny) != nbValleys[i]) {
                            // BFS must be done to check for a hole
                            // System.out.println("BFS corner");
                            toBFS.add(new Point(nx, ny, nbValleys[i]));
                        }
                        /*
                        // Add opposite corner too
                        nx = p.x + cx[i*2+3];
                        ny = p.y + cx[i*2+3];
                        if (inBounds(nx, ny) && queryCoords(nx, ny) != nbValleys[i]) {
                            // System.out.println("BFS corner");
                            toBFS.add(new Point(nx, ny, nbValleys[i]));
                        }
                         */
                    }
                } else {
                    nbValleys[i] = -1;
                }
            }
            
            // Check for BFS cases where only horizontal or diagonal line exists
            if (nbValleys[0] != -1 && nbValleys[0] == nbValleys[2]) {
                // Must BFS left and right sides
                // System.out.println("BFS left and right");
                if (!(nbValleys[1] == nbValleys[0]) && inBounds(p.x+1, p.y)) toBFS.add(new Point(p.x + 1, p.y, nbValleys[0]));
                if (!(nbValleys[3] == nbValleys[0]) && inBounds(p.x-1, p.y)) toBFS.add(new Point(p.x - 1, p.y, nbValleys[0]));
            }
            if (nbValleys[1] != -1 && nbValleys[1] == nbValleys[3]) {
                // Must BFS top and bottom sides
                // System.out.println("BFS top and bottom");
                if (!(nbValleys[0] == nbValleys[1]) && inBounds(p.x, p.y-1)) toBFS.add(new Point(p.x, p.y - 1, nbValleys[1]));
                if (!(nbValleys[2] == nbValleys[1]) && inBounds(p.x, p.y+1)) toBFS.add(new Point(p.x, p.y + 1, nbValleys[1]));
            }

            // Combine all the valleys (including the current point)
            int setWithPoint = coordsToInt(p.x, p.y);
            inSet[p.y][p.x] = true;

            // Combine point with neighbors
            for (int i = 0; i < 4; i++) {
                if (nbValleys[i] != -1) combineValleys(setWithPoint, nbValleys[i]);
            }

            // If BFSs are needed, do those / update maxValueInSet if needed
            setWithPoint = queryCoords(p.x, p.y);
            if (toBFS.size() > 0) {
                int maxValue = tryBFS(toBFS, setWithPoint);
                if (maxValue != -1) {
                    // BFS didn't reach edge, so there is a hole here; set max value accordingly
                    maxValueInSet[setWithPoint] = Math.max(maxValue, maxValueInSet[setWithPoint]);
                }
            }

            // Add to answer if needed
            if (maxValueInSet[setWithPoint] <= p.v) {
                // No holes currently; this is a valid valley
                answer += ds.getSize(setWithPoint);
                // System.out.println(ds.getSize(setWithPoint) + " added to answer");
            }
        }
        return answer;
    }

    /**
     * Returns the maximum value found during the BFS if it gets trapped by the given valley (hole).
     * Else, returns -1.
     */
    int tryBFS(ArrayList<Point> startPoints, int valley) {
        // Run all BFSs at once so you can stop once a hole has been found
        int numPoints = startPoints.size();
        boolean[] running = new boolean[numPoints];
        int[] maxSoFar = new int[numPoints];
        HashSet<Integer> visited = new HashSet<>();
        Queue<Point>[] queues = new LinkedList[numPoints];
        int x, y;
        for (int i = 0; i < numPoints; i++) {
            queues[i] = new LinkedList<>();
            x = startPoints.get(i).x;
            y = startPoints.get(i).y;
            queues[i].add(new Point(x, y, 0));
            visited.add(stateToInt(x, y, i));
            maxSoFar[i] = grid[y][x];
            running[i] = true;
        }

        Point curr;
        int nx, ny, cid = 0, numDone = 0;
        while (!queues[cid].isEmpty()) {
            curr = queues[cid].poll();
            x = curr.x;
            y = curr.y;
            maxSoFar[cid] = Math.max(grid[y][x], maxSoFar[cid]);

            // Loop through neighbors
            for (int i = 0; i < 8; i++) {
                nx = x + cx[i];
                ny = y + cy[i];
                if (!inBounds(nx, ny)) {
                    // Done with BFS; no hole
                    running[cid] = false;
                    numDone++;
                    if (numDone == numPoints) return -1;
                    break;
                } else if (!visited.contains(stateToInt(nx, ny, cid)) && (!inSet[ny][nx] || !(queryCoords(ny, nx) == valley))) {
                    // Add new location
                    queues[cid].add(new Point(nx, ny, 0));
                    visited.add(stateToInt(nx, ny, cid));
                }
            }

            // Switch to next queue
            do {
                cid = (cid + 1) % numPoints;
            } while (!running[cid]);
        }

        // Trapped; there is a hole here
        // System.out.println("Found hole, max value in it is " + maxSoFar);
        return maxSoFar[cid];
    }

    int stateToInt(int x, int y, int id) {
        return (x * N + y) + (N * N * id);
    }

    int combineValleys(int a, int b) {
        maxValueInSet[a] = Math.max(maxValueInSet[b], maxValueInSet[a]);
        maxValueInSet[b] = Math.max(maxValueInSet[a], maxValueInSet[b]);
        return ds.merge(a, b);
    }

    boolean inBounds(int x, int y) {
        return y >= 0 && y < N && x >= 0 && x < N;
    }

    int queryCoords(int x, int y) {
        return ds.query(coordsToInt(x, y));
    }

    int coordsToInt(int x, int y) {
        return x * N + y;
    }

    int getX(int hash) {
        return hash / N;
    }

    int getY(int hash) {
        return hash % N;
    }

    public static void main(String[] args) throws IOException {
        new valleys();
    }
    
    static class Point {
        int x, y, v;
        Point(int x, int y, int v) {
            this.x = x;
            this.y = y;
            this.v = v;
        }
    }

    static class DisjointSet {
        int[] v;
        int size;
        DisjointSet(int size) {
            this.size = size;
            v = new int[size];
            for (int i = 0; i < size; i++) {
                v[i] = -1;
            }
        }

        /**
         * Attempts to merge elements a and b. Returns the root of the newly merged set.
         */
        int merge(int a, int b) {
            // System.out.println("Merging " + a + " and " + b);
            // System.out.println("Before: " + Arrays.toString(v));
            int setA = query(a);
            int setB = query(b);
            if (setA == setB) return setA;

            // Merge the two sets into the one with the bigger set
            if (v[setA] > v[setB]) {
                // Set B is bigger; merge into that one
                v[setB] += v[setA];
                v[setA] = setB;
                // System.out.println("After: " + Arrays.toString(v));
                return setB;
            } else {
                // Set A is bigger (or they're equal); merge into that one
                v[setA] += v[setB];
                v[setB] = setA;
                // System.out.println("After: " + Arrays.toString(v));
                return setA;
            }
        }

        /**
         * Returns the root of the set that x is currently in.
         */
        int query(int x) {
            if (v[x] < 0) return x;
            else {
                int root = query(v[x]);
                // Condense the set
                v[x] = root;
                return root;
            }
        }

        /**
         * Gets the size of the set that x is currently in.
         */
        int getSize(int x) {
            return -v[query(x)];
        }
    }
}
