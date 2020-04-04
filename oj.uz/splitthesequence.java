/*
 * The order of the splits does not matter (figure this out by trying smaller cases).
 * Use some algebra to transform the cost into a more workable form.
 * ab + ac + bc = [(a + b + c)^2 - (a^2 + b^2 + c^2)] / 2
 * (a + b + c) remains constant, so the goal is to find the best way to split the array into pieces a, b, c such that
 * the sum of the squares is minimized. This can be done using dynamic programming, with a form of convex hull optimization.
 * Runtime: O(NK)
 */

import java.util.*;
import java.io.*;

public class splitthesequence {
    final long INF = 5876543212345678L;
    int N, K;
    int[] arr;
    int[][] from;
    ConvexHull hull;

    splitthesequence(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken()) + 1;
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        hull = new ConvexHull();
        from = new int[K + 1][N + 1];
        long[][] dp = new long[2][N + 1];
        Arrays.fill(dp[0], INF);
        dp[0][0] = 0;
        int currDP = 1;
        for (int i = 1; i <= K; i++) {
            hull.bot = 0;
            hull.top = 0;
            int currX = 0;
            for (int j = 0; j <= N; j++) {
                // Transition from best state
                State s = hull.query(currX);
                if (s == null) dp[currDP][j] = INF;
                else {
                    dp[currDP][j] = s.eval(currX);
                    from[i][j] = s.i;
                }
                // Add new transition
                if (dp[1-currDP][j] != INF) hull.add(currX, dp[1-currDP][j], j);
                // Move currX
                if (j != N) currX += arr[j];
            }
            // System.out.println(Arrays.toString(dp[currDP]));
            // System.out.println(Arrays.toString(from[i]));
            currDP = 1 - currDP;
        }

        long answer = 0;
        for (int i = 0; i < N; i++) answer += arr[i];
        answer *= answer;
        answer -= dp[1-currDP][N];
        answer /= 2;
        out.println(answer);
        int loc = N;
        for (int i = K; i > 1; i--) {
            loc = from[i][loc];
            
            if (i != K) out.print(' ');
            out.print(loc);
        }
        out.println();
    }

    class ConvexHull {
        State[] states;
        int bot, top;

        ConvexHull() {
            states = new State[N];
            for (int i = 0; i < N; i++) states[i] = new State(-1, -1, -1);
            bot = 0;
            top = 0;
        }

        void add(int sx, long sy, int i) {
            // Remove states with the same sx
            while (top - bot >= 2 && states[top-1].sx == sx) {
                if (states[top-1].sy > sy) top--;
                else return;  // This state is useless
            }
            // Remove useless states
            while (top - bot >= 2) {
                State prev = states[top-1];
                State prev2 = states[top-2];
                if (prev2.intersect(prev) >= prev.intersect(sx, sy)) {
                    // prev is useless
                    top--;
                } else break;
            }

            // Add this state
            states[top].sx = sx;
            states[top].sy = sy;
            states[top++].i = i;
        }

        /**
         * Assumes x is in increasing order.
         */
        State query(int x) {
            // Remove outdated states
            while (top - bot >= 2) {
                if (states[bot].eval(x) >= states[bot+1].eval(x)) {
                    // Bottom state is outdated
                    bot++;
                } else break;
            }
            if (top - bot == 0) return null;
            return states[bot];
        }
    }

    class State {
        int sx, i;
        long sy;

        State(int sx, long sy, int i) {
            this.sx = sx;
            this.sy = sy;
            this.i = i;
        }

        double intersect(State o) {
            return intersect(o.sx, o.sy);
        }

        double intersect(int osx, long osy) {
            double part1 = (sy - osy) / (2 * (sx - osx));
            double part2 = (sx + osx) / 2;
            return part1 + part2;
        }

        long eval(int x) {
            return sy + (long) (sx - x) * (sx - x);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new splitthesequence(in, out);
        in.close();
        out.close();
    }
}
