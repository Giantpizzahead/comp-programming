import java.util.*;
import java.io.*;

public class painting {
    int N;
    int[] arr;

    painting(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());
        int answer = paint(0, N-1, 0);
        out.println(answer);
    }

    int paint(int l, int r, int currHeight) {
        // System.out.println("l = " + l + ", r = " + r + ", currHeight = " + currHeight);
        if (l == r) return 1;
        else if (l > r) return 0;

        int strokes = 0;
        while (currHeight < 5010) {
            // Paint one level higher
            int newHeight = currHeight + 1;
            strokes++;
            ArrayList<Integer> splitPoints = new ArrayList<>();
            for (int i = l; i <= r; i++) {
                if (arr[i] == newHeight) {
                    // Splits up into two areas
                    splitPoints.add(i);
                }
            }

            if (splitPoints.size() != 0) {
                // Split up and continue calculations
                int last = l;
                for (int s : splitPoints) {
                    strokes += paint(last, s-1, newHeight);
                    last = s + 1;
                }
                strokes += paint(last, r, newHeight);
                return Math.min(r-l+1, strokes);
            }
            currHeight = newHeight;
        }

        // Didn't finish coloring, just individually color range
        return r-l+1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new painting(in, out);
        in.close();
        out.close();
    }
}
