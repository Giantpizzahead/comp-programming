import java.util.*;
import java.io.*;

public class oddevensubseq {
    int N, K;
    int[] arr;

    oddevensubseq(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        int low = 0, high = 1_000_000_000;
        while (low < high) {
            int mid = (low + high) / 2;
            if (check(mid)) {
                high = mid;
            } else {
                low = mid + 1;
            }
        }
        out.println(low);
    }

    boolean check(int v) {
        int numTaken1 = 0, numTaken2 = 0;
        boolean lastTaken1 = false, lastTaken2 = true;
        for (int i = 0; i < N; i++) {
            if (lastTaken1) {
                numTaken1++;
                lastTaken1 = false;
            } else if (arr[i] <= v) {
                numTaken1++;
                lastTaken1 = true;
            }

            if (lastTaken2) {
                numTaken2++;
                lastTaken2 = false;
            } else if (arr[i] <= v) {
                numTaken2++;
                lastTaken2 = true;
            }
        }
        return numTaken1 >= K || numTaken2 >= K;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new oddevensubseq(in, out);
        in.close();
        out.close();
    }
}
