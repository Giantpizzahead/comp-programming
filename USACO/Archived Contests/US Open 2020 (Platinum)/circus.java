import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class circus {
    final int MOD = 1000000007;
    int[] factorials, maxBot;
    int N;
    ArrayList<Integer>[] adj;

    circus(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        factorials = new int[N + 1];
        factorials[0] = 1;
        for (int i = 1; i <= N; i++) factorials[i] = (int) ((long) factorials[i-1] * i % MOD);

        maxBot = new int[N + 1];
        for (int i = 1; i <= N; i++) maxBot[i] = i;

        // Evaluate all vertexes with degree > 2
        boolean evaluated = false;
        for (int i = 0; i < N; i++) {
            if (adj[i].size() >= 2) {
                evaluated = true;
                evalRoot(i);
                System.out.println(Arrays.toString(maxBot));
            }
        }

        // Finally, print the answers
        int bot = 1, bottomRate = 1, currExI = 0;
        for (int top = 1; top <= N; top++)
            out.println(moddiv(factorials[top], factorials[maxBot[top]]));
    }

    ArrayList<Integer> subtreeDepths = new ArrayList<>();
    void evalRoot(int root) {
        // Find subtree sizes
        subtreeDepths.clear();
        for (int e : adj[root]) {
            findDepth(e, root, 1);
        }
        int depthSum = 0;
        for (int d : subtreeDepths) depthSum += d;
        System.out.println(subtreeDepths);

        // Now, find sorted list of depth sums excluding one path
        ArrayList<Integer> excludeSums = new ArrayList<>();
        for (int i = 0; i < subtreeDepths.size(); i++) {
            excludeSums.add(depthSum - subtreeDepths.get(i));
        }
        Collections.sort(excludeSums);

        // Update minimum bottom
        int bot = 1, bottomRate = 1, currExI = 0;
        for (int top = 1; top <= N; top++) {
            maxBot[top] = Math.min(bot, maxBot[top]);
            // Update change rate
            while (currExI != excludeSums.size() && excludeSums.get(currExI) == top) {
                bottomRate--;
                currExI++;
            }
            bot = Math.max(bot + bottomRate, 0);
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
            Pair result = modinv(b, d);
            int e = result.a;
            int f = result.b;
            int nf = (int) (((long) -c * f + e) % MOD);
            if (nf < 0) nf += MOD;
            return new Pair(f, nf);
        }
    }

    class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    void findDepth(int n, int p, int d) {
        if (adj[n].size() == 1) {
            // Leaf node!
            subtreeDepths.add(d);
            return;
        }

        for (int e : adj[n]) {
            if (e != p) findDepth(e, n, d + 1);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("circus.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("circus.out")));
        new circus(in, out);
        in.close();
        out.close();
    }
}
