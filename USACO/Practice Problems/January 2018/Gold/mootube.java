/*
Solution: Union-find will work here. Start by putting the edge with the most relevance. When the next edge
to include has a smaller relevance than the next query (sorted in decreasing relevance order), answer the
query by taking the size of that node's set minus one.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class mootube {
    int N, Q;
    Edge[] edges;
    Question[] questions;
    UnionFind uf;

    mootube() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("mootube.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        uf = new UnionFind(N);
        edges = new Edge[N - 1];
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            edges[i] = new Edge(Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()) - 1, Integer.parseInt(st.nextToken()));
        }
        questions = new Question[Q];
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(fin.readLine());
            int a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
            questions[i] = new Question(b - 1, a, i);
        }
        fin.close();

        // Process edges and questions in the right order
        Arrays.sort(edges, Comparator.comparingInt(x -> -x.r));
        Arrays.sort(questions, Comparator.comparingInt(x -> -x.r));
        int[] answers = new int[Q];
        int currQ = 0, currE = 0;
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mootube.out")));
        while (currQ < Q) {
            // Add new edges while needed
            while (currE != N - 1 && questions[currQ].r <= edges[currE].r) {
                uf.union(edges[currE].a, edges[currE].b);
                currE++;
            }

            // Answer question
            answers[questions[currQ].origI] = uf.getSetSize(questions[currQ++].n) - 1;
        }

        Arrays.stream(answers).forEach(fout::println);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new mootube();
    }

    static class Edge {
        int a, b, r;
        Edge(int a, int b, int r) {
            this.a = a;
            this.b = b;
            this.r = r;
        }
    }

    static class Question {
        int n, r, origI;
        Question(int n, int r, int origI) {
            this.n = n;
            this.r = r;
            this.origI = origI;
        }
    }

    static class UnionFind {
        int size;
        int[] vals;

        UnionFind(int size) {
            this.size = size;
            vals = new int[size];
            Arrays.fill(vals, -1);
        }

        void union(int a, int b) {
            a = query(a);
            b = query(b);
            if (a == b) return;

            if (vals[a] < vals[b]) {
                vals[a] += vals[b];
                vals[b] = a;
            } else {
                vals[b] += vals[a];
                vals[a] = b;
            }
        }

        int query(int n) {
            if (vals[n] < 0) return n;
            vals[n] = query(vals[n]);
            return vals[n];
        }

        int getSetSize(int n) {
            return -vals[query(n)];
        }
    }
}
