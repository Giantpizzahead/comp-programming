import java.util.*;
import java.io.*;

public class lamps {
    int N, M;
    String[] strings;
    int[] numWithLamp;

    lamps(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        strings = new String[N];
        numWithLamp = new int[M];
        for (int i = 0; i < N; i++) {
            strings[i] = in.readLine();
            for (int j = 0; j < M; j++) {
                if (strings[i].charAt(j) == '1') numWithLamp[j]++;
            }
        }

        outer:
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (strings[i].charAt(j) == '1' && numWithLamp[j] == 1) {
                    // Cannot ignore
                    continue outer;
                }
            }
            out.println("YES");
            return;
        }
        out.println("NO");
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new lamps(in, out);
        in.close();
        out.close();
    }
}
