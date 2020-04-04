import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class whiteboard {
    int H, W, N;
    ArrayList<Point>[][] hSegs, vSegs;
    boolean[][] isMarked;
    long[][] lastMarked;
    final long INF = 1_000_000_000_000_000L;

    whiteboard() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        H = Integer.parseInt(st.nextToken());
        W = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        isMarked = new boolean[H][W];
        for (int y=0; y<H; y++) {
            String line = in.readLine();
            for (int x=0; x<W; x++) {
                isMarked[y][x] = line.charAt(x) == '#';
            }
        }
        hSegs = new ArrayList[H][W];
        vSegs = new ArrayList[W][H];
        for (int y=0; y<H; y++) {
            for (int x=0; x<W; x++) {
                hSegs[y][x] = new ArrayList<>(2);
                vSegs[x][y] = new ArrayList<>(2);
            }
        }
        // Parse the instructions while simulating the drawing
        int currX = 0, currY = H-1;
        long currTime = 1;
        for (int i=0; i<N; i++) {
            st = new StringTokenizer(in.readLine());
            String type = st.nextToken();
            int amount = Integer.parseInt(st.nextToken());
            switch (type) {
                case "up":
                    vSegs[currX][currY].add(new Point(currY, amount, currTime, false, true));
                    currY -= amount;
                    vSegs[currX][currY].add(new Point(currY, amount, currTime, true, true));
                    break;
                case "right":
                    hSegs[currY][currX].add(new Point(currX, amount, currTime, true, false));
                    currX += amount;
                    hSegs[currY][currX].add(new Point(currX, amount, currTime, false, false));
                    break;
                case "down":
                    vSegs[currX][currY].add(new Point(currY, amount, currTime, true, false));
                    currY += amount;
                    vSegs[currX][currY].add(new Point(currY, amount, currTime, false, false));
                    break;
                default:  // Left
                    hSegs[currY][currX].add(new Point(currX, amount, currTime, false, true));
                    currX -= amount;
                    hSegs[currY][currX].add(new Point(currX, amount, currTime, true, true));
                    break;
            }
            currTime += amount;
        }
        in.close();

        lastMarked = new long[H][W];
        for (int y=0; y<H; y++) {
            for (int x=0; x<W; x++) {
                lastMarked[y][x] = -1;
            }
        }

        sweepHSegs();
        sweepVSegs();
        /*
        for (int y=0; y<H; y++) {
            System.out.println(Arrays.toString(lastMarked[y]));
        }
         */

        outputAnswers();
    }

    void outputAnswers() {
        long maxMarkerDrawn = 0;
        long minEraserDrawn = INF;
        for (int y=0; y<H; y++) {
            for (int x=0; x<W; x++) {
                if (isMarked[y][x]) {
                    if (lastMarked[y][x] == -1) {
                        // Impossible
                        maxMarkerDrawn = INF;
                    }
                    maxMarkerDrawn = Math.max(lastMarked[y][x], maxMarkerDrawn);
                } else if (!(lastMarked[y][x] == -1)) {
                    minEraserDrawn = Math.min(lastMarked[y][x], minEraserDrawn);
                }
            }
        }

        // System.out.println("Drawns: " + maxMarkerDrawn + " " + minEraserDrawn);

        PrintWriter out = new PrintWriter(System.out);
        if (maxMarkerDrawn > minEraserDrawn) {
            // Impossible
            out.println("-1 -1");
        } else if (minEraserDrawn == INF) {
            // Special case: Marker never dried out
            out.println(maxMarkerDrawn + " " + maxMarkerDrawn);
        } else {
            // Regular case
            out.println(maxMarkerDrawn + " " + (minEraserDrawn - 1));
        }
        out.close();
    }

    void sweepHSegs() {
        TreeSet<Point> currSegs = new TreeSet<>(Comparator.comparingLong(a -> a.startTime));
        // Sweep each y coordinate separately
        for (int y=0; y<H; y++) {
            currSegs.clear();
            for (int x=0; x<W; x++) {
                ArrayList<Point> points = hSegs[y][x];
                for (Point p : points) {
                    if (p.isStart) {
                        // Handle start point
                        currSegs.add(p);
                    }
                }

                // Update current lastMarked values
                if (!currSegs.isEmpty()) {
                    Point latestPoint = currSegs.last();
                    lastMarked[y][x] = Math.max(timeMarked(x, latestPoint), lastMarked[y][x]);
                }

                for (Point p : points) {
                    if (!p.isStart) {
                        // Handle end point
                        currSegs.remove(p);
                    }
                }
            }
        }
    }

    void sweepVSegs() {
        TreeSet<Point> currSegs = new TreeSet<>(Comparator.comparingLong(a -> a.startTime));
        // Sweep each x coordinate separately
        for (int x=0; x<W; x++) {
            currSegs.clear();
            for (int y=0; y<H; y++) {
                ArrayList<Point> points = vSegs[x][y];
                for (Point p : points) {
                    if (p.isStart) {
                        // Handle start point
                        currSegs.add(p);
                    }
                }

                // Update current lastMarked values
                if (!currSegs.isEmpty()) {
                    Point latestPoint = currSegs.last();
                    lastMarked[y][x] = Math.max(timeMarked(y, latestPoint), lastMarked[y][x]);
                }

                for (Point p : points) {
                    if (!p.isStart) {
                        // Handle end point
                        currSegs.remove(p);
                    }
                }
            }
        }
    }

    long timeMarked(int loc, Point point) {
        long result = point.startTime;
        if (!point.dirReversed) {
            result += loc - point.startLoc;
        } else {
            result = result + point.duration - (loc - point.startLoc);
        }
        return result;
    }

    public static void main(String[] args) throws IOException {
        new whiteboard();
    }

    static class Point {
        int startLoc, duration;
        long startTime;
        boolean isStart, dirReversed;
        Point(int startLoc, int duration, long startTime, boolean isStart, boolean dirReversed) {
            this.startLoc = startLoc;
            this.duration = duration;
            this.startTime = startTime;
            this.isStart = isStart;
            this.dirReversed = dirReversed;
        }
    }
}
