/*
Solution: A query can be thought of as a suffix of a prefix. So, sweep along the list of problems,
keeping an updated segment tree of the sums at each suffix of a prefix (do this by tracking when each
problem value was last seen, and only update the sum of all suffixes after that index). When reaching a
query, return the historic max value within the query range (to allow subsequences that don't end at
the query endpoint).

Runtime: O((N + Q) * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class GSS2 {
    int N, Q;
    int[] scores;
    long[] answers;
    ArrayList<Query>[] queries;

    GSS2(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        scores = new int[N];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) scores[i] = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(in.readLine());
        // queries[i] has all queries that end at i (b = i)
        queries = new ArrayList[N];
        for (int i = 0; i < N; i++) queries[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            queries[b].add(new Query(a, b, i));
        }
        in.close();

        // Keep a 'rolling' segment tree with all sums of suffixes, along with historic max
        final int OFFSET = 100000;
        SegmentTree seg = new SegmentTree(N);
        answers = new long[Q];
        int[] lastSeen = new int[200001];
        Arrays.fill(lastSeen, -1);
        for (int i = 0; i < N; i++) {
            // Update required sums
            seg.increment(lastSeen[scores[i] + OFFSET] + 1, i, scores[i]);
            lastSeen[scores[i] + OFFSET] = i;
            // Answer any new queries
            for (Query q : queries[i]) {
                answers[q.id] = seg.queryHistMax(q.a, q.b);
            }
        }

        Arrays.stream(answers).forEach(out::println);
        out.close();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new GSS2(in, out);
    }

    static class Query {
        int a, b, id;
        Query(int a, int b, int id) {
            this.a = a;
            this.b = b;
            this.id = id;
        }
    }

    static class SegmentTree {
        int size;
        long[] currMax, histMax, delta, histDelta;

        SegmentTree(int size) {
            this.size = size;
            currMax = new long[size * 4 + 1];
            histMax = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
            histDelta = new long[size * 4 + 1];
        }

        void increment(int l, int r, int v) {
            increment(1, 0, size - 1, l, r, v);
        }

        void increment(int n, int lb, int ub, int l, int r, int v) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                updateDelta(n, v);
                return;
            }

            propagate(n);
            increment(n*2, lb, (lb+ub)/2, l, r, v);
            increment(n*2+1, (lb+ub)/2+1, ub, l, r, v);
            updateFromChildren(n);
        }

        long queryHistMax(int l, int r) {
            return queryHistMax(1, 0, size - 1, l, r);
        }

        long queryHistMax(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return histMax[n];

            propagate(n);
            return Math.max(queryHistMax(n*2, lb, (lb+ub)/2, l, r), queryHistMax(n*2+1, (lb+ub)/2+1, ub, l, r));
        }

        void propagate(int n) {
            histMax[n * 2] = Math.max(currMax[n * 2] + histDelta[n], histMax[n * 2]);
            histMax[n * 2 + 1] = Math.max(currMax[n * 2 + 1] + histDelta[n], histMax[n * 2 + 1]);
            currMax[n * 2] += delta[n];
            currMax[n * 2 + 1] += delta[n];
            histDelta[n * 2] = Math.max(delta[n * 2] + histDelta[n], histDelta[n * 2]);
            histDelta[n * 2 + 1] = Math.max(delta[n * 2 + 1] + histDelta[n], histDelta[n * 2 + 1]);
            delta[n * 2] += delta[n];
            delta[n * 2 + 1] += delta[n];
            delta[n] = 0;
            histDelta[n] = 0;
        }

        void updateDelta(int n, int v) {
            currMax[n] += v;
            histMax[n] = Math.max(currMax[n], histMax[n]);
            delta[n] += v;
            histDelta[n] = Math.max(delta[n], histDelta[n]);
        }

        void updateFromChildren(int n) {
            currMax[n] = Math.max(currMax[n*2], currMax[n*2+1]);
            histMax[n] = Math.max(currMax[n], histMax[n]);
        }
    }
}
