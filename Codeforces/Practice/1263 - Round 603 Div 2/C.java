import java.util.*;
import java.io.*;

public class winner {
    int T, N;

    winner() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            N = Integer.parseInt(in.readLine());
            Queue<Integer> valid = new LinkedList<>();
            valid.add(0);
            int toDivide = N, last = 0;
            while (last != N) {
                // System.out.println(valid.peek());
                last = N / toDivide;
                valid.add(last);
                toDivide = N / (last + 1);
            }

            out.println(valid.size());
            while (!valid.isEmpty()) {
                out.print(valid.poll());
                if (valid.isEmpty()) break;
                out.print(' ');
            }
            out.println();
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new winner();
    }
}
