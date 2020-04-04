import java.util.*;
import java.io.*;

public class workout {
    int N, K;
    int[] diffs;

    workout(BufferedReader in, PrintWriter out, int t) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        diffs = new int[N-1];
        st = new StringTokenizer(in.readLine());
        int prevMinutes = Integer.parseInt(st.nextToken()), currMinutes;
        for (int i = 0; i < N-1; i++) {
            currMinutes = Integer.parseInt(st.nextToken());
            diffs[i] = currMinutes - prevMinutes;
            prevMinutes = currMinutes;
        }

        // Binary search on y (will it work with <= K sessions added?)
        int low = 1, high = 1000000000;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        out.println("Case #" + (t+1) + ": " + low);
    }
    
    boolean check(int targetDiff) {
        int numAdded = 0;
        for (int diff : diffs) {
            if (diff > targetDiff) {
                // Must add at least 1 session here
                int numToAdd = (diff - 1) / targetDiff;
                numAdded += numToAdd;
            }
            if (numAdded > K) return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new workout(in, out, i);
        in.close();
        out.close();
    }
}
