/*
Solution: Get rid of unnecessary rectangles, then do DP with a monotonic-like queue thing.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class acquire {
    int N;
    Plot[] plots;
    final long INF = 98765432123456789L;

    acquire() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        plots = new Plot[N];
        int w, l;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            w = Integer.parseInt(st.nextToken());
            l = Integer.parseInt(st.nextToken());
            plots[i] = new Plot(w, l);
        }
        in.close();

        // Sort plots in order of decreasing width, breaking ties by decreasing length
        Arrays.sort(plots, (a, b) -> {
            if (a.w == b.w) return b.l - a.l;
            else return b.w - a.w;
        });

        // Remove unnecessary plots
        ArrayList<Plot> newPlots = new ArrayList<>(N);
        int maxLength = 0;
        for (Plot p : plots) {
            if (p.l > maxLength) {
                newPlots.add(p);
                maxLength = p.l;
            }
        }
        plots = newPlots.toArray(new Plot[0]);
        N = plots.length;

        // System.out.println(Arrays.toString(plots));
        long answer = doDP();
        System.out.println(answer);
    }

    long doDP() {
        long[] dp = new long[N];
        // Custom queue
        Line[] trans = new Line[N+1];
        int backi = 0, fronti = 0, queueSize = 1;
        trans[fronti++] = new Line(plots[0].w, 0);
        for (int i = 0; i < N; i++) {
            int x = plots[i].l;
            // Remove outdated transitions (query)
            while (queueSize >= 2 && trans[backi].calc(x) >= trans[backi+1].calc(x)) {
                // First trans is outdated
                backi++;
                queueSize--;
            }

            // Use this transition
            // System.out.println("For " + x + ": " + trans[backi]);
            dp[i] = trans[backi].calc(x);

            // Add new transition
            if (i == N - 1) continue;
            Line newL = new Line(plots[i+1].w, dp[i]);
            // Remove outdated transitions (insert)
            while (queueSize >= 2) {
                // l1 has least slope
                Line l1 = trans[fronti-1], l2 = trans[fronti-2];
                if (l1.intersectX(newL) < l2.intersectX(l1)) {
                    // l1 is outdated
                    // System.out.println("delete");
                    fronti--;
                    queueSize--;
                } else break;
            }
            // System.out.println("New trans " + newL);
            trans[fronti++] = newL;
            queueSize++;
        }
        // System.out.println(Arrays.toString(dp));
        return dp[N-1];
    }

    public static void main(String[] args) throws IOException {
        new acquire();
    }

    static class Plot {
        int w, l;
        Plot(int w, int l) {
            this.w = w;
            this.l = l;
        }

        public String toString() {
            return "(" + w + ", " + l + ")";
        }
    }

    static class Line {
        long m, b;
        Line(long m, long b) {
            this.m = m;
            this.b = b;
        }

        long calc(int x) {
            return m * x + b;
        }

        /**
         * Returns ceil(x value of intersection point between this line and line o).
         * In other words, returns the first x at which this line and the other line switch
         * positions.
         */
        long intersectX(Line o) {
            // double x = (double) (o.b - b) / (m - o.m);
            // System.out.println(x);
            // return (long) Math.ceil(x);
            return (o.b - b) / (m - o.m) + 1;
        }

        public String toString() {
            return "(" + m + "x + " + b + ")";
        }
    }
}
