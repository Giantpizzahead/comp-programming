/*
ID: sunnyky1
LANG: JAVA
TASK: holstein

Solution: Solve with iterative deepening / backtracking.

Runtime: O(2 * 2^G * V)
*/

import java.util.*;
import java.io.*;

public class holstein {
    int V, G;
    int[] required, currVitamins;
    Integer[] solution;
    int[][] feedAmount;
    Stack<Integer> feedsUsed;

    holstein() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("holstein.in"));
        V = Integer.parseInt(fin.readLine());
        StringTokenizer st = new StringTokenizer(fin.readLine());
        required = new int[V];
        for (int i=0; i<V; i++) {
            required[i] = Integer.parseInt(st.nextToken());
        }

        G = Integer.parseInt(fin.readLine());
        feedAmount = new int[G][V];
        for (int i=0; i<G; i++) {
            st = new StringTokenizer(fin.readLine());
            for (int j=0; j<V; j++) {
                feedAmount[i][j] = Integer.parseInt(st.nextToken());
            }
        }
        fin.close();

        // Do iterative deepening
        currVitamins = new int[V];
        feedsUsed = new Stack<>();
        for (int numFeeds = 1; numFeeds <= G; numFeeds++) {
            dfs(new int[V], numFeeds);
            if (solution != null) break;
        }

        assert solution != null;
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("holstein.out")));
        StringBuilder sb = new StringBuilder();
        sb.append(solution.length).append(' ');
        for (int v : solution) sb.append(v+1).append(' ');
        fout.println(sb.substring(0, sb.length() - 1));
        fout.close();
    }

    void dfs(int[] vitaminCount, int numFeeds) {
        int lastFeedUsed = feedsUsed.isEmpty() ? -1 : feedsUsed.peek();
        for (int n = lastFeedUsed + 1; n < G; n++) {
            // Try using this feed
            for (int i = 0; i < V; i++) {
                vitaminCount[i] += feedAmount[n][i];
            }
            feedsUsed.add(n);
            numFeeds--;

            if (numFeeds == 0) {
                // Test this
                boolean valid = true;
                for (int i = 0; i < V; i++) {
                    if (vitaminCount[i] < required[i]) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    // Found solution
                    if (solution == null) solution = feedsUsed.toArray(new Integer[0]);
                    return;
                }
            } else {
                // Recurse
                dfs(vitaminCount, numFeeds);
            }

            // Backtrack
            feedsUsed.pop();
            numFeeds++;
            for (int i = 0; i < V; i++) {
                vitaminCount[i] -= feedAmount[n][i];
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new holstein();
    }
}