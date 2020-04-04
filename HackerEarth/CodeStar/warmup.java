package CodeStar;/*
Solution: 
*/

import java.util.*;
import java.io.*;

public class warmup {
    int N;

    warmup() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        in.close();

        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
        out.println(N*N);
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new warmup();
    }
}
