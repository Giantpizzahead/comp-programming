import java.util.*;
import java.io.*;

public class candies {
    int N, Q;
    SegmentTree segAlt, segSum;

    candies(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        segAlt = new SegmentTree(N);
        segSum = new SegmentTree(N);
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            long x = Integer.parseInt(st.nextToken());
            if (i % 2 == 0) {
                // Positive
                segAlt.update(i, x * (i + 1));
                segSum.update(i, x);
            } else {
                // Negative
                segAlt.update(i, -x * (i + 1));
                segSum.update(i, -x);
            }
        }

        long sum = 0;
        char c;
        int a, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            c = st.nextToken().charAt(0);
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken());
            if (c == 'U') {
                if (a % 2 == 0) {
                    // Positive
                    segAlt.update(a, b * (a + 1));
                    segSum.update(a, b);
                } else {
                    // Negative
                    segAlt.update(a, -b * (a + 1));
                    segSum.update(a, -b);
                }
            } else {
                b--;
                long result = segAlt.query(a, b);
                result -= segSum.query(a, b) * a;
                if (a % 2 == 1) result *= -1;  // First term should be positive
                // System.out.println(result);
                sum += result;
            }
        }

        out.println("Case #" + tn + ": " + sum);
    }

    class SegmentTree {
        int size;
        long[] arr;

        SegmentTree(int size) {
            this.size = size;
            arr = new long[size * 4 + 1];
        }

        void update(int i, long v) {
            update(1, 0, size - 1, i, v);
        }

        void update(int n, int lb, int ub, int i, long v) {
            if (lb == ub) {
                arr[n] = v;
                return;
            }

            if (i > (lb+ub)/2) update(n*2+1, (lb+ub)/2+1, ub, i, v);
            else update(n*2, lb, (lb+ub)/2, i, v);
            arr[n] = arr[n*2] + arr[n*2+1];
        }

        long query(int l, int r) {
            return query(1, 0, size - 1, l, r);
        }

        long query(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return 0;
            else if (lb >= l && ub <= r) return arr[n];

            return query(n*2, lb, (lb+ub)/2, l, r) + query(n*2+1, (lb+ub)/2+1, ub, l, r);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new candies(in, out, i);
        in.close();
        out.close();
    }
}
