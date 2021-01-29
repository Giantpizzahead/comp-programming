import java.util.*;
import java.io.*;

public class subseq {
    long K, powRes;
    String str = "codeforces";

    subseq(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        K = Long.parseLong(st.nextToken());
        int currPow = 1;
        powRes = 1;
        while (powRes < K) {
            currPow++;
            powRes = 1;
            for (int i = 0; i < 10; i++) powRes *= currPow;
        }

        for (int i = 0; i < 10; i++) {
            if (powRes / currPow * (currPow - 1) >= K) {
                powRes = powRes / currPow * (currPow - 1);
                out.print(str.substring(i, i+1).repeat(currPow-1));
            } else {
                out.print(str.substring(i, i+1).repeat(currPow));
            }
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new subseq(in, out);
        in.close();
        out.close();
    }
}
