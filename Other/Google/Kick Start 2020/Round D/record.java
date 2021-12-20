import java.util.*;
import java.io.*;

public class record {
    int N;
    boolean[] isMax;
    int[] arr;

    record(BufferedReader in, PrintWriter out, int tn) throws IOException {
        N = Integer.parseInt(in.readLine());
        int currMax = -1;
        arr = new int[N];
        isMax = new boolean[N];
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(st.nextToken());
            isMax[i] = arr[i] > currMax;
            currMax = Math.max(arr[i], currMax);
        }

        int answer = 0;
        for (int i = 0; i < N-1; i++) {
            if (isMax[i] && arr[i] > arr[i+1]) answer++;
        }
        if (isMax[N-1]) answer++;
        out.printf("Case #%d: %d\n", tn, answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int t = Integer.parseInt(in.readLine());
        for (int i = 1; i <= t; i++) new record(in, out, i);
        in.close();
        out.close();
    }
}
