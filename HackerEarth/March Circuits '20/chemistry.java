import java.util.*;
import java.io.*;

public class chemistry {
    int x, y, p, q;

    chemistry(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        x = Integer.parseInt(st.nextToken());
        y = Integer.parseInt(st.nextToken());
        p = Integer.parseInt(st.nextToken());
        q = Integer.parseInt(st.nextToken());
        long b3 = x * y;
        long b1 = b3 * p / x;
        long b2 = b3 * q / y;
        long gcf = findGCF(findGCF(b1, b2), b3);
        b1 /= gcf;
        b2 /= gcf;
        b3 /= gcf;
        out.printf("%d %d %d\n", b1, b2, b3);
    }

    long findGCF(long a, long b) {
        if (a == 0) return b;
        return findGCF(b % a, a);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new chemistry(in, out);
        in.close();
        out.close();
    }
}
