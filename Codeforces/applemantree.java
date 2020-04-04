import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class applemantree {
    final int MOD = 1000000007;
    int N;
    boolean[] coloredBlack;
    int[] dpWhite, dpBlack;
    ArrayList<Integer>[] children;

    applemantree(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());

        children = new ArrayList[N];
        for (int i = 0; i < N; i++) children[i] = new ArrayList<>(2);
        st = new StringTokenizer(in.readLine());
        for (int i = 1; i < N; i++) children[Integer.parseInt(st.nextToken())].add(i);

        coloredBlack = new boolean[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) coloredBlack[i] = (Integer.parseInt(st.nextToken()) == 1);

        dpWhite = new int[N];
        dpBlack = new int[N];
        go(0);

        // System.out.println(Arrays.toString(dpWhite));
        // System.out.println(Arrays.toString(dpBlack));

        out.println(dpBlack[0]);
    }

    void go(int n) {
        for (int e : children[n]) go(e);

        if (coloredBlack[n]) {
            // All children must cut off black vertexes or extend current subtrees
            long result = 1;
            for (int e : children[n]) result = result * (dpBlack[e] + dpWhite[e]) % MOD;
            dpBlack[n] = (int) result;
            // No way to make subtree have no black nodes (this node itself is black)
            dpWhite[n] = 0;
        } else {
            // All children must cut off black vertexes for dpWhite, or extend their
            // current subtree
            long multWhite = 1;
            for (int e : children[n]) {
                multWhite = multWhite * (dpBlack[e] + dpWhite[e]) % MOD;
            }
            dpWhite[n] = (int) multWhite;

            // Exactly one child must extend black vertex for dpBlack
            long blackResult = 0;
            for (int e : children[n]) {
                blackResult += (long) moddiv((int) multWhite, (dpBlack[e] + dpWhite[e]) % MOD) * dpBlack[e] % MOD;
                blackResult %= MOD;
            }
            dpBlack[n] = (int) blackResult;
        }
    }

    int moddiv(int a, int b) {
        int inv;
        if (b == 1) inv = 1;
        else inv = modinv(MOD, b).b;
        return (int) ((long) a * inv % MOD);
    }

    Pair modinv(int a, int b) {
        int c = a / b;
        int d = a % b;
        if (d == 1) {
            // Base case
            return new Pair(1, -c + MOD);
        } else {
            Pair pair = modinv(b, d);
            int e = pair.a;
            int f = pair.b;
            int nf = (int) (((long) -c * f + e) % MOD);
            if (nf < 0) nf += MOD;
            return new Pair(f, nf);
        }
    }

    static class Pair {
        int a, b;

        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new applemantree(in, out);
        in.close();
        out.close();
    }
}