import jdk.swing.interop.SwingInterOpUtils;

import java.util.*;
import java.io.*;

public class robotdecoding {
    final int MOD = 1000000000;
    String line;
    int N;

    robotdecoding(BufferedReader in, PrintWriter out, int tn) throws IOException {
        line = in.readLine();
        Result answer = parse(0);
        out.println("Case #" + tn + ": " + (answer.w+1) + " " + (answer.h+1));
        out.flush();
    }

    Result parse(int i) {
        Result curr = new Result(0, 0, i);
        while (curr.i < line.length()) {
            // System.out.println(curr.i);
            char c = line.charAt(curr.i);
            if (Character.isDigit(c)) {
                // New recursion
                Result p = parse(curr.i+2);
                curr.i = p.i;
                int times = c - '0';
                p.h = (int) ((long) p.h * times % MOD);
                p.w = (int) ((long) p.w * times % MOD);
                curr.h = (curr.h + p.h) % MOD;
                curr.w = (curr.w + p.w) % MOD;
            } else if (c == ')') {
                // End recursion
                return curr;
            } else if (c == 'N') {
                curr.h--;
                if (curr.h < 0) curr.h += MOD;
            } else if (c == 'S') {
                curr.h = (curr.h + 1) % MOD;
            } else if (c == 'W') {
                curr.w--;
                if (curr.w < 0) curr.w += MOD;
            } else {
                curr.w = (curr.w + 1) % MOD;
            }
            curr.i++;
        }
        return curr;
    }

    class Result {
        int w, h, i;
        Result(int w, int h, int i) {
            this.w = w;
            this.h = h;
            this.i = i;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new robotdecoding(in, out, i);
        in.close();
        out.close();
    }
}
