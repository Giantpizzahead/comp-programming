import java.io.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.StringTokenizer;

@SuppressWarnings("unchecked")
public class circusMerged {
    final int MOD = 1000000007;
    int[] factorials;
    int N;
    ArrayList<Integer>[] adj;

    circusMerged(BufferedReader in, PrintWriter out) throws IOException {
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

        if (N > 10) {
            // Star method
            factorials = new int[N + 1];
            factorials[0] = 1;
            for (int i = 1; i <= N; i++) factorials[i] = (int) ((long) factorials[i - 1] * i % MOD);

            // Find vertex without degree 2
            int root = -1;
            for (int i = 0; i < N; i++) {
                if (adj[i].size() > 2) {
                    root = i;
                    break;
                }
            }

            if (root == -1) {
                // Special case; print all factorials
                for (int i = 1; i <= N; i++) out.println(factorials[i]);
                return;
            }

            // Find path depths
            ArrayList<Integer> pathDepths = new ArrayList<>();
            int depthSum = 0;
            for (int e : adj[root]) {
                depth = 0;
                findDepth(e, root);
                pathDepths.add(depth);
                depthSum += depth;
            }

            // Now, find sorted list of depth sums excluding one path
            ArrayList<Integer> excludeSums = new ArrayList<>();
            for (int i = 0; i < pathDepths.size(); i++) {
                excludeSums.add(depthSum - pathDepths.get(i));
            }
            Collections.sort(excludeSums);

            // Finally, print the answers
            int bot = 1, bottomRate = 1, currExI = 0;
            for (int top = 1; top <= N; top++) {
                out.println(moddiv(factorials[top], factorials[bot]));
                // Update change rate
                while (currExI != excludeSums.size() && excludeSums.get(currExI) == top) {
                    bottomRate--;
                    currExI++;
                }
                bot = Math.max(bot + bottomRate, 0);
            }
        } else {
            bruteForce(out);
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

    int depth = 0;
    void findDepth(int n, int p) {
        depth++;
        for (int e : adj[n]) {
            if (e != p) findDepth(e, n);
        }
    }

    HashSet<Long> visited;
    void bruteForce(PrintWriter out) {
        // Do a BFS-like thing
        visited = new HashSet<>();
        answer = new int[N + 1];
        currLocs = new int[N];
        used = new boolean[N];
        genAllLocs(0);

        for (int i = 1; i <= N; i++) out.println(answer[i]);
    }

    int[] answer;
    int[] currLocs;
    boolean[] used;
    void genAllLocs(int i) {
        if (i != 0) {
            // BFS from this location
            long hash = hash(currLocs);
            if (!visited.contains(hash)) {
                answer[i]++;
                bfs(hash);
            }
        }
        for (int j = 0; j < N; j++) {
            if (!used[j]) {
                used[j] = true;
                currLocs[i] = j+1;
                genAllLocs(i+1);
                used[j] = false;
                currLocs[i] = 0;
            }
        }
    }

    void bfs(long hash) {
        if (visited.contains(hash)) return;  // Already visited
        visited.add(hash);
        int[] locs = decode(hash);
        // System.out.println(Arrays.toString(locs));

        // Try moving each cow
        for (int i = 0; i < N; i++) {
            if (locs[i] == 0) break;  // No more cows to move

            for (int e : adj[locs[i]-1]) {
                // Is this space open?
                boolean isOpen = true;
                for (int j = 0; j < N; j++) {
                    if (locs[j]-1 == e) {
                        isOpen = false;
                        break;
                    }
                }
                if (isOpen) {
                    // Try this state!
                    int[] newLocs = new int[N];
                    for (int j = 0; j < N; j++) {
                        if (j == i) newLocs[j] = e+1;
                        else newLocs[j] = locs[j];
                    }
                    bfs(hash(newLocs));
                }
            }
        }
    }

    long hash(int[] locs) {
        long pow = 1, hash = 0;
        for (int i = 0; i < N; i++) {
            hash += locs[i] * pow;
            pow *= N + 1;
        }
        return hash;
    }

    int[] decode(long hash) {
        int[] locs = new int[N];
        for (int i = 0; i < N; i++) {
            locs[i] = (int) (hash % (N + 1));
            hash /= (N + 1);
        }
        return locs;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("circus.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("circus.out")));
        new circusMerged(in, out);
        in.close();
        out.close();
    }
}
