import java.util.*;
import java.io.*;

public class NHAY {
    int N;
    int[] kmp;
    String needle;

    NHAY(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        kmp = new int[N];
        needle = in.readLine();
        kmp[0] = -1;
        int l = -1;
        for (int i = 1; i < N; i++) {
            while (l != -1 && needle.charAt(i) != needle.charAt(l+1)) l = kmp[l];
            if (needle.charAt(i) == needle.charAt(l+1)) l++;
            kmp[i] = l;
        }
        // System.out.println(Arrays.toString(kmp));

        boolean matchFound = false;
        int i = 0;
        l = -1;
        char c = (char) in.read();
        while (c != '\n') {
            while (l != -1 && c != needle.charAt(l + 1)) l = kmp[l];
            if (c == needle.charAt(l + 1)) l++;
            if (l == N - 1) {
                // Match found
                matchFound = true;
                out.println(i - N + 1);
                out.flush();
                l = kmp[l];
            }
            i++;
            c = (char) in.read();
        }
        if (!matchFound) out.println();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        while (in.ready()) {
            new NHAY(in, out);
        }
    }
}