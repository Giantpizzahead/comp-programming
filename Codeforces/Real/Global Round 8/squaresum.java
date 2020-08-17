import java.util.*;
import java.io.*;

public class squaresum {
    int N;
    int[] numBits;
    long answer;

    squaresum(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        numBits = new int[20];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            int x = Integer.parseInt(st.nextToken());
            for (int j = 0; j < 20; j++) {
                if ((x & (1 << j)) != 0) numBits[j]++;
            }
        }

        answer = 0;
        boolean nonZero = true;
        while (nonZero) {
            nonZero = false;
            int x = 0;
            for (int j = 0; j < 20; j++) {
                if (numBits[j] != 0) {
                    nonZero = true;
                    numBits[j]--;
                    x += 1 << j;
                }
            }
            answer += (long) x * x;
        }

        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new squaresum(in, out);
        in.close();
        out.close();
    }
}
