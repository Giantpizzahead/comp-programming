import java.util.*;
import java.io.*;

public class skateboard {
    char[] str;

    skateboard(BufferedReader in, PrintWriter out) throws IOException {
        str = in.readLine().toCharArray();
        int prev2 = 0, prev = str[0] - '0';
        long ans = 0;
        for (int i = 1; i < str.length; i++) {
            prev2 = prev;
            prev = str[i] - '0';
            int last2 = prev2 * 10 + prev;
            // System.out.println(last2);
            if (last2 % 4 == 0) ans += i;
        }

        // Count 1-length divisible by 4
        for (int i = 0; i < str.length; i++) {
            int num = str[i] - '0';
            if (num % 4 == 0) ans++;
        }
        out.println(ans);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new skateboard(in, out);
        in.close();
        out.close();
    }
}
