/*
Solution: Doing the obvious N^2 solution because time issues.
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class falling {
    int N;
    int[] initY, target;
    final long INF = 98765432123456789L;

    falling(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        initY = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) initY[i] = Integer.parseInt(st.nextToken());
        target = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) target[i] = Integer.parseInt(st.nextToken()) - 1;

        // For every cow, try using every other world as a 'proxy'
        Fraction[] answers = new Fraction[N];
        for (int i = 0; i < N; i++) {
            Fraction best = new Fraction(INF, 1);
            int goal = target[i];
            int bl, br;
            if (goal < i && initY[goal] < initY[i]) {
                bl = i;
                br = N;
            } else if (goal < i) {
                bl = 0;
                br = goal;
            } else if (initY[goal] < initY[i]) {
                bl = goal + 1;
                br = N;
            } else {
                bl = 0;
                br = i + 1;
            }
            for (int j = bl; j < br; j++) {
                if (goal == j) continue;
                // First, check if this can actually be used
                if (goal < i && initY[goal] < initY[i]) {
                    // Goal is to bottom-left of i; only need to check proxies to the right of i
                    if (initY[j] < initY[i]) continue;
                } else if (goal < i) {
                    // Goal is to top-left of i; only need to check proxies to the left of goal
                    if (initY[j] > initY[i]) continue;
                } else if (initY[goal] < initY[i]) {
                    // Goal is to bottom-right of i; only need to check proxies to right of goal
                    if (initY[j] < initY[i]) continue;
                } else {
                    // Goal is to top-right of i; only need to check proxies to left of i
                    if (initY[j] > initY[i]) continue;
                }

                // Calculate proxy time
                Fraction currTime = new Fraction(initY[j] - initY[goal], j - goal);
                if (currTime.val < 0) continue;
                if (currTime.val < best.val) {
                    // New best time
                    // System.out.println("best for " + i + " from " + j);
                    best = currTime;
                }
            }
            best.simplify();
            answers[i] = best;
        }

        for (Fraction f : answers) {
            if (f.a == INF) out.println(-1);
            else out.println(f);
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("falling.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("falling.out")));
        new falling(in, out);
        in.close();
        out.close();
    }

    class Fraction {
        long a, b;
        double val;
        Fraction(long a, long b) {
            this.a = a;
            this.b = b;
            val = (double) a / b;
        }

        void simplify() {
            if (a < 0 && b < 0) {
                // Both negative
                a *= -1;
                b *= -1;
            }
            long gcf = findGCF(a, b);
            a /= gcf;
            b /= gcf;
        }

        long findGCF(long a, long b) {
            if (b == 0) return a;
            return findGCF(b, a % b);
        }

        public String toString() {
            return a + "/" + b;
        }
    }
}
