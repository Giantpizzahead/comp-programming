/*
Solution A: First of all, figure out what numbers make a city beautiful, and
what numbers make a city ugly. All odd numbers that are not perfect squares
are ugly, so mark those accordingly in a 1.5*10^6 size array. Then, iterate
through that array, marking i*2 as the same ugly or not ugly result as i,
since adding a factor of 2 won't change the ugly result. Finally, set the
actual city beauty values on the nodes of the tree.

Runtime A: O(3*10^6) = 3,000,000 (OK)

Solution B: Now, solve the actual problem using centroid decomposition. To
solve for all paths including / going through the centroid node, keep a
prefix subtree sum array containing the sum of lengths of all paths with a
certain # of beautiful cities. This array should contain
arr[(centroid's beauty)] = 1 by default. Now, DFS through each subtree,
tracking the sum of lengths of all paths with a certain # of beautiful
cities completely within that subtree (not including centroid!). Store this
is a size 2M array with an offset to avoid log(M) factor. Then, iterate
through the prefix array and the new subtree array, adding (sum lengths
with K beauty in curr subtree) * (sum lengths with >= -K beauty in prefix
subtrees) to the answer. Finally, update the prefix array, making sure to
include the centroid when updating (old beauty value + beauty of centroid,
old length + 1). (Note: M is the max depth of the subtree, can be precomped)

Runtime B: O(3N * log(N)) = ~20,000,000 (OK)
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

@SuppressWarnings("unchecked")
class TESTERS {
    int N;
    int[] beauty;
    ArrayList<Integer>[] graph;

    // For Part A
    int[] cityNums;
    final int MAX_NUM = 1500000;

    // For Part B
    int offset;
    boolean[] blocked;
    int[] parent, subtreeSize;
    ArrayDeque<Path> currST;

    TESTERS() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        cityNums = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            cityNums[i] = Integer.parseInt(st.nextToken());
        }
        in.close();

        // Part A: Find out which cities are beautiful
        findBeautifulCities();
        // System.out.println(Arrays.toString(isBeautiful));

        // Part B: Do centroid decomposition
        offset = N;
        blocked = new boolean[N];
        subtreeSize = new int[N];
        parent = new int[N];
//        for (int i = 0; i < N; i++) {
//            findCentroid(i);
//            System.out.println("solveTree(" + (i + 1) + ") = " + solveTree(i));
//        }
        findCentroid(0);
        long answer = divideAndConquer(0);
        System.out.println(answer);
    }

    // Part A
    void findBeautifulCities() {
        boolean[] allBeautiful = new boolean[MAX_NUM + 1];
        // All odd numbers that are perfect squares are beautiful, rest ugly
        for (int i = 1; i*i <= MAX_NUM; i += 2) {
            allBeautiful[i*i] = true;
        }

        // Calculate the rest based off of the previous beauty values
        for (int i = 1; i*2 <= MAX_NUM; i++) {
            allBeautiful[i*2] = allBeautiful[i];
        }

        // Set city beauty values
        beauty = new int[N];
        for (int i = 0; i < N; i++) beauty[i] = allBeautiful[cityNums[i]] ? 1 : -1;
    }

    // Part B
    long solveTree(int n) {
        BIT prefixST = new BIT(subtreeSize[n] * 2 + 1);
        int currOffset = subtreeSize[n] + 1;
        // Base case
        prefixST.add(currOffset + beauty[n], 1);

        // Iterate through all subtrees
        long answer = (beauty[n] == 1) ? 1 : 0;
        for (int e : graph[n]) {
            if (blocked[e]) continue;

            // Fill curr subtree queue
            currST = new ArrayDeque<>(subtreeSize[e]);
            dfsSubtree(e, n, 1, beauty[e]);
            // Add to answer
            for (Path p : currST) {
                // System.out.println(p.b + " " + p.l);
                Result query = prefixST.queryCountGE(currOffset - p.b);
                answer += query.s + (query.c * p.l);
                // System.out.println(query.s + " " + query.c);
            }

            // Update prefix subtree BIT
            Path p;
            while (!currST.isEmpty()) {
                p = currST.poll();
                prefixST.add(currOffset + p.b + beauty[n], p.l + 1);
            }
        }

        return answer;
    }

    void dfsSubtree(int n, int p, int length, int beautySum) {
        currST.add(new Path(beautySum, length));
        for (int e : graph[n]) {
            if (e != p && !blocked[e]) {
                dfsSubtree(e, n, length + 1, beautySum + beauty[e]);
            }
        }
    }

    long divideAndConquer(int n) {
        n = findCentroid(n);
        // System.out.println("Centroid: " + (n + 1));
        long answer = solveTree(n);

        // Divide and conquer subtrees
        blocked[n] = true;
        for (int e : graph[n]) {
            if (blocked[e]) continue;
            answer += divideAndConquer(e);
        }

        return answer;
    }

    int findCentroid(int n) {
        findSubtreeSizes(n, n);

        // Find the best centroid
        int centroidI = n;
        int centroidMaxSize = subtreeSize[n];
        Queue<Integer> q = new LinkedList<>();
        q.add(n);
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            int currMaxSize = subtreeSize[n] - subtreeSize[c];
            for (int e : graph[c]) {
                if (parent[c] != e && !blocked[e]) {
                    currMaxSize = Math.max(subtreeSize[e], currMaxSize);
                    q.add(e);
                }
            }

            if (currMaxSize < centroidMaxSize) {
                // New best centroid found
                centroidI = c;
                centroidMaxSize = currMaxSize;
            }
        }

        return centroidI;
    }

    int findSubtreeSizes(int n, int p) {
        parent[n] = p;
        int currSubtreeSize = 1;
        for (int e : graph[n]) {
            if (e != p && !blocked[e]) {
                currSubtreeSize += findSubtreeSizes(e, n);
            }
        }
        subtreeSize[n] = currSubtreeSize;
        return currSubtreeSize;
    }

    public static void main(String[] args) throws IOException {
        new TESTERS();
    }

    class BIT {
        int size;
        long[] vals;
        int[] count;

        BIT(int size) {
            this.size = size;
            vals = new long[size + 1];
            count = new int[size + 1];
        }

        void add(int i, int v) {
            i = size - i + 1;
            while (i <= size) {
                vals[i] += v;
                count[i]++;
                i += Integer.lowestOneBit(i);
            }
        }

        Result queryCountGE(int i) {
            i = size - i + 1;
            long result = 0, numPaths = 0;
            while (i > 0) {
                result += vals[i];
                numPaths += count[i];
                i -= Integer.lowestOneBit(i);
            }
            return new Result(result, numPaths);
        }
    }

    class Result {
        long s, c;
        Result(long s, long c) {
            this.s = s;
            this.c = c;
        }
    }

    class Path {
        int b, l;
        Path(int b, int l) {
            this.b = b;
            this.l = l;
        }
    }
}