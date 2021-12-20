import java.io.*;
import java.util.*;

public class wormhole {
    int N;
    Point[] points;

    wormhole(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        points = new Point[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            points[i] = new Point(x, y);
        }

        // Try all possible directions
        int answer = 1;
        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {
                answer = Math.max(tryDirection(points[i], points[j]), answer);
            }
        }

        out.println("Case #" + tn + ": " + answer);
    }

    HashMap<Long, Integer> count;
    int tryDirection(Point a, Point b) {
        count = new HashMap<>();
        if (a.x - b.x == 0) {
            // Special case (vertical line)
            for (Point p : points) {
                long hashGroup = p.x;
                count.put((long) hashGroup, count.getOrDefault(hashGroup, 0) + 1);
            }
        } else {
            int slopeNumer = a.y - b.y;
            int slopeDenom = a.x - b.x;
            if (slopeDenom < 0) {
                slopeDenom = -slopeDenom;
                slopeNumer = -slopeNumer;
            }
            for (Point p : points) {
                long hashGroup = (long) p.y * slopeDenom - (long) p.x * slopeNumer;
                count.put(hashGroup, count.getOrDefault(hashGroup, 0) + 1);
            }
        }

        // Do greedy thing
        int non1Sum = 0;
        int num1s = 0;
        int numOdd = 0, numEven = 0;
        for (Map.Entry<Long, Integer> entry : count.entrySet()) {
            if (entry.getValue() == 1) num1s++;
            else {
                if (entry.getValue() % 2 == 0) numEven++;
                else numOdd++;
                non1Sum += entry.getValue();
            }
        }

        if (numOdd % 2 == 1) return non1Sum + Math.min(num1s, 1);
        else return non1Sum + Math.min(num1s, 2);
    }

    class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new wormhole(in, out, i);
        in.close();
        out.close();
    }
}
