import java.util.*;
import java.io.*;

public class expogo {
    int X, Y;
    StringBuilder sb;

    expogo(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        X = Integer.parseInt(st.nextToken());
        Y = Integer.parseInt(st.nextToken());
        sb = new StringBuilder();

        while (X != 0 || Y != 0) {
            // System.out.println(X + " " + Y);
            // Base cases
            if (X == 1 && Y == 0) {
                sb.append('E');
                break;
            } else if (X == -1 && Y == 0) {
                sb.append('W');
                break;
            } else if (X == 0 && Y == 1) {
                sb.append('N');
                break;
            } else if (X == 0 && Y == -1) {
                sb.append('S');
                break;
            }

            if ((Math.abs(X) % 2 == 0) == (Math.abs(Y) % 2 == 0)) {
                // Impossible
                out.println("Case #" + tn + ": IMPOSSIBLE");
                return;
            } else if (Math.abs(X) % 2 == 1) {
                // Move X depending on whether Y will be odd next turn
                if (Y % 4 == 0) {
                    // Y will be even next turn; make X odd
                    if (X % 4 == 1 || X % 4 == -3) {
                        X++;
                        sb.append('W');
                    } else {
                        X--;
                        sb.append('E');
                    }
                } else {
                    // Y will be odd next turn; make X even
                    if (X % 4 == 1 || X % 4 == -3) {
                        X--;
                        sb.append('E');
                    } else {
                        X++;
                        sb.append('W');
                    }
                }
            } else {
                // Move Y
                if (X % 4 == 0) {
                    if (Y % 4 == 1 || Y % 4 == -3) {
                        Y++;
                        sb.append('S');
                    } else {
                        Y--;
                        sb.append('N');
                    }
                } else {
                    if (Y % 4 == 1 || Y % 4 == -3) {
                        Y--;
                        sb.append('N');
                    } else {
                        Y++;
                        sb.append('S');
                    }
                }
            }
            X /= 2;
            Y /= 2;
        }
        out.println("Case #" + tn + ": " + sb.toString());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new expogo(in, out, i);
        in.close();
        out.close();
    }
}
