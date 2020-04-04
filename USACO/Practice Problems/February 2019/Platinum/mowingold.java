/*
Solution: Basic DP for now.
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class mowing {
    int N, T;
    Point[] flowers;
    final long INF = 1_000_000_000_000_000L;

    mowing() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("mowing.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        flowers = new Point[N + 1];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            flowers[i] = new Point(x, y);
        }
        fin.close();

        // Sort points by x coordinate
        flowers[N] = new Point(T, T);
        Arrays.sort(flowers, (a, b) -> { return a.x - b.x; });

        long answer = doDP();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mowing.out")));
        fout.println(answer);
        fout.close();
    }

    long doDP() {
        // Sort solutions by most flowers passed
        TreeMap<Integer, HashSet<Sol>> solutions = new TreeMap<>((a, b) -> { return b - a; });
        solutions.put(0, new HashSet<>(1));
        solutions.get(0).add(new Sol(0, 0, 0));
        long answer = -1;
        for (Point f : flowers) {
            int bound = solutions.size();
            long minValue = INF;
            int mostFlowers = -1;
            for (Map.Entry<Integer, HashSet<Sol>> entry : solutions.entrySet()) {
                if (mostFlowers > entry.getKey()) break;
                for (Sol sol : entry.getValue()) {
                    if (sol.y > f.y) continue;
                    minValue = Math.min(sol.v + (long) (f.x - sol.x) * (f.y - sol.y), minValue);
                    mostFlowers = Math.max(entry.getKey(), mostFlowers);
                }
            }
            if (solutions.get(mostFlowers + 1) == null) solutions.put(mostFlowers + 1, new HashSet<>());
            solutions.get(mostFlowers + 1).add(new Sol(f.x, f.y, minValue));
            if (f.x == T) answer = minValue;
        }
         System.out.println(solutions);
        return answer;
    }

    public static void main(String[] args) throws IOException {
        new mowing();
    }

    static class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Sol {
        int x, y;
        long v;
        Sol(int x, int y, long v) {
            this.x = x;
            this.y = y;
            this.v = v;
        }
        @Override
        public String toString() {
            return "Sol[" + x + ", " + y + ", " + v + "]";
        }
    }
}
