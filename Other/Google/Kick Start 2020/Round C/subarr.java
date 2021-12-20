import java.util.*;
import java.io.*;

public class subarr {
    int[] arr, count;
    int N, zeroLoc;

    subarr(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        // for (int i = 0; i < N; i++) arr[i] = 100;
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        int maxNum = 200 * N;
        count = new int[maxNum + 1];
        zeroLoc = 100 * N;

        long answer = 0;
        int currMax = 0;
        for (int i = 0; i < N; i++) {
            count[zeroLoc]++;
            zeroLoc -= arr[i];
            currMax += arr[i];
            currMax = Math.max(arr[i], currMax);

            // Check all possible perfect squares
            for (int j = 0; j*j <= currMax; j++) {
                answer += count[zeroLoc + j*j];
            }
        }

        out.println("Case #" + tn + ": " + answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new subarr(in, out, i);
        in.close();
        out.close();
    }
}
