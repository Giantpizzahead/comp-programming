import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class optics {
    int N, R, C, laserX, laserY, barnX, barnY;
    TreeSet<Integer> xLocs, yLocs;
    TreeSet<Mirror>[] xToMirrors, yToMirrors;
    Mirror[] mirrors;
    BIT2D horSegs, vertSegs;

    optics(BufferedReader fin, PrintWriter fout) throws IOException {
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        barnX = Integer.parseInt(st.nextToken());
        barnY = Integer.parseInt(st.nextToken());
        xLocs = new TreeSet<>();
        yLocs = new TreeSet<>();
        mirrors = new Mirror[N];
        int x, y;
        char orient;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            orient = st.nextToken().charAt(0);
            xLocs.add(x);
            yLocs.add(y);
            mirrors[i] = new Mirror(x, y, i, orient == '\\');
        }
        xLocs.add(laserX);
        yLocs.add(laserY);
        xLocs.add(barnX);
        yLocs.add(barnY);
        // Coordinate compression
        Integer[] xArr = xLocs.toArray(new Integer[0]);
        Integer[] yArr = yLocs.toArray(new Integer[0]);
        for (int i = 0; i < N; i++) {
            mirrors[i].x = Arrays.binarySearch(xArr, mirrors[i].x);
            mirrors[i].y = Arrays.binarySearch(yArr, mirrors[i].y);
        }
        laserX = Arrays.binarySearch(xArr, laserX);
        laserY = Arrays.binarySearch(yArr, laserY);
        barnX = Arrays.binarySearch(xArr, barnX);
        barnY = Arrays.binarySearch(yArr, barnY);

        R = yArr.length;
        C = xArr.length;

        // Keep mirror lookup tables for easy simulation
        xToMirrors = new TreeSet[C];
        yToMirrors = new TreeSet[R];
        for (int i = 0; i < C; i++) xToMirrors[i] = new TreeSet<>(new Comparator<Mirror>() {
            @Override
            public int compare(Mirror o1, Mirror o2) {
                return o1.y - o2.y;
            }
        });
        for (int i = 0; i < R; i++) yToMirrors[i] = new TreeSet<>(new Comparator<Mirror>() {
            @Override
            public int compare(Mirror o1, Mirror o2) {
                return o1.x - o2.x;
            }
        });

        for (Mirror m : mirrors) {
            xToMirrors[m.x].add(m);
            yToMirrors[m.y].add(m);
        }

        // Generate segments to be intersected with later
        horSegs = new BIT2D(C, R);
        vertSegs = new BIT2D(R, C);
        simulateLaser();

        // Now, try simulating from the barn, and count the # of intersections with the laser
        int answer = 0;
        // Avoid visiting the same side of a mirror twice
        // Add the barn as a mirror for easier implementation
        Mirror barn = new Mirror(barnX, barnY, N, true);
        xToMirrors[barnX].add(barn);
        yToMirrors[barnY].add(barn);
        visited = new boolean[2][N];
        barnVisited = new boolean[4];
        for (int dir = 0; dir < 4; dir++) {
            if (!barnVisited[dir]) answer += simulateBarn(dir);
        }
        fout.println(answer);
    }

    int[] cx = {0, 1, 0, -1}, cy = {1, 0, -1, 0};
    boolean[][] visited;
    boolean[] barnVisited;
    int simulateBarn(int startDir) {
        int x = barnX, y = barnY, dir = startDir, newDir, answer = 0, type;
        Mirror m;
        while (true) {
            if (dir == 0) {
                m = xToMirrors[x].higher(new Mirror(x, y, 0, true));
                if (m == null) break;
                answer += horSegs.queryPoint(y + 1, m.y - 1, x);
                if (m.isUL) {
                    newDir = 3;
                    type = 0;
                } else {
                    newDir = 1;
                    type = 0;
                }
            } else if (dir == 2) {
                m = xToMirrors[x].lower(new Mirror(x, y, 0, true));
                if (m == null) break;
                answer += horSegs.queryPoint(m.y + 1, y - 1, x);
                if (m.isUL) {
                    newDir = 1;
                    type = 1;
                } else {
                    newDir = 3;
                    type = 1;
                }
            } else if (dir == 1) {
                m = yToMirrors[y].higher(new Mirror(x, y, 0, true));
                if (m == null) break;
                answer += vertSegs.queryPoint(x + 1, m.x - 1, y);
                if (m.isUL) {
                    newDir = 2;
                    type = 0;
                } else {
                    newDir = 0;
                    type = 1;
                }
            } else {
                m = yToMirrors[y].lower(new Mirror(x, y, 0, true));
                if (m == null) break;
                answer += vertSegs.queryPoint(m.x + 1, x - 1, y);
                if (m.isUL) {
                    newDir = 0;
                    type = 1;
                } else {
                    newDir = 2;
                    type = 0;
                }
            }
            if (m.id == N) {
                // Barn reached; record and stop here
                barnVisited[(dir + 2) % 4] = true;
                return answer;
            } else if (visited[type][m.id]) {
                // Visited this path already
                return answer;
            } else visited[type][m.id] = true;
            x = m.x;
            y = m.y;
            dir = newDir;
        }
        // Query final
        if (dir == 0) answer += horSegs.queryPoint(y + 1, R, x);
        else if (dir == 2) answer += horSegs.queryPoint(0, y - 1, x);
        else if (dir == 1) answer += vertSegs.queryPoint(x + 1, C, y);
        else answer += vertSegs.queryPoint(0, x - 1, y);
        return answer;
    }

    void simulateLaser() {
        int x = laserX, y = laserY, dir = 0;
        Mirror m;
        while (true) {
            if (dir == 0) {
                m = xToMirrors[x].higher(new Mirror(x, y, 0, true));
                if (m == null) break;
                vertSegs.addSegment(y, m.y, x);
                if (m.isUL) dir = 3;
                else dir = 1;
            } else if (dir == 2) {
                m = xToMirrors[x].lower(new Mirror(x, y, 0, true));
                if (m == null) break;
                vertSegs.addSegment(m.y, y, x);
                if (m.isUL) dir = 1;
                else dir = 3;
            } else if (dir == 1) {
                m = yToMirrors[y].higher(new Mirror(x, y, 0, true));
                if (m == null) break;
                horSegs.addSegment(x, m.x, y);
                if (m.isUL) dir = 2;
                else dir = 0;
            } else {
                m = yToMirrors[y].lower(new Mirror(x, y, 0, true));
                if (m == null) break;
                horSegs.addSegment(m.x, x, y);
                if (m.isUL) dir = 0;
                else dir = 2;
            }
            x = m.x;
            y = m.y;
        }
        // Add final
        if (dir == 0) vertSegs.addSegment(y, R, x);
        else if (dir == 2) vertSegs.addSegment(0, y, x);
        else if (dir == 1) horSegs.addSegment(x, C, y);
        else horSegs.addSegment(0, x, y);
    }

    // Range updates, point queries.
    class BIT2D {
        int size;
        BIT[] vals;

        BIT2D(int size1, int size2) {
            size = size1;
            vals = new BIT[size + 1];
            for (int i = 1; i <= size; i++) vals[i] = new BIT(size2);
        }

        void addSegment(int l, int r, int p) {
            // System.out.println("add l = " + l + ", r = " + r + ", p = " + p);
            l++;
            r++;
            p++;
            addPoint(l, p, 1);
            addPoint(r + 1, p, -1);
        }

        void addPoint(int i, int p, int v) {
            while (i <= size) {
                vals[i].add(p, v);
                i += Integer.lowestOneBit(i);
            }
        }

        int queryPoint(int l, int r, int i) {
            // System.out.println("query l = " + l + ", r = " + r + ", i = " + i);
            l++;
            r++;
            i++;
            if (l > r) return 0;
            int result = 0;
            while (i > 0) {
                result += vals[i].query(l, r);
                i -= Integer.lowestOneBit(i);
            }
            // System.out.println(result);
            return result;
        }
    }

    // Point updates, range queries.
    class BIT {
        final int MIN_BIT_SIZE = 1100;
        int size;
        int[] vals;
        boolean isBIT;
        ArrayList<Pair> points;

        BIT(int size) {
            this.size = size;
            isBIT = false;
            points = new ArrayList<>(2);
        }

        void add(int i, int v) {
            if (isBIT) {
                while (i <= size) {
                    vals[i] += v;
                    i += Integer.lowestOneBit(i);
                }
            } else {
                points.add(new Pair(i, v));
                if (points.size() >= MIN_BIT_SIZE) {
                    // Convert to BIT
                    isBIT = true;
                    vals = new int[size + 1];
                    for (Pair p : points) {
                        add(p.a, p.b);
                    }
                }
            }
        }

        class Pair {
            int a, b;
            Pair(int a, int b) {
                this.a = a;
                this.b = b;
            }
        }

        int query(int l, int r) {
            if (isBIT) return query0(r) - query0(l-1);
            else {
                int result = 0;
                for (Pair p : points) {
                    if (l <= p.a && p.a <= r) result += p.b;
                }
                return result;
            }
        }

        int query0(int i) {
            int result = 0;
            while (i > 0) {
                result += vals[i];
                i -= Integer.lowestOneBit(i);
            }
            return result;
        }
    }

    class Mirror {
        int x, y, id;
        boolean isUL;
        Mirror(int x, int y, int id, boolean isUL) {
            this.x = x;
            this.y = y;
            this.id = id;
            this.isUL = isUL;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("optics.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("optics.out")));
        new optics(fin, fout);
        fin.close();
        fout.close();
    }
}
