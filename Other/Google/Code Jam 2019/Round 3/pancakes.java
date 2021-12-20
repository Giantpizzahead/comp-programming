import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.StringTokenizer;

public class pancakes {
    final long MOD = 1000000007;
    int S;
    long[] arr, pre;

    pancakes(BufferedReader in, int tn) throws IOException {
        S = Integer.parseInt(in.readLine());
        arr = new long[S];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < S; i++) arr[i] = Integer.parseInt(st.nextToken());
        pre = new long[S];
        pre[0] = arr[0];
        for (int i = 1; i < S; i++) {
            pre[i] = pre[i-1] + arr[i];
        }
    }

    long sumOfRange(int l, int r) {
        return pre[r] - (l == 0 ? 0 : pre[l-1]);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new pancakes(in, i);
        in.close();
    }
}
