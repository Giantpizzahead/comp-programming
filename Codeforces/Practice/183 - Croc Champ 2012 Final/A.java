import java.util.*;
import java.io.*;

public class headquarters {
    int N;

    headquarters(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        int currW = 1, currH = 1;
        for (int i = 0; i < N; i++) {
            String str = in.readLine();
            if (str.equals("UL") || str.equals("DR")) currH++;
            else if (str.equals("UR") || str.equals("DL")) currW++;
            else {
                currH++;
                currW++;
            }
        }
        out.println((long) currW * currH);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new headquarters(in, out);
        in.close();
        out.close();
    }
}
