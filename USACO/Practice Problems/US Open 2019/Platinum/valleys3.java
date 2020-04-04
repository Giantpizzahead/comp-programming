/*
Solution 2: To find the mountains that would cause holey valleys, you can
do a similar process of taking the highest values first, and forming
mountains using a disjoint set. Make sure to join all the pointwise-
contiguous mountains together. As soon as you take a value that links with
the edge of the grid, record that value in an ArrayList, along with the
maximum value in the mountain. Mark the newly linked mountain as an
"edge mountain". Do this until all values have been taken.

This will record the last value taken that will cause a holey valley, and
it will also record the last value taken that will cause the hole to be
filled. It will find all the holey valleys possible.

Runtime for part 1: O(N^2 * log(N) [sorting])

Then, take the lowest values first, generating the valleys using a disjoint set.
Keep in mind that for this one, only join the edgewise-contiguous valleys.
Whenever the new value taken equals the next value that will cause a holey
valley (genned in step 1), set the blockedUntil value for the current valley to
max(last value to fill hole, current value).

If blockedUntil > the value added, don't add to the answer. Else, add the size
of the current set to the answer.

Runtime for part 2: O(N^2)

Iterate through the points backwards in part 1 to avoid having to sort 2 times.
Store the holey valley trigger points in an ArrayList (will be sorted in reverse order).
Then, just track where your next trigger point is in the list with a pointer in part 2.
 */

import java.io.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;

public class valleys3 {
    int N;
    int[][] grid;
    Point[] points;
    ArrayList<Trigger> holeyTriggers;

