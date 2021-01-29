/*
Solution: Use a 2D BIT to process each query in log(N)^2. arr[i][j] = 1 if element at index i in
permutation a is at index j in permutation b. Allocate memory on-demand to avoid issues.
Runtime: O(N * log(M)^2)
*/

import java.util.*;
import java.io.*;

public class permutations {
    int N, M;
    int[] bLocToCurrALoc;

    permutations(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        int[] elementToALoc = new int[N + 1];
        bLocToCurrALoc = new int[N + 1];
        st = new StringTokenizer(in.readLine());
        for (int i = 1; i <= N; i++) {
            elementToALoc[Integer.parseInt(st.nextToken())] = i;
        }
        st = new StringTokenizer(in.readLine());
        for (int i = 1; i <= N; i++) {
            bLocToCurrALoc[i] = elementToALoc[Integer.parseInt(st.nextToken())];
        }

        BIT2D bit2d = new BIT2D();
        // System.out.println(Arrays.toString(bLocToCurrALoc));
        for (int i = 1; i <= N; i++) bit2d.add(bLocToCurrALoc[i], i);
        int a, b, c, d, e;
        // Handle queries
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            c = Integer.parseInt(st.nextToken());
            if (a == 1) {
                // Calculate
                d = Integer.parseInt(st.nextToken());
                e = Integer.parseInt(st.nextToken());
                out.println(bit2d.query(b, c, d, e));
                // out.flush();
            } else {
                // Swap
                bit2d.remove(bLocToCurrALoc[b], b);
                bit2d.remove(bLocToCurrALoc[c], c);
                bit2d.add(bLocToCurrALoc[b], c);
                bit2d.add(bLocToCurrALoc[c], b);
                int temp = bLocToCurrALoc[b];
                bLocToCurrALoc[b] = bLocToCurrALoc[c];
                bLocToCurrALoc[c] = temp;
                // System.out.println(Arrays.toString(bLocToCurrALoc));
            }
        }
    }

    class BIT2D {
        int size;
        BIT[] vals;

        BIT2D() {
            size = N;
            vals = new BIT[size + 1];
            for (int i = 1; i <= size; i++) vals[i] = new BIT(Integer.lowestOneBit(i));
        }

        void add(int a, int b) {
            while (a <= size) {
                vals[a].add(b);
                a += Integer.lowestOneBit(a);
            }
        }

        void remove(int a, int b) {
            while (a <= size) {
                vals[a].remove(b);
                a += Integer.lowestOneBit(a);
            }
        }

        int query(int al, int ar, int bl, int br) {
            return query0(ar, bl, br) - ((al == 1) ? 0 : query0(al-1, bl, br));
        }

        int query0(int a, int bl, int br) {
            int res = 0;
            while (a > 0) {
                res += vals[a].query(bl, br);
                a -= Integer.lowestOneBit(a);
            }
            return res;
        }
    }

    class BIT {
        final int MAX_NUM = 256;
        boolean isBIT;
        int size;
        int[] vals;
        ArrayList<Integer> points;

        BIT(int num) {
            this.size = N;
            if (num > MAX_NUM) {
                isBIT = true;
                vals = new int[size + 1];
            } else {
                points = new ArrayList<>();
            }
        }

        void add(int i) {
            if (isBIT) {
                while (i <= size) {
                    vals[i]++;
                    i += Integer.lowestOneBit(i);
                }
            } else {
                points.add(i);
            }
        }

        void remove(int i) {
            if (isBIT) {
                while (i <= size) {
                    vals[i]--;
                    i += Integer.lowestOneBit(i);
                }
            } else {
                points.remove((Integer) i);
            }
        }

        int query(int l, int r) {
            return query0(r) - ((l == 1) ? 0 : query0(l-1));
        }

        int query0(int i) {
            int res = 0;
            if (isBIT) {
                while (i > 0) {
                    res += vals[i];
                    i -= Integer.lowestOneBit(i);
                }
            } else {
                for (int p : points) {
                    if (p <= i) res++;
                }
            }
            return res;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("permutations.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("permutations.out")));
        new permutations(in, out);
        in.close();
        out.close();
    }
}
