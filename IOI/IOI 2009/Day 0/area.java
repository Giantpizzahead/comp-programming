/*
Solution: Just do sum(A * b).
Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class area {
    int N;

    area() throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("area.in"));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        N = Integer.parseInt(in.readLine());
        StringTokenizer st;
        long answer = 0;
        int a, b;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            a = Integer.parseInt(st.nextToken());
            b = Integer.parseInt(st.nextToken());
            answer += a * b;
        }
        out.println(answer);
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new area();
    }
}
