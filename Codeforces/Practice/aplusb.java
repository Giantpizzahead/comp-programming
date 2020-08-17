/*
Solution: 

Runtime: 
*/

import java.util.*;
import java.io.*;

public class aplusb {
    long a, b;

    aplusb(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        a = Long.parseLong(st.nextToken());
        b = Long.parseLong(st.nextToken());
        // Hi
        out.println(a + b);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new aplusb(in, out);
        in.close();
        out.close();
    }
}
