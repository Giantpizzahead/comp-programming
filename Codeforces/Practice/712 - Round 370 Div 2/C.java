import java.util.*;
import java.io.*;

public class memory {
    int X, Y;

    memory(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        X = Integer.parseInt(st.nextToken());
        Y = Integer.parseInt(st.nextToken());
        if (X == Y) {
            out.println(0);
            return;
        } else if (X > Y) {
            int t = X;
            X = Y;
            Y = t;
        }

        int side1 = X, side2 = X, side3 = X, seconds = 0;
        while (side1 < Y || side2 < Y || side3 < Y) {
            if (side1 <= side2 && side2 <= side3) {
                // Side1 min
                side1 = side2 + side3 - 1;
            } else if (side2 <= side1 && side2 <= side3) {
                // Side2 min
                side2 = side1 + side3 - 1;
            } else {
                // Side3 min
                side3 = side1 + side2 - 1;
            }
            seconds++;
        }
        out.println(seconds);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new memory(in, out);
        in.close();
        out.close();
    }
}
