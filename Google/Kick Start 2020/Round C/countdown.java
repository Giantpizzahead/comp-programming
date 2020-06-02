import java.util.*;
import java.io.*;

public class countdown {
    int N, K;

    countdown(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        int currNum = K, numSeq = 0;
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            int x = Integer.parseInt(st.nextToken());
            if (x == currNum) {
                currNum--;
                if (currNum == 0) {
                    currNum = K;
                    numSeq++;
                }
            } else if (x == K) currNum = K-1;
            else currNum = K;
        }
        out.println("Case #" + tn + ": " + numSeq);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new countdown(in, out, i);
        in.close();
        out.close();
    }
}