    valleys3() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowdate.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new int[N][N];
        points = new Point[N*N];
        // Sort the points using an array for hopefully quicker runtime
        Point[] pointArr = new Point[1000001];
        for (int y = 0; y < N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 0; x < N; x++) {
                grid[y][x] = Integer.parseInt(st.nextToken());
                pointArr[grid[y][x]] = new Point(x, y, grid[y][x]);
            }
        }
        fin.close();

        // Sort points in order of increasing value
        int currI = 0;
        for (int i = 0; i < 1000001; i++) {
            if (pointArr[i] != null) {
                points[currI] = pointArr[i];
                currI++;
            }
        }

        // Sanity check
        // if (currI != N*N) grid[currI-99999999][0] = 0;

        // Part 1
        findMountains();

        System.out.println(holeyTriggers);

        // Part 2
        long answer = genValleys();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("valleys.out")));
        fout.println(answer);
        fout.close();
    }

    long genValleys() {
        DisjointSet ds = new DisjointSet(N*N);
        int[] setIsBlockedUntil = new int[N*N];
        int nextTriggerIndex = holeyTriggers.size() - 1;
        long answer = 0;

        // Iterate through points in increasing order
        int x, y, nx, ny, v;
        int[] neighbors = new int[4];
        int[] cx = new int[] {0, 1, 0, -1};
        int[] cy = new int[] {1, 0, -1, 0};
        for (Point c : points) {
            x = c.x;
            y = c.y;
            v = c.v;
            System.out.println("Point " + x + " " + y + " v " + v);

            // Get neighboring valleys (if there are any)
            for (int j = 0; j < 4; j++) {
                nx = x + cx[j];
                ny = y + cy[j];
                if (inBounds(nx, ny)) {
                    neighbors[j] = ds.query(nx, ny);
                } else {
                    neighbors[j] = -1;
                }
            }

            // Join all found valleys together
            // Update setIsBlockedUntil as needed
            int oldSet;
            int newSet = hashCoords(x, y);
            ds.enabled[newSet] = true;
            for (int neighbor : neighbors) {
                if (neighbor == -1) continue;
                oldSet = newSet;
                newSet = ds.merge(newSet, neighbor);
                setIsBlockedUntil[newSet] = Math.max(setIsBlockedUntil[neighbor], setIsBlockedUntil[oldSet]);
            }

            // If this is a trigger point, update setIsBlockedUntil
            if (nextTriggerIndex != -1 && v == holeyTriggers.get(nextTriggerIndex).triggerAt) {
                setIsBlockedUntil[newSet] = Math.max(holeyTriggers.get(nextTriggerIndex).newBlocked, setIsBlockedUntil[newSet]);
                nextTriggerIndex--;
            }

            // Add to answer if no holes exist currently
            if (v >= setIsBlockedUntil[newSet]) {
                answer += ds.getSize(newSet);
                System.out.println(ds.getSize(newSet) + " added to answer");
            }

            /*
            System.out.println(Arrays.toString(ds.vals));
            System.out.println(Arrays.toString(ds.enabled));
            System.out.println(answer);
             */
        }

        // Sanity check
        // if (nextTriggerIndex != -1) neighbors[nextTriggerIndex-9292929] = 0;

        return answer;
    }

    /*
    Modification: When joining mountains, if one is completely enclosed in another,
    then a trigger should be added with the inner mountain's maximum value.
     */
    void findMountains() {
        holeyTriggers = new ArrayList<>();
        DisjointSet ds = new DisjointSet(N*N);
        int[] maxValueInSet = new int[N*N];
        boolean[] setIsOnEdge = new boolean[N*N];

        // Iterate through points in decreasing order
        Point c;
        int x, y, nx, ny, v;
        boolean cWillJoinEdge;
        int[] neighbors = new int[8];
        int[] cx = new int[] {0, 1, 1, 1, 0, -1, -1, -1};
        int[] cy = new int[] {1, 1, 0, -1, -1, -1, 0, 1};
        for (int i = points.length - 1; i >= 0; i--) {
            c = points[i];
            x = c.x;
            y = c.y;
            v = c.v;
            cWillJoinEdge = false;

            // Get neighboring mountains (if there are any)
            for (int j = 0; j < 8; j++) {
                nx = x + cx[j];
                ny = y + cy[j];
                if (!inBounds(nx, ny)) {
                    // Not in bounds; this mountain will be joined to the edge
                    cWillJoinEdge = true;
                    neighbors[j] = -1;
                } else {
                    neighbors[j] = ds.query(nx, ny);
                    if (neighbors[j] != -1 && setIsOnEdge[neighbors[j]]) {
                        // Mountain is about to be joined to the edge
                        cWillJoinEdge = true;
                    }
                }
            }

            // If joined to the edge, make a new holey trigger if any of the other neighbors are already in a mountain
            // that isn't joined to the edge
            int maxBlocked = -1;
            HashSet<Integer> uniqueNeighbors = new HashSet<>();
            for (int neighbor : neighbors) {
                if (neighbor != -1 && !setIsOnEdge[neighbor]) {
                    // This neighbor is in a mountain that isn't joined to the edge; add its max value to the trigger
                    maxBlocked = Math.max(maxValueInSet[neighbor], maxBlocked);
                    uniqueNeighbors.add(neighbor);
                }
            }

            if (maxBlocked != -1 && (uniqueNeighbors.size() >= 2 || (cWillJoinEdge))) {
                // Trigger must be added here
                holeyTriggers.add(new Trigger(v, maxBlocked));
            }

            // Add point to current mountains, joining if necessary
            // Update setIsOnEdge and maxValueInSet as needed
            int oldSet;
            int newSet = hashCoords(x, y);
            setIsOnEdge[newSet] = cWillJoinEdge;
            maxValueInSet[newSet] = v;
            ds.enabled[newSet] = true;
            for (int neighbor : neighbors) {
                if (neighbor == -1) continue;
                oldSet = newSet;
                newSet = ds.merge(newSet, neighbor);
                if (setIsOnEdge[oldSet]) setIsOnEdge[newSet] = true;
                maxValueInSet[newSet] = Math.max(maxValueInSet[neighbor], maxValueInSet[oldSet]);
            }

            /*
            System.out.println("After point " + x + " " + y);
            System.out.println(Arrays.toString(ds.vals));
            System.out.println(Arrays.toString(ds.enabled));
             */
        }
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    int hashCoords(int x, int y) {
        return x * N + y;
    }

    public static void main(String[] args) throws IOException {
        new valleys3();
    }

    static class Trigger {
        int triggerAt, newBlocked;
        Trigger(int triggerAt, int newBlocked) {
            this.triggerAt = triggerAt;
            this.newBlocked = newBlocked;
        }

        @Override
        public String toString() {
            return "Trigger[" + triggerAt + ", " + newBlocked + "]";
        }
    }

    static class Point {
        int x, y, v;
        Point(int x, int y, int v) {
            this.x = x;
            this.y = y;
            this.v = v;
        }
    }

    class DisjointSet {
        int size;
        int[] vals;
        boolean[] enabled;
        DisjointSet(int size) {
            this.size = size;
            vals = new int[size];
            enabled = new boolean[size];
            for (int i = 0; i < size; i++) {
                vals[i] = -1;
            }
        }

        int query(int x, int y) {
            return query(hashCoords(x, y));
        }

        int query(int i) {
            if (vals[i] < 0) {
                // Check if enabled
                if (!enabled[i]) return -1;
                else return i;
            } else {
                int root = query(vals[i]);
                // Condense tree
                vals[i] = root;
                return root;
            }
        }

        int merge(int x1, int y1, int x2, int y2) {
            return merge(hashCoords(x1, y1), hashCoords(x2, y2));
        }

        /*
        Returns the root of the set that the two indexes were merged to.
         */
        int merge(int a, int b) {
            enabled[a] = true;
            enabled[b] = true;

            int aSet = query(a);
            int bSet = query(b);
            if (aSet == bSet) return aSet;

            // Merge to the set with more elements
            if (vals[aSet] < vals[bSet]) {
                // aSet has more
                vals[aSet] += vals[bSet];
                vals[bSet] = aSet;
                return aSet;
            } else {
                // bSet has equal or more
                vals[bSet] += vals[aSet];
                vals[aSet] = bSet;
                return bSet;
            }
        }

        int getSize(int i) {
            return -vals[query(i)];
        }
    }
}
