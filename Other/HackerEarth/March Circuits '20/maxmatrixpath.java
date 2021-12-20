import java.math.BigInteger;
import java.util.*;
import java.io.*;

public class maxmatrixpath {
    final int[] cxa = {-1, 0, 1, 0}, cya = {0, -1, 0, 1};
    int N;
    int[][] arr;
    ArrayList<Point> pathForward, pathBackward, pathSpiral;

    maxmatrixpath(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N][N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < N; j++) arr[i][j] = Integer.parseInt(st.nextToken());
        }
        BigInteger longMax = BigInteger.valueOf(Long.MAX_VALUE);

        // Very bad solution (for testing only)
        // System.out.println(Long.MAX_VALUE);
        // System.out.println(23563861928311008L);

        pathForward = new ArrayList<>();
        BigInteger score1 = BigInteger.ZERO;
        int y = 0, x = 0, cx = 1;
        while (pathForward.size() < N * N && score1.compareTo(longMax) < 0) {
            pathForward.add(new Point(x+1, y+1));
            score1 = score1.add(BigInteger.valueOf((long) arr[y][x] * pathForward.size()));
            x += cx;
            if (x < 0 || x >= N) {
                cx *= -1;
                y++;
                x += cx;
            }
        }
        // Reduce path by 1 if overflowed
        if (score1.compareTo(longMax) > 0) pathForward.remove(pathForward.size() - 1);

        // Try backward path
        pathBackward = new ArrayList<>();
        BigInteger score2 = BigInteger.ZERO;
        y = N - 1;
        x = N - 1;
        cx = -1;
        while (pathBackward.size() < N * N && score2.compareTo(longMax) < 0) {
            pathBackward.add(new Point(x+1, y+1));
            score2 = score2.add(BigInteger.valueOf((long) arr[y][x] * pathBackward.size()));
            x += cx;
            if (x < 0 || x >= N) {
                cx *= -1;
                y--;
                x += cx;
            }
        }
        // Reduce path by 1 if overflowed
        if (score2.compareTo(longMax) > 0) pathBackward.remove(pathBackward.size() - 1);

        // Try spiral path from center
        pathSpiral = new ArrayList<>();
        BigInteger score3 = BigInteger.ZERO;
        y = N / 2;
        x = N / 2;
        int dir = 0, stepsLeft = 1, startSteps = 1;
        while (pathSpiral.size() < N * N && score3.compareTo(longMax) < 0) {
            pathSpiral.add(new Point(x+1, y+1));
            score3 = score3.add(BigInteger.valueOf((long) arr[y][x] * pathSpiral.size()));
            x += cxa[dir];
            y += cya[dir];
            if (--stepsLeft == 0) {
                dir = (dir + 1) % 4;
                if (dir % 2 == 0) startSteps++;
                stepsLeft = startSteps;
            }
        }
        // Reduce path by 1 if overflowed
        if (score3.compareTo(longMax) > 0) pathSpiral.remove(pathSpiral.size() - 1);

        if (score1.compareTo(score2) > 0 && score1.compareTo(score3) > 0) printPath(pathForward, out);
        else if (score2.compareTo(score3) > 0) printPath(pathBackward, out);
        else printPath(pathSpiral, out);
    }

    void printPath(ArrayList<Point> path, PrintWriter out) {
        out.println(path.size());
        for (Point p : path) out.println(p);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new maxmatrixpath(in, out);
        in.close();
        out.close();
    }
}

class Point {
    int x, y;
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    @Override
    public String toString() {
        return y + " " + x;
    }
}