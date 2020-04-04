/*
Solution: Segment tree.
Runtime: O(N * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

public class deepuArray {
    int N, M;
    int[] arr, arrToSorted;
    Integer[] sortArr;
    SegmentTree segt;

    deepuArray(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        sortArr = new Integer[N];
        for (int i = 0; i < N; i++) sortArr[i] = i;
        Arrays.sort(sortArr, Comparator.comparingInt(a -> arr[a]));

        arrToSorted = new int[N];
        for (int i = 0; i < N; i++) arrToSorted[sortArr[i]] = i;

        int[] inputArr = new int[N];
        for (int i = 0; i < N; i++) inputArr[i] = arr[sortArr[i]];

        segt = new SegmentTree(inputArr);
        M = Integer.parseInt(in.readLine());
        // printArr(out);
        int X;
        for (int i = 0; i < M; i++) {
            X = Integer.parseInt(in.readLine());
            segt.hit(X);
            // printArr(out);
        }

        printArr(out);
    }

    void printArr(PrintWriter out) {
        for (int i = 0; i < N; i++) {
            if (i != 0) out.print(' ');
            out.print(segt.query(arrToSorted[i]));
        }
        out.println();
    }

    class SegmentTree {
        int size;
        int[] vals, delta, initArr;

        SegmentTree(int[] initArr) {
            this.size = initArr.length;
            vals = new int[size * 4 + 1];
            delta = new int[size * 4 + 1];
            this.initArr = initArr;
            initTree(1, 0, size - 1);
        }

        void hit(int x) {
            hit(1, 0, size - 1, x);
        }

        void hit(int n, int lb, int ub, int x) {
            if (lb == ub) {
                if (vals[n] > x) {
                    // This is hit
                    vals[n]--;
                }
                return;
            }
            propagate(n);
            if (vals[n*2] <= x) {
                // Max in left is not hit; only in right
                hit(n*2+1, (lb+ub)/2+1, ub, x);
            } else {
                // At least 1 element in left is hit, so right is completely hit
                vals[n*2+1]--;
                delta[n*2+1]--;
                hit(n*2, lb, (lb+ub)/2, x);
            }
            vals[n] = Math.max(vals[n*2], vals[n*2+1]);
        }

        int query(int i) {
            return query(1, 0, size - 1, i);
        }

        int query(int n, int lb, int ub, int i) {
            if (lb == ub) return vals[n];

            propagate(n);
            if (i > (lb+ub)/2) return query(n*2+1, (lb+ub)/2+1, ub, i);
            else return query(n*2, lb, (lb+ub)/2, i);
        }

        void propagate(int n) {
            if (delta[n] != 0) {
                vals[n*2] += delta[n];
                vals[n*2+1] += delta[n];
                delta[n*2] += delta[n];
                delta[n*2+1] += delta[n];
                delta[n] = 0;
            }
        }

        void initTree(int n, int lb, int ub) {
            if (lb == ub) {
                vals[n] = initArr[lb];
            } else {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
                vals[n] = Math.max(vals[n*2], vals[n*2+1]);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("deepuArray.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("deepuArray.out")));
        new deepuArray(in, out);
        in.close();
        out.close();
    }
}
