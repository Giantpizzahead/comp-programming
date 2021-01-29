import java.util.*;
import java.io.*;

public class seabattle {
    int w1, h1, w2, h2;

    seabattle(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        w1 = Integer.parseInt(st.nextToken());
        h1 = Integer.parseInt(st.nextToken());
        w2 = Integer.parseInt(st.nextToken());
        h2 = Integer.parseInt(st.nextToken());
        long botArea = (long) (h1 + 2) * (w1 + 2);
        long topArea = (long) (h2 + 2) * (w2 + 2);
        long overlapArea = 2 * (w2 + 2);
        long shipAreas = (long) h1 * w1 + (long) h2 * w2;
        long answer = botArea + topArea - overlapArea - shipAreas;
        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new seabattle(in, out);
        in.close();
        out.close();
    }
}
