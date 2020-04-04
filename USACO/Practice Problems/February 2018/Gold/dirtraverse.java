/*
Solution: Store directories as a rooted tree. Track the # of files inside each node's subtree.
BFS from root to find total length of all relative paths from root directory. Then, do another
BFS from the root to try being in every single folder; the new cost is:
Orig cost + 3 * (# files in curr dir - # files in child dir) - (Name length) * (# files in child dir)
Using this, you can simulate everything in linear time.

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class dirtraverse {
    int N;
    long bestDist;
    int[] nameLength, numFiles, distFromRoot;
    boolean[] isFile;
    int[][] graph;

    dirtraverse() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("dirtraverse.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        graph = new int[N + 1][];
        nameLength = new int[N + 1];
        isFile = new boolean[N + 1];
        for (int i = 1; i < N + 1; i++) {
            st = new StringTokenizer(fin.readLine());
            nameLength[i] = st.nextToken().length();
            int numEdges = Integer.parseInt(st.nextToken());
            if (numEdges == 0) isFile[i] = true;
            else {
                nameLength[i]++;  // Account for slash
                graph[i] = new int[numEdges];
                for (int j = 0; j < numEdges; j++) graph[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        fin.close();

        // Find # of files in each folder
        numFiles = new int[N + 1];
        countFiles(1);

        // Do initial BFS to find relative path cost from root
        initialBFS();
        long initialCost = 0;
        for (int i = 1; i < N + 1; i++) {
            if (isFile[i]) initialCost += distFromRoot[i];
        }
        bestDist = initialCost;
        // System.out.println(Arrays.toString(distFromRoot));

        // Try every folder using a DFS (easier to implement)
        tryFolder(1, initialCost);

        PrintWriter fout = new PrintWriter("dirtraverse.out");
        fout.println(bestDist);
        fout.close();
    }

    void tryFolder(int node, long cost) {
        // System.out.println("node = " + node + ", cost = " + cost);
        bestDist = Math.min(cost, bestDist);
        for (int o : graph[node]) {
            if (isFile[o]) continue;
            // Try this child folder
            long newCost = cost + 3 * (numFiles[1] - numFiles[o]) - nameLength[o] * numFiles[o];
            tryFolder(o, newCost);
        }
    }

    void initialBFS() {
        Queue<Integer> q = new LinkedList<>();
        q.add(1);
        distFromRoot = new int[N + 1];

        while (!q.isEmpty()) {
            int c = q.poll();
            for (int o : graph[c]) {
                distFromRoot[o] = distFromRoot[c] + nameLength[o];
                if (!isFile[o]) q.add(o);
            }
        }
    }

    int countFiles(int node) {
        if (isFile[node]) return 1;
        int files = 0;
        for (int other : graph[node]) {
            files += countFiles(other);
        }
        numFiles[node] = files;
        return files;
    }

    public static void main(String[] args) throws IOException {
        new dirtraverse();
    }
}
