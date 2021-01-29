import java.util.*;
import java.io.*;

public class photoremember {
    int N;
    int[] w, h;

    photoremember(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        w = new int[N];
        h = new int[N];
        int wSum = 0, maxH1 = -1, maxH2 = -1;
        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            w[i] = Integer.parseInt(st.nextToken());
            h[i] = Integer.parseInt(st.nextToken());
            wSum += w[i];
            if (h[i] >= maxH1) {
                maxH2 = maxH1;
                maxH1 = h[i];
            } else if (h[i] > maxH2) {
                maxH2 = h[i];
            }
        }

        for (int i = 0; i < N; i++) {
            if (i != 0) out.print(' ');
            int ans = (wSum - w[i]);
            if (maxH1 == h[i]) ans *= maxH2;
            else ans *= maxH1;
            out.print(ans);
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new photoremember(in, out);
        in.close();
        out.close();
    }
}