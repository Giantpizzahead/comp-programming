import java.util.*;
import java.io.*;

public class grass {
    final int INF = 1000000007;
    int N, M, K, Q;
    int[] initialType;
    Edge[] edges;
    UpdateList[] updates;
    SegmentTree answers;

    grass(BufferedReader fin, PrintWriter fout) throws IOException {
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        edges = new Edge[M];
        int a, b, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            edges[i] = new Edge(a, b, c);
        }
        initialType = new int[N];
        st = new StringTokenizer(fin.readLine());
        for (int i = 0; i < N; i++) initialType[i] = Integer.parseInt(st.nextToken()) - 1;
        updates = new UpdateList[N];
        for (int i = 0; i < N; i++) updates[i] = new UpdateList();

        int n, t;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(fin.readLine());
            n = Integer.parseInt(st.nextToken()) - 1;
            t = Integer.parseInt(st.nextToken()) - 1;
            updates[n].addUpdate(new Update(i, n, t));
        }

        // Easier implementation
        for (int i = 0; i < N; i++) updates[i].addUpdate(new Update(INF, i, -1));

        Arrays.sort(edges, new Comparator<Edge>() {
            @Override
            public int compare(Edge o1, Edge o2) {
                return o1.c - o2.c;
            }
        });

        answers = new SegmentTree(Q);
        for (Edge e : edges) {
            fillAnswers(e);
        }

        for (int i = 0; i < Q; i++) {
            fout.println(answers.queryMin(i));
        }
    }

    void fillAnswers(Edge e) {
        // System.out.println(e.a + " " + e.b + " " + e.c);
        int n1 = e.a, n2 = e.b;
        int prevGrass1 = -1, currGrass1 = initialType[n1];
        int prevGrass2 = -1, currGrass2 = initialType[n2];
        boolean isDifferent = currGrass1 != currGrass2;
        int diffStartTime = isDifferent ? 0 : INF;
        Update u1 = updates[n1].first, u2 = updates[n2].first;
        while (u1.time != INF || u2.time != INF) {
            if (u1.time < u2.time) {
                // Evaluate u1 first
                prevGrass1 = currGrass1;
                currGrass1 = u1.grass;
                if (prevGrass1 == currGrass1) {
                    // This update is useless
                    updates[n1].delete(u1);
                } else if (u1.grass != u1.next.grass && !answers.queryInf(u1.time, u1.next.time - 1)) {
                    // Useless update (next one overrules this one)
                    updates[n1].delete(u1);
                }

                if (currGrass1 == currGrass2) {
                    // Grass types are now the same
                    if (isDifferent) {
                        isDifferent = false;
                        answers.min(diffStartTime, u1.time - 1, e.c);
                        diffStartTime = INF;
                    }
                } else if (!isDifferent) {
                    // Grass types changed from same to different
                    isDifferent = true;
                    diffStartTime = u1.time;
                } else {
                    // Types are still different
                }
                u1 = u1.next;
            } else {
                // Evaluate u2 first
                prevGrass2 = currGrass2;
                currGrass2 = u2.grass;
                if (prevGrass2 == currGrass2) {
                    // This update is useless
                    updates[n2].delete(u2);
                } else if (u2.grass != u2.next.grass && !answers.queryInf(u2.time, u2.next.time - 1)) {
                    // Useless update (again)
                    updates[n2].delete(u2);
                }

                if (currGrass1 == currGrass2) {
                    // Grass types are now the same
                    if (isDifferent) {
                        isDifferent = false;
                        answers.min(diffStartTime, u2.time - 1, e.c);
                        diffStartTime = INF;
                    }
                } else if (!isDifferent) {
                    // Grass types changed from same to different
                    isDifferent = true;
                    diffStartTime = u2.time;
                } else {
                    // Still different
                }
                u2 = u2.next;
            }
            // System.out.println(currGrass1 + " " + currGrass2);
        }
        if (isDifferent) {
            // Off-by-one
            answers.min(diffStartTime, Q-1, e.c);
        }
    }

    class SegmentTree {
        final int INF = 1000000007;
        int size;
        int[] min, delta;
        boolean[] hasInf;

        SegmentTree(int size) {
            this.size = size;
            min = new int[size * 4 + 1];
            hasInf = new boolean[size * 4 + 1];
            delta = new int[size * 4 + 1];
            Arrays.fill(min, INF);
            Arrays.fill(hasInf, true);
            Arrays.fill(delta, INF);
        }

        void min(int l, int r, int v) {
            if (l > r) return;
            min(1, 0, size - 1, l, r, v);
        }

        void min(int n, int lb, int ub, int l, int r, int v) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                min[n] = Math.min(v, min[n]);
                hasInf[n] = false;
                delta[n] = Math.min(v, delta[n]);
                return;
            }
            propagate(n);
            min(n*2, lb, (lb+ub)/2, l, r, v);
            min(n*2+1, (lb+ub)/2+1, ub, l, r, v);
            min[n] = Math.min(min[n*2], min[n*2+1]);
            hasInf[n] = hasInf[n*2] || hasInf[n*2+1];
        }

        int queryMin(int i) {
            // System.out.println("i = " + i);
            return queryMin(1, 0, size - 1, i);
        }

        int queryMin(int n, int lb, int ub, int i) {
            if (lb == ub) return min[n];
            propagate(n);
            if (i > (lb+ub)/2) return queryMin(n*2+1, (lb+ub)/2+1, ub, i);
            else return queryMin(n*2, lb, (lb+ub)/2, i);
        }

        public boolean queryInf(int l, int r) {
            if (l > r) return false;
            return queryInf(1, 0, size - 1, l, r);
        }

        boolean queryInf(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return false;
            else if (lb >= l && ub <= r) return hasInf[n];
            propagate(n);
            return queryInf(n*2, lb, (lb+ub)/2, l, r) || queryInf(n*2+1, (lb+ub)/2+1, ub, l, r);
        }

        void propagate(int n) {
            if (delta[n] != INF) {
                min[n*2] = Math.min(delta[n], min[n*2]);
                min[n*2+1] = Math.min(delta[n], min[n*2+1]);
                hasInf[n*2] = false;
                hasInf[n*2+1] = false;
                delta[n*2] = Math.min(delta[n], delta[n*2]);
                delta[n*2+1] = Math.min(delta[n], delta[n*2+1]);
                delta[n] = INF;
            }
        }
    }

    class Edge {
        int a, b, c;
        Edge(int a, int b, int c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }

    class Update {
        int time, node, grass;
        Update prev, next;

        Update(int t, int n, int g) {
            time = t;
            node = n;
            grass = g;
        }
    }

    class UpdateList {
        Update first, last;

        void addUpdate(Update update) {
            if (first == null) {
                first = update;
                last = update;
            } else {
                last.next = update;
                last = update;
            }
        }

        void delete(Update update) {
            if (update.prev == null) {
                // First node
                first = update.next;
                update.next.prev = null;
            } else {
                // Middle node
                update.prev.next = update.next;
                update.next.prev = update.prev;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("grass.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("grass.out")));
        new grass(fin, fout);
        fin.close();
        fout.close();
    }
}
