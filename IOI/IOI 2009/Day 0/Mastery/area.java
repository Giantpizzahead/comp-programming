import java.util.*;
import java.io.*;

public class area {
    int N;
    long answer;

    area(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            answer += a * b;
        }
        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new area(in, out);
        in.close();
        out.close();
    }
}
