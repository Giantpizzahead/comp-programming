import java.util.*;
import java.io.*;

public class naming {
    final int INF = 987654321;
    String C, J;
    int[][] dp, from;

    naming(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        C = st.nextToken();
        J = st.nextToken();

        dp = new int[C.length() + 1][J.length() + 1];
        from = new int[C.length() + 1][J.length() + 1];
        for (int i = 0; i <= C.length(); i++) Arrays.fill(dp[i], INF);
        dp[0][0] = 0;
        for (int i = 0; i <= C.length(); i++) {
            for (int j = 0; j <= J.length(); j++) {
                if (i != 0) {
                    if (dp[i-1][j] + 1 < dp[i][j]) {
                        dp[i][j] = dp[i-1][j] + 1;
                        from[i][j] = 1;
                    }
                }
                if (j != 0) {
                    if (dp[i][j-1] + 1 < dp[i][j]) {
                        dp[i][j] = dp[i][j-1] + 1;
                        from[i][j] = 2;
                    }
                }
                if (i != 0 && j != 0) {
                    int ec;
                    if (C.charAt(i-1) == J.charAt(j-1)) ec = 0;
                    else ec = 1;
                    if (dp[i-1][j-1] + ec < dp[i][j]) {
                        dp[i][j] = dp[i - 1][j - 1] + ec;
                        from[i][j] = 3;
                    }
                }
            }
        }

        // Find midpoint of edit distance
        int editDist = dp[C.length()][J.length()];
        int mid = editDist / 2;
        String str = C;
        // Go backwards until at midpoint
        int currI = C.length(), currJ = J.length();
        while (dp[currI][currJ] != mid) {
            // System.out.println(str);
            int currFrom = from[currI][currJ];
            if (currFrom == 1) {
                // Delete from i
                // System.out.println("del");
                str = str.substring(0, currI - 1) + str.substring(currI);
                currI--;
            } else if (currFrom == 2) {
                // Insert to i
                // System.out.println("ins");
                str = str.substring(0, currI) + J.charAt(currJ - 1) + str.substring(currI);
                currJ--;
            }
            else if (currFrom == 3) {
                // Replace in i
                // System.out.println("repl");
                str = str.substring(0, currI - 1) + J.charAt(currJ - 1) + str.substring(currI);
                currI--;
                currJ--;
            }
        }
        System.out.printf("Case #%d: %s\n", tn, str);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new naming(in, out, i);
        in.close();
        out.close();
    }
}
