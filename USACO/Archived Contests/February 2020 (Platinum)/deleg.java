/*
Solution: Binary search on K, and greedily push up the longest path at each node.
Runtime: O(N * log(N)^2)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class deleg {
    int N;
    ArrayList<Integer>[] adj;

    deleg(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        int low = 0, high = N - 1;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            // System.out.println("Check " + mid);
            if (check(mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }
        out.println(low);
    }

    int checkK;
    boolean valid;
    boolean check(int K) {
        checkK = K;
        valid = true;
        dfs(0, 0);
        return valid;
    }

    int dfs(int n, int p) {
        if (!valid) return 0;  // Break early

        int numChildPaths = 0;
        TreeMap<Integer, Integer> childPaths = new TreeMap<>();
        for (int e : adj[n]) {
            if (e != p) {
                add(childPaths, dfs(e, n));
                numChildPaths++;
                if (!valid) return 0;
            }
        }

        if (childPaths.size() == 0) {
            // Leaf node
            return 1;
        }
        // System.out.println(childPaths);

        // Pair the remaining paths until one or two remain
        int toExtend = -1;
        if (n == 0) toExtend = 9999999;
        while (numChildPaths > 2) {
            int currPath = childPaths.firstKey();
            remove(childPaths, currPath);
            numChildPaths--;
            // Pair with smallest path that can be paired
            Integer canPair = childPaths.ceilingKey(checkK - currPath);
            // System.out.println(currPath + " " + canPair);
            if (canPair == null) {
                // This one must be extended
                if (toExtend == -1) {
                    toExtend = currPath;
                } else {
                    // More than 1 path extended; not valid
                    valid = false;
                    return -1;
                }
            } else {
                remove(childPaths, canPair);
                numChildPaths--;
            }
        }

        if (numChildPaths == 2) {
            // Do these need to be paired?
            int lower = childPaths.firstKey();
            int higher = childPaths.lastKey();
            if (toExtend != -1) {
                // Yes, they must be paired
                if (lower + higher < checkK) {
                    // Not valid
                    valid = false;
                    return -1;
                } else {
                    // Paired!
                    return toExtend + 1;
                }
            } else {
                // They don't need to be paired...
                if (higher >= checkK) {
                    // Lower can be extended!
                    return lower + 1;
                } else if (lower + higher >= checkK) {
                    // Paired!
                    return 1;
                } else {
                    // Not valid
                    valid = false;
                    return -1;
                }
            }
        } else {
            // Can this be extended?
            if (toExtend == -1) return childPaths.firstKey() + 1;  // Yes
            else {
                // Can this be dropped?
                if (childPaths.firstKey() >= checkK) {
                    // Yes
                    return toExtend + 1;
                } else {
                    // Not valid
                    valid = false;
                    return -1;
                }
            }
        }
    }

    void add(TreeMap<Integer, Integer> map, int val) {
        map.put(val, map.getOrDefault(val, 0) + 1);
    }

    void remove(TreeMap<Integer, Integer> map, int val) {
        int get = map.get(val);
        if (get == 1) map.remove(val);
        else map.put(val, get-1);
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("deleg.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("deleg.out")));
        new deleg(in, out);
        in.close();
        out.close();
    }
}
