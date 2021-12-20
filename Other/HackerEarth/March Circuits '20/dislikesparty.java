import java.util.*;
import java.io.*;

public class dislikesparty {
    int N;
    HashMap<Integer, HashSet<Integer>> dislike;
    long numHandshakes;

    dislikesparty(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        dislike = new HashMap<>();
        numHandshakes = (long) N * (N - 1) / 2;
        for (int i = 0; i < 10; i++) {
            st = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(st.nextToken());
            for (int j = 0; j < 9; j++) {
                int b = Integer.parseInt(st.nextToken());
                if (a == b) continue;
                else if (dislike.containsKey(a) && dislike.get(a).contains(b)) continue;
                // Not double-counting dislike
                if (!dislike.containsKey(a)) dislike.put(a, new HashSet<>());
                dislike.get(a).add(b);
                if (!dislike.containsKey(b)) dislike.put(b, new HashSet<>());
                dislike.get(b).add(a);
                numHandshakes--;
            }
        }
        out.println(numHandshakes);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new dislikesparty(in, out);
        in.close();
        out.close();
    }
}
