import java.util.*;
import java.io.*;

public class numbergame {
    int N;

    numbergame(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        if (N == 1) out.println("FastestFinger");
        else if (N == 2) out.println("Ashishgup");
        else if (N % 2 == 0 && N % 4 != 0) {
            if (isPrime(N / 2)) out.println("FastestFinger");
            else out.println("Ashishgup");
        } else {
            int pow2 = 1;
            while (pow2 < N) {
                pow2 *= 2;
            }
            if (pow2 == N) out.println("FastestFinger");
            else out.println("Ashishgup");
        }
    }

    boolean isPrime(int x) {
        for (int i = 2; i < Math.min(x, (int) Math.sqrt(x) + 2); i++) {
            if (x % i == 0) return false;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new numbergame(in, out);
        in.close();
        out.close();
    }
}
