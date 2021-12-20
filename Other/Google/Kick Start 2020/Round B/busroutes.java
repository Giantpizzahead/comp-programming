import java.util.*;
import java.io.*;

public class busroutes {
    int N;
    long D;
    long[] buses;

    busroutes(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        D = Long.parseLong(st.nextToken());
        buses = new long[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) buses[i] = Long.parseLong(st.nextToken());

        // Backtrack
        for (int i = N - 1; i >= 0; i--) {
            D = D - (D % buses[i]);
        }
        out.println("Case #" + tn + ": " + D);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new busroutes(in, out, i);
        in.close();
        out.close();
    }
}
