/*
Solution: Make the convex hull of the given points. This is my first try implementing this, so wish me luck! :D

Runtime: O(T * N * log(N))
*/

import org.w3c.dom.ls.LSOutput;

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class BSHEEP {
    final int INF = 987654321;
    int T, N;
    Point[] points;
    ArrayList<Point> hull = new ArrayList<>();

    BSHEEP() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            testCase(in, out);
            if (i != T - 1) out.println();
        }
        in.close();
        out.close();
    }

    void testCase(BufferedReader in, PrintWriter out) throws IOException {
        in.readLine();
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        points = new Point[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            points[i] = new Point(x, y, i + 1);
        }
        Arrays.sort(points, new Comparator<Point>() {
            @Override
            public int compare(Point a, Point b) {
                if (a.y != b.y) return a.y - b.y;
                else if (a.x != b.x) return a.x - b.x;
                else return a.id - b.id;
            }
        });
        convexHull();

        double perimeter = 0;
        for (int i = 1; i < hull.size(); i++) {
            perimeter += dist(hull.get(i-1), hull.get(i));
        }
        perimeter += dist(hull.get(hull.size() - 1), hull.get(0));

        out.printf("%.2f\n", perimeter);
        for (int i = 0; i < hull.size(); i++) {
            out.print(hull.get(i).id);
            if (i != hull.size() - 1) out.print(' ');
            else out.println();
        }
    }

    double dist(Point a, Point b) {
        return Math.sqrt(Math.pow(Math.abs(a.x - b.x), 2) + Math.pow(Math.abs(a.y - b.y), 2));
    }

    void convexHull() {
        hull.clear();
        Point p;

        // Use Andrew's sweep algorithm
        // Upper hull
        for (int i = 0; i < N; i++) {
            p = points[i];
            while (hull.size() >= 2 && ccw(hull.get(hull.size() - 2), hull.get(hull.size() - 1), p) <= 0) {
                // Left turn caused by new point, meaning last point must be removed from hull
                hull.remove(hull.size() - 1);
            }
            hull.add(p);
        }
        int upperHullSize = hull.size();

        // Lower hull
        for (int i = N - 2; i >= 0; i--) {
            p = points[i];
            while (hull.size() >= upperHullSize + 1 && ccw(hull.get(hull.size() - 2), hull.get(hull.size() - 1), p) <= 0) {
                // Left turn caused by new point, last point must be removed
                hull.remove(hull.size() - 1);
            }
            hull.add(p);
        }

        if (hull.size() >= 2) hull.remove(hull.size() - 1); // Duplicated last element
    }

    // Determines whether a->b->c is a left (+), right (-), or no (0) turn.
    int ccw(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    public static void main(String[] args) throws IOException {
        new BSHEEP();
    }

    static class Point {
        int x, y, id;
        Point(int x, int y, int id) {
            this.x = x;
            this.y = y;
            this.id = id;
        }
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }
}
