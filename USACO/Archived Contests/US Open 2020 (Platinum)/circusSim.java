import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class circusSim {
    final int MOD = 1000000007;
    int N;
    HashSet<Long> visited;
    ArrayList<Integer>[] adj;

    circusSim(BufferedReader in, PrintWriter out) throws IOException {
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
        new circusSim(in, out);
        in.close();
        out.close();
    }
}
