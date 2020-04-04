/*
Solution: Count the # of Os in the numbers.
*/

import java.util.*;
import java.io.*;

public class PROBLEM {
    int T;
    int[] vals = {1, 0, 0, 0, 0, 0, 1, 0, 2, 1};

    PROBLEM() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            char[] line = in.readLine().toCharArray();
            int sum = 0;
            for (char c : line) {
                sum += vals[c - '0'];
            }
            out.println(sum);
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new PROBLEM();
    }
}
