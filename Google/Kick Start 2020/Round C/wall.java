import java.util.*;
import java.io.*;

public class wall {
    int R, C;
    boolean[] available;
    StringBuilder sb;
    int[][] wall;
    boolean[][] filled;

    wall(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        wall = new int[R][C];
        filled = new boolean[R][C];
        available = new boolean[26];
        for (int i = 0; i < R; i++) {
            char[] str = in.readLine().toCharArray();
            for (int j = 0; j < C; j++) {
                wall[i][j] = str[j] - 'A';
                available[wall[i][j]] = true;
            }
        }

        int numAvailable = 0;
        for (int i = 0; i < 26; i++) if (available[i]) numAvailable++;
        sb = new StringBuilder();
        outerLoop:
        while (numAvailable > 0) {
            pieceSelection:
            for (int p = 0; p < 26; p++) {
                if (available[p]) {
                    // Can this be placed next?
                    for (int i = 0; i < R; i++) {
                        for (int j = 0; j < C; j++) {
                            if (wall[i][j] == p && i != R-1 && wall[i+1][j] != p && !filled[i+1][j]) {
                                // Cannot be used
                                continue pieceSelection;
                            }
                        }
                    }
                    // Can be placed!
                    // System.out.println(p);
                    available[p] = false;
                    sb.append((char) (p + 'A'));
                    numAvailable--;
                    for (int i = 0; i < R; i++) {
                        for (int j = 0; j < C; j++) {
                            if (wall[i][j] == p) filled[i][j] = true;
                        }
                    }
                    continue outerLoop;
                }
            }
            // Impossible (got to end of loop)
            out.println("Case #" + tn + ": -1");
            return;
        }
        out.println("Case #" + tn + ": " + sb.toString());
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new wall(in, out, i);
        in.close();
        out.close();
    }
}
