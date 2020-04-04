import java.util.*;
import java.io.*;

public class word {
    int N, K;

    word(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        int currLength = 0;
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            String word = st.nextToken();
            if (currLength + word.length() > K) {
                out.println();
                currLength = 0;
            } else if (i != 0) out.print(' ');
            currLength += word.length();
            out.print(word);
        }
        out.println();
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("word.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("word.out")));
        new word(in, out);
        in.close();
        out.close();
    }
}