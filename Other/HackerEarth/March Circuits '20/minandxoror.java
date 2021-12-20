/*
The expression deduces to A ^ B. To find the min xor in the array, just sort it and try each
adjacent pair.
 */

import java.util.*;
import java.io.*;

public class minandxoror {
    int N;
    int[] arr;

    minandxoror(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        arr = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());
        Arrays.sort(arr);

        int answer = arr[0] ^ arr[1];
        for (int i = 1; i < N; i++) {
            answer = Math.min(arr[i-1] ^ arr[i], answer);
        }
        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new minandxoror(in, out);
        in.close();
        out.close();
    }
}
