/*
Solution: Sort the rectangles by x-coordinate. Then, do DP with the convex
hull trick.
Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class rectangles {
    int N;
    Rect[] rects;

    rectangles(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        rects = new Rect[N];
        int x, y;
        long a;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            a = Long.parseLong(st.nextToken());
            rects[i] = new Rect(x, y, a);
        }

        Arrays.sort(rects, new Comparator<Rect>() {
            @Override
            public int compare(Rect o1, Rect o2) {
                return o1.x - o2.x;
            }
        });

        long[] dp = new long[N];
        long answer = 0;
        LineHolder lh = new LineHolder();
        // Base transition
        lh.addLine(new Line(0, 0));

        Rect r;
        for (int i = 0; i < N; i++) {
            r = rects[i];
            dp[i] = lh.query(r.y) + (long) r.x * r.y - r.a;
            answer = Math.max(dp[i], answer);
            Line newLine = new Line(-r.x, dp[i]);
            lh.addLine(newLine);
        }

        // System.out.println(Arrays.toString(dp));

        out.println(answer);
    }

    static class Rect {
        int x, y;
        long a;
        Rect(int xx, int yy, long aa) {
            x = xx;
            y = yy;
            a = aa;
        }
    }

    class LineHolder {
        Line[] lines;
        int front = 2, back = 2, size = 0;

        LineHolder() {
            lines = new Line[N + 5];
        }

        // Assumes lines are added with decreasing slope (which they will be)
        void addLine(Line l) {
            // Remove outdated lines (this one overtakes before the old one)
            Line currFront = lines[front - 1];
            Line nextFront = lines[front - 2];
            while (size > 1 && l.intersect(currFront) >= currFront.intersect(nextFront)) {
                // currFront will never be the best line
                front--;
                size--;
                currFront = lines[front - 1];
                nextFront = lines[front - 2];
            }

            // Add this line
            lines[front++] = l;
            size++;
        }

        // Assumes queries are decreasing (which they will be)
        long query(int n) {
            // Remove outdated lines at back
            Line currBack = lines[back];
            Line nextBack = lines[back + 1];
            // if (size > 1) System.out.println(currBack.intersect(nextBack));
            while (size > 1 && currBack.intersect(nextBack) >= n) {
                // currBack is now outdated
                back++;
                size--;
                currBack = lines[back];
                nextBack = lines[back + 1];
            }
            return currBack.eval(n);
        }
    }

    static class Line {
        int m;
        long b;
        Line(int m, long b) {
            this.m = m;
            this.b = b;
        }

        // Returns the intersection point (x-coord) of the two lines.
        double intersect(Line o) {
            return (double) (o.b - b) / (m - o.m);
        }

        long eval(int x) {
            return (long) m * x + b;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("rectangles.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("rectangles.out")));
        new rectangles(in, out);
        in.close();
        out.close();
    }
}