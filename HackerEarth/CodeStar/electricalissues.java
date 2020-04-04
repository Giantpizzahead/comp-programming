package CodeStar;/*
Solution: Not enough time. Basic solution.
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class electricalissues {
    int N, M, Q;
    int[] types;
    ArrayList<Integer>[] graph;

    electricalissues() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        types = new int[N];
        for (int i = 0; i < N; i++) {
            types[i] = Integer.parseInt(st.nextToken());
        }

        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) {
            graph[i] = new ArrayList<Integer>(1);
        }

        int a, b;
        for (int i = 0; i < N-1; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }

        Q = Integer.parseInt(in.readLine());
        int t;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            t = Integer.parseInt(st.nextToken());
            if (t == 1) {
                a = Integer.parseInt(st.nextToken()) - 1;
                bfs(a);
            } else {
                a = Integer.parseInt(st.nextToken()) - 1;
                // Changed
                types[a] = Integer.parseInt(st.nextToken());
            }
        }

        in.close();
    }

    void bfs(int n) {
        Queue<State> q = new LinkedList<>();
        q.add(new State(n, 0));
        int targetType = types[n];
        boolean[] visited = new boolean[N];
        visited[n] = true;

        State c;
        while (!q.isEmpty()) {
            c = q.poll();
            // Neighbors
            for (int i : graph[c.n]) {
                if (!visited[i]) {
                    // Check if diff type
                    if (types[i] != targetType) {
                        System.out.println(c.c + 1);
                        return;
                    } else {
                        q.add(new State(i, c.c + 1));
                        visited[i] = true;
                    }
                }
            }
        }

        // No result
        System.out.println(-1);
        return;
    }

    static class State {
        int n, c;
        State(int n, int c) {
            this.n = n;
            this.c = c;
        }
    }

    public static void main(String[] args) throws IOException {
        new electricalissues();
    }
}
