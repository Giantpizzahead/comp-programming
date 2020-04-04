/*
Solution: A very unique convex hull trick problem. First, reverse the queries if the query world's y is higher than the
starting world. Then, evaluate worlds in decreasing y coord order.
To answer a query, binary search on the line (world) where the best y attainable reaches the moving query y. The line
where this happens is the best line.

Runtime: O(N * log(N)^2)
*/

import java.io.*;
import java.util.Arrays;
import java.util.Comparator;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class falling3 {
    int N;
    Pair[] evalOrder;
    int[] startY;
    Fraction[] answers;
    int[] queries;

    falling3(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        evalOrder = new Pair[N];
        startY = new int[N];
        answers = new Fraction[N];
        queries = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            startY[i] = Integer.parseInt(st.nextToken());
            evalOrder[i] = new Pair(i, startY[i]);
        }
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            int t = Integer.parseInt(st.nextToken()) - 1;
            queries[i] = t;
        }

        // Process worlds in order of decreasing y coord
        Arrays.sort(evalOrder, new Comparator<Pair>() {
            @Override
            public int compare(Pair o1, Pair o2) {
                return o2.n - o1.n;
            }
        });

        // Answer queries going down
        ConvexHull ch = new ConvexHull();
        int c;
        for (Pair p : evalOrder) {
            c = p.i;
            // Add current world to convex hull container
            ch.add(new Line(-c-1, startY[c]));

            // Answer query involving this world (if applicable)
            if (startY[queries[c]] < startY[c]) {
                // Going down = Query can be answered now
                int t = queries[c];
                // System.out.println("query " + c + " to " + t);
                Line line = ch.query(t);
                // System.out.println("using line " + line);
                if (line == null) answers[c] = null;
                else {
                    Fraction f = new Fraction(startY[t] - line.b, line.m - (-t - 1));
                    f.simplify();
                    answers[c] = f;
                }
            }
        }

        // System.out.println("switched");

        // Answer queries going up
        ConvexHullOpp cho = new ConvexHullOpp();
        Pair p;
        for (int i = N - 1; i >= 0; i--) {
            p = evalOrder[i];
            c = p.i;
            // Add current world to convex hull container
            cho.add(new Line(-c-1, startY[c]));

            // Answer query involving this world (if applicable)
            if (startY[queries[c]] > startY[c]) {
                // Going up = Query can be answered now
                int t = queries[c];
                // System.out.println("query " + c + " to " + t);
                Line line = cho.query(t);
                // System.out.println("using line " + line);
                if (line == null) answers[c] = null;
                else {
                    Fraction f = new Fraction(startY[t] - line.b, line.m - (-t - 1));
                    f.simplify();
                    answers[c] = f;
                }
            }
        }

        for (Fraction a : answers) {
            if (a == null) out.println(-1);
            else out.println(a);
        }
    }

    class ConvexHull {
        TreeSet<Line> lines = new TreeSet<>(new Comparator<Line>() {
            // Sort in order of decreasing slope (- to \ to |)
            @Override
            public int compare(Line o1, Line o2) {
                return o2.m - o1.m;
            }
        });

        void add(Line l) {
            // Check if this line is useless
            Line lower = lines.lower(l);
            Line higher = lines.higher(l);
            if (lower != null && higher != null && lower.intersect(l) >= l.intersect(higher)) {
                // System.out.println(l + " useless");
                return;  // Useless
            }

            // This line is useful; remove useless lines above this one
            if (higher != null) {
                Line higher2 = lines.higher(higher);
                while (higher2 != null && l.intersect(higher) >= higher.intersect(higher2)) {
                    // higher is useless (this one is always better)
                    lines.remove(higher);
                    higher = higher2;
                    higher2 = lines.higher(higher);
                }
            }

            // Remove useless lines before this one
            if (lower != null) {
                Line lower2 = lines.lower(lower);
                while (lower2 != null && lower2.intersect(lower) >= lower.intersect(l)) {
                    // lower is useless (this one is always better)
                    lines.remove(lower);
                    lower = lower2;
                    lower2 = lines.lower(lower);
                }
            }

            // Add this line
            lines.add(l);

            // System.out.println(lines);
        }

        // Find the line that first overtakes world t's y position. Returns null if no line
        // is found. Uses binary search on the line's slope.
        Line query(int t) {
            int low = -N, high = -1;
            while (low < high) {
                // System.out.println(low + " " + high);
                int mid = (low + high) / 2;
                if (check(mid, t)) {
                    // Overtook before (or at) this line
                    low = mid;
                } else {
                    // Never overtook world t
                    high = mid - 1;
                }
            }

            // System.out.println(low);
            return lines.ceiling(new Line(low, 0));
        }

        boolean check(int m, int t) {
            Line curr = lines.floor(new Line(m, 0));
            // System.out.println(curr);
            if (curr == null) return false;  // No line exists with shallow enough slope

            // Find last time before this line is overtaken
            Line higher = lines.higher(curr);
            double lastT;
            if (higher == null) lastT = 1000000007;
            else lastT = curr.intersect(higher);
            // System.out.println(lastT);

            // Does this line overtake query world?
            return curr.eval(lastT) - 0.000001 < new Line(-t-1, startY[t]).eval(lastT);
        }
    }

    class ConvexHullOpp {
        TreeSet<Line> lines = new TreeSet<>(new Comparator<Line>() {
            // Sort in order of increasing slope (| to \ to -)
            @Override
            public int compare(Line o1, Line o2) {
                return o1.m - o2.m;
            }
        });

        void add(Line l) {
            // Check if this line is useless
            Line lower = lines.lower(l);
            Line higher = lines.higher(l);
            if (lower != null && higher != null && lower.intersect(l) >= l.intersect(higher)) {
                // System.out.println(l + " useless");
                return;  // Useless
            }

            // This line is useful; remove useless lines above this one
            if (higher != null) {
                Line higher2 = lines.higher(higher);
                while (higher2 != null && l.intersect(higher) >= higher.intersect(higher2)) {
                    // higher is useless (this one is always better)
                    lines.remove(higher);
                    higher = higher2;
                    higher2 = lines.higher(higher);
                }
            }

            // Remove useless lines before this one
            if (lower != null) {
                Line lower2 = lines.lower(lower);
                while (lower2 != null && lower2.intersect(lower) >= lower.intersect(l)) {
                    // lower is useless (this one is always better)
                    lines.remove(lower);
                    lower = lower2;
                    lower2 = lines.lower(lower);
                }
            }

            // Add this line
            lines.add(l);

            // System.out.println(lines);
        }

        // Find the line that first overtakes world t's y position. Returns null if no line
        // is found. Uses binary search on the line's slope.
        Line query(int t) {
            int low = -N, high = -1;
            while (low < high) {
                // System.out.println(low + " " + high);
                int mid = (low + high - 1) / 2;
                if (check(mid, t)) {
                    // Overtook before (or at) this line
                    high = mid;
                } else {
                    // Never overtook world t
                    low = mid + 1;
                }
            }

            // System.out.println(low);
            return lines.ceiling(new Line(low, 0));
        }

        boolean check(int m, int t) {
            Line curr = lines.floor(new Line(m, 0));
            // System.out.println(curr);
            if (curr == null) return false;  // No line exists with shallow enough slope

            // Find last time before this line is overtaken
            Line higher = lines.higher(curr);
            double lastT;
            if (higher == null) lastT = 1000000007;
            else lastT = curr.intersect(higher);
            // System.out.println(lastT);

            // Does this line overtake query world?
            return curr.eval(lastT) + 0.000001 > new Line(-t-1, startY[t]).eval(lastT);
        }
    }

    static class Line {
        int m, b;

        Line(int mm, int bb) {
            m = mm;
            b = bb;
        }

        double eval(double t) {
            return m * t + b;
        }

        double intersect(Line other) {
            return (double) (other.b - b) / (m - other.m);
        }

        @Override
        public String toString() {
            return m + "x + " + b;
        }
    }

    static class Fraction {
        int n, d;

        Fraction(int nn, int dd) {
            n = nn;
            d = dd;
            if (n < 0 && d < 0) {
                n = -n;
                d = -d;
            }
        }

        void simplify() {
            int gcf = getGCF(n, d);
            n /= gcf;
            d /= gcf;
        }

        int getGCF(int a, int b) {
            if (b == 0) return a;
            else return getGCF(b, a % b);
        }

        public String toString() {
            if ((n < 0) != (d < 0)) return "-1";
            else return n + "/" + d;
        }
    }

    static class Pair {
        int i, n;
        Pair(int ii, int nn) {
            i = ii;
            n = nn;
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(System.out);
        BufferedReader in = new BufferedReader(new FileReader("falling.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("falling.out")));
        new falling3(in, out);
        in.close();
        out.close();
    }
}
