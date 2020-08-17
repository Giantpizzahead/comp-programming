import java.util.*;
import java.io.*;

public class cplusequals {
    int A, B, N;

    cplusequals(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        A = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        int numMoves = 0;
        while (A <= N && B <= N) {
            numMoves++;
            if (A <= B) A += B;
            else B += A;
        }
        out.println(numMoves);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new cplusequals(in, out);
        in.close();
        out.close();
    }
}
