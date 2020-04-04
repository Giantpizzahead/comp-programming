import java.util.*;
import java.io.*;

public class allocation {
    int N, B;
    int[] count;

    allocation(BufferedReader in, PrintWriter out, int t) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        count = new int[1001];
        for (int i = 0; i < N; i++) count[Integer.parseInt(st.nextToken())]++;

        int num = 0;
        for (int i = 1; i < 1001; i++) {
            if (count[i] * i <= B) {
                B -= count[i] * i;
                num += count[i];
            } else {
                int maxBuy = B / i;
                num += maxBuy;
                break;
            }
        }
        out.println("Case #" + (t+1) + ": " + num);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new allocation(in, out, i);
        in.close();
        out.close();
    }
}
