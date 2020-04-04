/*
USACO 2016 January (Platinum), Problem 2. Mowing the Field
Solution: Handle vertical and horizontal queries separately (since we're only
checking for perp. intersections). For vertical queries:
Store horizontal segments in a segment tree, with each node containing an interval
tree. Segment tree stores y values, interval tree stores x ranges.
When adding a new horizontal segment, treat the segment tree as a range of
y values (root node is [0, MAXY], splits into child nodes). Insert the new segment
into the interval trees with that Y value (max log(N) insertions).
To query a vertical segment, query all the interval trees that the segment tree
would normally return, and sum the results (max log(N) queries).
Do the same thing for the other type of query. To handle segments only being
counted after a certain time, check intersections for segment i+T before inserting
segment i.

Runtime: O(N * log(N)^2 + A lot of other factors)
This should be ok, since the time limit's been raised to 10 seconds.
*/

import java.util.*;
import java.io.*;

public class mowing {
    int N, T;
    Integer[] xCoords, yCoords;
    Point[] points;

    mowing() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("mowing.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        points = new Point[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            points[i] = new Point(x, y);
        }
        fin.close();

        /*
        // Test BIT
        SegHolder sh = new SegHolder(300000);
        SegHolder sh2 = new SegHolder(300000);
        sh2.K = 100000;
        for (int i = 0; i < 5000; i++) {
            Segment s = new Segment((int) (Math.random() * 300000), (int) (Math.random() * 300000));
            sh2.add(s);
            sh.add(new Segment(s.s, s.e));
        }
        for (int i = 0; i < 30; i++) {
            if (sh.query(i) != sh2.query(i)) {
                System.out.println(i + " -> " + sh.query(i) + " " + sh.query(2));
            }
        }
        System.out.println();
         */

        // Coordinate compression
        TreeSet<Integer> xSet = new TreeSet<>();
        for (int i = 0; i < N; i++) xSet.add(points[i].x);
        xCoords = xSet.toArray(new Integer[0]);

        TreeSet<Integer> ySet = new TreeSet<>();
        for (int i = 0; i < N; i++) ySet.add(points[i].y);
        yCoords = ySet.toArray(new Integer[0]);

        // Compress each point
        for (int i = 0; i < N; i++) {
            points[i].x = Arrays.binarySearch(xCoords, points[i].x);
            points[i].y = Arrays.binarySearch(yCoords, points[i].y);
        }

        // Handle queries
        long answer = handleQueries();

        PrintWriter fout = new PrintWriter("mowing.out");
        fout.println(answer);
        fout.close();
    }

    long handleQueries() {
        BIT xBIT = new BIT(xCoords.length, yCoords.length);
        BIT yBIT = new BIT(yCoords.length, xCoords.length);
        long answer = 0;
        for (int i = 0; i < N - 1; i++) {
            if (points[i].x != points[i+1].x) {
                // Horizontal segment
                int x1 = Math.min(points[i].x, points[i+1].x);
                int x2 = Math.max(points[i].x, points[i+1].x);
                yBIT.add(new Segment(x1, x2), points[i].y);
            } else {
                // Vertical segment
                int y1 = Math.min(points[i].y, points[i+1].y);
                int y2 = Math.max(points[i].y, points[i+1].y);
                xBIT.add(new Segment(y1, y2), points[i].x);
            }

            // Do queries for later segments
            int queryI = i + T;
            if (queryI < N - 1) {
                // Segment exists to query
                if (points[queryI].x != points[queryI+1].x) {
                    // Horizontal segment
                    int x1 = Math.min(points[queryI].x, points[queryI+1].x);
                    int x2 = Math.max(points[queryI].x, points[queryI+1].x);
                    answer += xBIT.query(x1, x2, points[queryI].y);
                } else {
                    // Vertical segment
                    int y1 = Math.min(points[queryI].y, points[queryI+1].y);
                    int y2 = Math.max(points[queryI].y, points[queryI+1].y);
                    answer += yBIT.query(y1, y2, points[queryI].x);
                }
            } else {
                // No more queries will happen; stop here
                return answer;
            }
        }

        return answer;
    }

    public static void main(String[] args) throws IOException {
        new mowing();
    }
}

class BIT {
    int size, holderSize;
    SegHolder[] vals;
    BIT(int size, int holderSize) {
        this.size = size;
        this.holderSize = holderSize;
        vals = new SegHolder[size + 1];
        for (int i = 1; i < size + 1; i++) vals[i] = new SegHolder(holderSize);
    }

    void add(Segment seg, int loc) {
        loc++;
        while (loc <= size) {
            vals[loc].add(seg);
            loc += Integer.lowestOneBit(loc);
        }
    }

    int query(int start, int end, int loc) {
        start++;
        end++;
        if (end - start < 2) return 0;
        return queryFromStart(end - 1, loc) - queryFromStart(start, loc);
    }

    int queryFromStart(int index, int loc) {
        if (index <= 0) return 0;
        else {
            int result = 0;
            while (index > 0) {
                result += vals[index].query(loc);
                index -= Integer.lowestOneBit(index);
            }
            return result;
        }
    }
}

// This is just a simple ArrayList when # segs < K, otherwise it's a BIT.
class SegHolder {
    int K = 100;
    int bitSize;
    ArrayList<Segment> segs;
    int[] vals;
    boolean isBig = false;
    SegHolder(int size) {
        bitSize = size;
        segs = new ArrayList<>(3);
    }

    void convertToBIT() {
        isBig = true;
        vals = new int[bitSize + 1];
        for (Segment s : segs) add(s);
        segs.clear();
    }

    void add(Segment seg) {
        if (!isBig) {
            // ArrayList
            segs.add(seg);
            if (segs.size() >= K) {
                convertToBIT();
            }
        } else {
            // BIT
            if (seg.e - seg.s < 2) return;
            addRaw(seg.s + 2, 1);
            addRaw(seg.e + 1, -1);
        }
    }

    void addRaw(int loc, int val) {
        while (loc <= bitSize) {
            vals[loc] += val;
            loc += Integer.lowestOneBit(loc);
        }
    }

    int query(int loc) {
        int result = 0;
        if (!isBig) {
            // ArrayList
            for (Segment seg : segs) {
                if (seg.s < loc && seg.e > loc) result++;
            }
        } else {
            // BIT
            loc++;
            while (loc > 0) {
                result += vals[loc];
                loc -= Integer.lowestOneBit(loc);
            }
        }
        return result;
    }
}

class Segment {
    int s, e;
    Segment(int s, int e) {
        this.s = s;
        this.e = e;
    }
}

class Point {
    int x, y;
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}