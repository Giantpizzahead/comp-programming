/*
Solution: Math. If you draw out the problem a bit, it's basically asking to find the # of positive area rectangles
that can fit inside a jagged \-like shape. Formulas and stuff will get you an N * log(N) way of calculating this.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class sprinklersOld {
    int N;
    int[] minY, maxY;
    final long MOD = 1000000007;

    sprinklersOld() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sprinklers.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        minY = new int[N];
        maxY = new int[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            minY[x] = y;
            maxY[x] = y;
        }
        fin.close();

        // Find the min and max Y's using 2 sweeps
        int currMinY = minY[0];
        for (x = 0; x < N; x++) {
            currMinY = Math.min(minY[x], currMinY);
            minY[x] = currMinY;
        }
        int currMaxY = maxY[N-1];
        for (x = N-1; x >= 0; x--) {
            currMaxY = Math.max(maxY[x], currMaxY);
            maxY[x] = currMaxY - 1;
        }

        // System.out.println(Arrays.toString(minY));
        // System.out.println(Arrays.toString(maxY));

        // Do quick maths
        long answer = quickMaths();

        PrintWriter fout = new PrintWriter("sprinklers.out");
        fout.println(answer);
        fout.close();
    }

    long quickMaths() {
        int[] startLoc = new int[N];
        Arrays.fill(startLoc, -1);
        long ySum = 0, answer = 0;
        SegmentTree rectSums = new SegmentTree(N);
        int cMinY = N - 1, cMaxY = maxY[0];
        for (int x = 0; x < N; x++) {
            while (cMaxY != maxY[x]) {
                // Remove from ySum
                if (startLoc[cMaxY] != -1) ySum -= (x - startLoc[cMaxY]) * cMaxY;
                ySum %= MOD;
                cMaxY--;
            }
            if (ySum < 0) ySum += MOD;
            while (x != 0 && cMinY != minY[x-1]) {
                startLoc[--cMinY] = x;
            }

            if (cMinY <= cMaxY) {
                // Add to ySum
                ySum += ((long) cMaxY * cMaxY - (long) cMinY * cMinY + cMaxY + cMinY) / 2;
                ySum %= MOD;

                // Add new range
                rectSums.add(cMinY, cMaxY, (cMaxY - cMinY + 1) - cMaxY);

                // Add to answer
                answer += rectSums.query(cMinY, cMaxY) + ySum;
                answer %= MOD;
            }

//            System.out.println(cMinY + " " + cMaxY + " " + rectSums.query(cMinY, cMaxY) + " " + ySum);
//            System.out.println(Arrays.toString(startLoc));
//            System.out.println("Answer: " + answer);
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        new sprinklersOld();
    }

    class SegmentTree {
        int size;
        long[] vals;
        long[] delta;

        SegmentTree(int size) {
            this.size = size;
            vals = new long[size * 4 + 1];
            delta = new long[size * 4 + 1];
        }

        void add(int low, int high, int v) {
            if (v < 0) v += MOD;
            add(1, 0, size - 1, low, high, v);
        }

        void add(int n, int lb, int ub, int low, int high, int v) {
            if (lb > high || ub < low) return;
            else if (lb >= low && ub <= high) {
                delta[n] += v;
                delta[n] %= MOD;
                return;
            }

            propagate(n, lb, ub);
            add(n*2, lb, (lb + ub) / 2, low, high, v);
            add(n*2+1, (lb + ub) / 2 + 1, ub, low, high, v);
            vals[n] = calc(n*2, lb, (lb+ub)/2) + calc(n*2+1, (lb+ub)/2+1, ub);
        }

        long query(int low, int high) {
            return query(1, 0, size - 1, low, high);
        }

        long query(int n, int lb, int ub, int low, int high) {
            if (lb > high || ub < low) return 0;
            else if (lb >= low && ub <= high) {
                return calc(n, lb, ub);
            }

            propagate(n, lb, ub);
            return (query(n*2, lb, (lb+ub)/2, low, high) + query(n*2+1, (lb+ub)/2+1, ub, low, high)) % MOD;
        }

        void propagate(int n, int lb, int ub) {
            delta[n*2] += delta[n];
            delta[n*2+1] += delta[n];
            vals[n] = calc(n, lb, ub);
            delta[n] = 0;
        }

        long calc(int n, int lb, int ub) {
            return (vals[n] + delta[n] * (ub - lb + 1)) % MOD;
        }
    }
}
