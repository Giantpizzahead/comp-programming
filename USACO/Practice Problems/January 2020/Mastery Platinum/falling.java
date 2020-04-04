import java.io.*;
import java.util.*;

public class falling {
    int N, sqrtN;
    int[] startY, Q;
    Line[] planetLine;
    Planet[] planets;
    Fraction[] answers;
    ArrayList<Line> waitingLines;
    ConvexHull hull;

    falling(BufferedReader in, PrintWriter out) throws IOException {
        // Line[] lines = new Line[] {new Line(6, 8), new Line(4, 9), new Line(1, 4), new Line(-1, 10), new Line(-2, 22), new Line(-3, 25)};
        // hull = new ConvexHull(lines);

        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        startY = new int[N];
        Q = new int[N];
        planets = new Planet[N];
        planetLine = new Line[N];
        answers = new Fraction[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) startY[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            Q[i] = Integer.parseInt(st.nextToken()) - 1;
            planets[i] = new Planet(startY[i], -i - 1, i);
        }

        sqrtN = (int) Math.ceil(Math.sqrt(N));
        waitingLines = new ArrayList<>(sqrtN);
        hull = new ConvexHull(new Line[0]);
        solve();

        // Flip the problem around to solve low to high queries
        for (int i = 0; i < N; i++) {
            startY[i] = 1000000001 - startY[i];
            planets[i] = new Planet(startY[i], i + 1, i);
        }

        waitingLines.clear();
        hull = new ConvexHull(new Line[0]);
        // System.out.println("Part 2");
        // System.out.println(Arrays.toString(startY));
        // System.out.println(Arrays.toString(planetLine));
        solve();

        for (Fraction f : answers) {
            if (f == null) out.println(-1);
            else out.println(f);
        }
        // System.out.println(Arrays.toString(answers));
    }

    void solve() {
        // Start with the highest up planets
        Arrays.sort(planets, new Comparator<Planet>() {
            @Override
            public int compare(Planet o1, Planet o2) {
                return o2.sy - o1.sy;
            }
        });

        Planet p;
        for (int i = 0; i < N; i++) {
            p = planets[i];
            // System.out.println(p.i);
            // Add this planet as a line
            waitingLines.add(planetLine[p.i]);
            if (waitingLines.size() == sqrtN) {
                // Time to make a new convex hull!
                int newSize = hull.lines.length + waitingLines.size();
                Line[] initLines = new Line[newSize];
                // Merge slopes in decreasing order
                waitingLines.sort(new Comparator<Line>() {
                    @Override
                    public int compare(Line o1, Line o2) {
                        return o2.m - o1.m;
                    }
                });
                int wli = 0, hi = 0;
                for (int j = 0; j < newSize; j++) {
                    if (wli == waitingLines.size()) initLines[j] = hull.lines[hi++];
                    else if (hi == hull.lines.length) initLines[j] = waitingLines.get(wli++);
                    else if (hull.lines[hi].m < waitingLines.get(wli).m) initLines[j] = waitingLines.get(wli++);
                    else initLines[j] = hull.lines[hi++];
                }
                hull = new ConvexHull(initLines);
                waitingLines.clear();
            }

            // Test all possible lines (if going down)
            if (startY[Q[p.i]] < p.sy) {
                // System.out.println("Testing " + p.i + " to " + Q[p.i]);
                Line bestLine = hull.query(planetLine[Q[p.i]]);
                double bestTime = -1;
                if (bestLine != null) bestTime = bestLine.intersect(planetLine[Q[p.i]]);
                for (Line l : waitingLines) {
                    double intersect = l.intersect(planetLine[Q[p.i]]);
                    // System.out.println(intersect);
                    if (intersect > 0 && (bestTime < 0 || intersect < bestTime)) {
                        // New best line
                        bestLine = l;
                        bestTime = intersect;
                    }
                }
                if (bestLine == null) continue;  // No line found
                Fraction fraction = bestLine.fractionIntersect(planetLine[Q[p.i]]);
                // System.out.println(fraction);
                if (fraction.a < 0 || fraction.b < 0) continue;  // Impossible to reach planet
                fraction.simplify();
                answers[p.i] = fraction;
            }
        }
    }

    class ConvexHull {
        final double INF = 987654322347d;
        final double EPSILON = 0.000001d;
        Line[] lines;
        double[] takeoverLocs;

        // Lines should be sorted in decreasing slope!
        ConvexHull(Line[] lineArr) {
            Line[] tempLines = new Line[lineArr.length];
            int top = 0;
            for (Line l : lineArr) {
                while (top >= 2) {
                    // Check for useless lines
                    Line prevLine = tempLines[top-1];
                    Line prev2Line = tempLines[top-2];
                    double intersect1 = prev2Line.intersect(prevLine);
                    double intersect2 = prevLine.intersect(l);
                    if (intersect1 + EPSILON >= intersect2) {
                        // prevLine is useless
                        top--;
                    } else break;
                }
                tempLines[top++] = l;
            }

            // Now make the actual line container
            lines = new Line[top];
            takeoverLocs = new double[top + 1];
            for (int i = 0; i < top; i++) {
                lines[i] = tempLines[i];
                if (i != 0) takeoverLocs[i] = lines[i-1].intersect(lines[i]);
                else takeoverLocs[i] = -INF;
            }
            takeoverLocs[top] = INF;

            // System.out.println(Arrays.toString(lines));
            // System.out.println(Arrays.toString(takeoverLocs));
        }

        // Finds the line that intersects with the given line at the earliest possible time.
        Line query(Line queryLine) {
            // Binary search on the first line that works
            int low = 0, high = lines.length - 1;
            while (low <= high) {
                // System.out.println("binary search " + low + " " + high);
                int mid = (low + high) / 2;
                Line currLine = lines[mid];
                double intersectTime = currLine.intersect(queryLine);
                if (intersectTime < 0) {
                    // Intersects later (this one doesn't intersect at all!)
                    low = mid + 1;
                } else if (intersectTime < takeoverLocs[mid]) {
                    // Convex hull intersects earlier
                    high = mid - 1;
                } else if (intersectTime > takeoverLocs[mid+1]) {
                    // Convex hull intersects later
                    low = mid + 1;
                } else {
                    // This is the right line!
                    return currLine;
                }
            }
            // No line found...?
            return null;
        }
    }

    class Fraction {
        int a, b;

        Fraction(int a, int b) {
            this.a = a;
            this.b = b;
            if (a < 0 && b < 0) {
                this.a *= -1;
                this.b *= -1;
            }
        }

        void simplify() {
            int gcf = gcf(a, b);
            a /= gcf;
            b /= gcf;
        }

        int gcf(int a, int b) {
            if (a == 0) return b;
            else return gcf(b % a, a);
        }

        @Override
        public String toString() {
            return a + "/" + b;
        }
    }

    class Planet {
        int sy, speed, i;

        Planet(int sy, int speed, int i) {
            this.sy = sy;
            this.speed = speed;
            this.i = i;
            planetLine[i] = new Line(speed, sy);
        }
    }

    class Line {
        int m, b;

        Line(int m, int b) {
            this.m = m;
            this.b = b;
        }

        double intersect(Line o) {
            return (double) (o.b - b) / (m - o.m);
        }

        Fraction fractionIntersect(Line o) {
            return new Fraction(o.b - b, m - o.m);
        }

        double eval(double x) {
            return m * x + b;
        }

        @Override
        public String toString() {
            return m + "x + " + b;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("falling.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("falling.out")));
        new falling(in, out);
        in.close();
        out.close();
    }
}
