/*
Solution: Once the final tree is cut down (tree N-1), the rest can be cut
for free. So, the real goal is to spend the minimum amount of energy
possible to cut down that last tree (if it so happens that every other
tree should be cut down first, that will be handled correctly as well). So,
dp[i] = Min energy needed to cut down ith tree. Transitions can be done
using the convex hull trick (increasing x, decreasing slope).
Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class logging {
    int N;
    int[] treeA, treeB;

    logging(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        treeA = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) treeA[i] = Integer.parseInt(st.nextToken());
        treeB = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) treeB[i] = Integer.parseInt(st.nextToken());

        long[] dp = new long[N];
        LineHolder lh = new LineHolder();
        lh.addLine(new Line(treeB[0], 0));
        for (int i = 1; i < N; i++) {
            dp[i] = lh.query(treeA[i]);
            Line nl = new Line(treeB[i], dp[i]);
            lh.addLine(nl);
        }
        out.println(dp[N-1]);
    }

    class LineHolder {
        Line[] lines;
        int front = 0, back = 0, size = 0;

        LineHolder() {
            lines = new Line[N];
        }

        // Assumes slopes are in decreasing order.
        void addLine(Line l) {
            // Remove unnecessary lines
            while (size > 1) {
                Line cf = lines[front - 1];
                Line nf = lines[front - 2];
                if (l.intersect(cf) <= cf.intersect(nf)) {
                    // Invariant broken
                    front--;
                    size--;
                } else break;
            }
            lines[front++] = l;
            size++;
        }

        // Assumes queries are in increasing order.
        long query(int x) {
            // Remove unnecessary lines
            while (size > 1) {
                Line cb = lines[back];
                Line nb = lines[back + 1];
                if (cb.intersect(nb) <= x) {
                    // Curr line is outdated
                    back++;
                    size--;
                } else break;
            }
            return lines[back].eval(x);
        }
    }

    static class Line {
        long m, b;
        Line(long m, long b) {
            this.m = m;
            this.b = b;
        }

        long eval(long x) {
            return m * x + b;
        }

        double intersect(Line o) {
            return (double) (o.b - b) / (m - o.m);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("logging.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("logging.out")));
        new logging(in, out);
        in.close();
        out.close();
    }
}