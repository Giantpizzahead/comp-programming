/*
Solution: Convex hull but it's not convex hull but it is convex hull. Fun! :)

Add 2 points at the start and end with 0 values for easier implementation. Also, put the points as an up-shaped convex
hull (semicircle facing up).

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class balance {
    int N;
    Point[] points;

    balance() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("balance.in"));
        N = Integer.parseInt(fin.readLine());
        points = new Point[N + 2];
        points[0] = new Point(0, 0);
        for (int i = 1; i < N + 1; i++) {
            points[i] = new Point(i, Long.parseLong(fin.readLine()) * 100000);
        }
        points[N + 1] = new Point(N + 1, 0);
        fin.close();

        Point[] hull = new Point[N + 2];
        int hullI = 0;
        hull[hullI++] = points[0];
        hull[hullI++] = points[1];
        for (int i = 2; i < N + 2; i++) {
            while (hullI >= 2 && ccw(hull[hullI-2], hull[hullI-1], points[i]) >= 0) hullI--;
            hull[hullI++] = points[i];
        }

        int hullSize = hullI;
        hull = Arrays.copyOf(hull, hullSize);
        // System.out.println(Arrays.toString(hull));

        PrintWriter fout = new PrintWriter("balance.out");
        int currI = 0;
        for (int i = 1; i < N + 1; i++) {
            if (hull[currI + 1].x == i) currI++;
            Point currPoint = hull[currI], nextPoint = hull[currI + 1];
            long fromSlope, expectedVal;
            if (nextPoint.y - currPoint.y >= 0) {
                // Slope positive; calculate from left
                fromSlope = (nextPoint.y - currPoint.y) * (i - currPoint.x) / (nextPoint.x - currPoint.x);
                expectedVal = currPoint.y + fromSlope;
            } else {
                // Slope negative; calculate from right
                fromSlope = (currPoint.y - nextPoint.y) * (nextPoint.x - i) / (currPoint.x - nextPoint.x);
                expectedVal = nextPoint.y - fromSlope;
            }
            fout.println(expectedVal);
        }
        fout.close();
    }

    long ccw(Point a, Point b, Point c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }

    public static void main(String[] args) throws IOException {
        new balance();
    }

    static class Point {
        long x, y;
        Point(long x, long y) {
            this.x = x;
            this.y = y;
        }
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }
}