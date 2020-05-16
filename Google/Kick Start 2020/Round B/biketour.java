import java.util.*;
import java.io.*;

public class biketour {
    int N;
    int[] heights;

    biketour(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        heights = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            heights[i] = Integer.parseInt(st.nextToken());
        }

        int numPeaks = 0;
        for (int i = 1; i < N - 1; i++) {
            if (heights[i] > heights[i-1] && heights[i] > heights[i+1]) numPeaks++;
        }
        out.println("Case #" + tn + ": " + numPeaks);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new biketour(in, out, i);
        in.close();
        out.close();
    }
}
