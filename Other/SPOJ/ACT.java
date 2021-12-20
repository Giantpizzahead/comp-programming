/*
Solution: This problem contains sooooo much unnecessary information. The whole thing can be ignored. Just print the
last character of the winners.

Runtime: O(1)
*/

import java.util.*;
import java.io.*;

public class ACT {
    int T, N;

    ACT() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            String line = in.readLine();
            System.out.println(line.charAt(line.length() - 1));
        }
        in.close();
    }

    public static void main(String[] args) throws IOException {
        new ACT();
    }
}
