/*
Solution: Use a segment tree, with each node storing the max # of 4s, max # of 7s, longest NDS, and
longest NIS. To handle the switch query, change NIS into NDS and vice versa.
Runtime: O(M * log(N))
*/

import javax.swing.text.Segment;
import java.util.*;
import java.io.*;

public class lucky {
    int N, M;
    char[] initString;

    lucky(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        initString = in.readLine().toCharArray();
        SegmentTree segt = new SegmentTree(N);

        int a, b;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            if (st.nextToken().equals("count")) {
                out.println(segt.count());
                // out.flush();
            } else {
                a = Integer.parseInt(st.nextToken()) - 1;
                b = Integer.parseInt(st.nextToken()) - 1;
                segt.switchDigits(a, b);
            }
        }
    }

    class SegmentTree {
        int size;
        int[] num4, num7, nds, nis;
        boolean[] delta;  // Is switched?

        SegmentTree(int size) {
            this.size = size;
            num4 = new int[size * 4 + 1];
            num7 = new int[size * 4 + 1];
            nds = new int[size * 4 + 1];
            nis = new int[size * 4 + 1];
            delta = new boolean[size * 4 + 1];
            initTree(1, 0, size - 1);
        }

        void switchDigits(int l, int r) {
            switchDigits(1, 0, size - 1, l, r);
        }

        void switchDigits(int n, int lb, int ub, int l, int r) {
            if (lb > r || ub < l) return;
            else if (lb >= l && ub <= r) {
                switchNode(n);
                delta[n] = !delta[n];
                return;
            }

            propagate(n);
            switchDigits(n*2, lb, (lb+ub)/2, l, r);
            switchDigits(n*2+1, (lb+ub)/2+1, ub, l, r);
            merge(n);
        }

        void switchNode(int n) {
            int temp = num4[n];
            num4[n] = num7[n];
            num7[n] = temp;
            temp = nds[n];
            nds[n] = nis[n];
            nis[n] = temp;
        }

        void propagate(int n) {
            if (delta[n]) {
                delta[n*2] = !delta[n*2];
                delta[n*2+1] = !delta[n*2+1];
                switchNode(n*2);
                switchNode(n*2+1);
                delta[n] = false;
            }
        }

        int count() {
//            System.out.println(Arrays.toString(num4));
//            System.out.println(Arrays.toString(num7));
//            System.out.println(Arrays.toString(nds));
//            System.out.println(Arrays.toString(nis));
            return nds[1];
        }

        // Updates this node's results with its children's results.
        void merge(int n) {
            num4[n] = num4[n*2] + num4[n*2+1];
            num7[n] = num7[n*2] + num7[n*2+1];
            nds[n] = Math.max(nds[n*2] + num7[n*2+1], num4[n*2] + nds[n*2+1]);
            nis[n] = Math.max(nis[n*2] + num4[n*2+1], num7[n*2] + nis[n*2+1]);
        }

        void initTree(int n, int lb, int ub) {
            // System.out.println("n = " + n + ", lb = " + lb + ", ub = " + ub);
            if (lb == ub) {
                nds[n] = 1;
                nis[n] = 1;
                if (initString[lb] == '4') {
                    num4[n] = 1;
                    num7[n] = 0;
                } else {
                    num4[n] = 0;
                    num7[n] = 1;
                }
            } else {
                initTree(n*2, lb, (lb+ub)/2);
                initTree(n*2+1, (lb+ub)/2+1, ub);
                merge(n);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("lucky.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("lucky.out")));
        new lucky(in, out);
        in.close();
        out.close();
    }
}
