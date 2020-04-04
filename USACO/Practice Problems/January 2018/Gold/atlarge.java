/*
Solution: The answer at a specific node is either 1 if the time Bessie takes to get to the node >= the min height of
this node, or it's the sum of the farmers needed in each subtree.

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class atlarge {
    int N, K;
    ArrayList<Integer>[] graph;
    boolean[] visited;

    atlarge() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("atlarge.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken()) - 1;
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        fin.close();

        visited = new boolean[N];
        visited[K] = true;
        int answer = dfs(K, 0).farmers;
        PrintWriter fout = new PrintWriter("atlarge.out");
        fout.println(answer);
        fout.close();
    }

    Result dfs(int n, int bessieDist) {
        int farmers = 0, minHeight = 999999;
        boolean isLeaf = true;
        for (int e : graph[n]) {
            if (!visited[e]) {
                visited[e] = true;
                isLeaf = false;
                Result r = dfs(e, bessieDist + 1);
                farmers += r.farmers;
                minHeight = Math.min(r.minHeight + 1, minHeight);
            }
        }

        if (isLeaf) {
            return new Result(1, 0);
        } else {
            // If farmers can block Bessie at this node, return 1 farmer; else, return sum of subtrees
            if (minHeight <= bessieDist) return new Result(1, minHeight);
            else return new Result(farmers, minHeight);
        }
    }

    public static void main(String[] args) throws IOException {
        new atlarge();
    }

    class Result {
        int farmers, minHeight;
        Result(int farmers, int minHeight) {
            this.farmers = farmers;
            this.minHeight = minHeight;
        }
    }
}