import java.util.*;
import java.io.*;

public class binaryrot {
    int N;
    boolean[] S, T;

    binaryrot(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        S = new boolean[N];
        T = new boolean[N];
        int num1S = 0, num1T = 0;
        String str = in.readLine();
        for (int i = 0; i < N; i++) {
            if (str.charAt(i) == '1') {
                S[i] = true;
                num1S++;
            } else S[i] = false;
        }
        str = in.readLine();
        for (int i = 0; i < N; i++) {
            if (str.charAt(i) == '1') {
                T[i] = true;
                num1T++;
            } else T[i] = false;
        }

        if (num1S != num1T) {
            out.println(-1);
            return;
        }

        for (int i = 0; i < N; i++) {
            if (S[i] && T[i]) {
                S[i] = false;
                T[i] = false;
            }
        }

        int minStack = 0, maxStack = 0, currStack = 0;
        for (int i = 0; i < N; i++) {
            if (S[i]) currStack++;
            else if (T[i]) currStack--;
            minStack = Math.min(minStack, currStack);
            maxStack = Math.max(maxStack, currStack);
        }
        out.println(maxStack - minStack);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new binaryrot(in, out);
        in.close();
        out.close();
    }
}
