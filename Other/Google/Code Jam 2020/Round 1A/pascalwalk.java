import java.util.*;
import java.io.*;

public class pascalwalk {
    final int MAX_POW = 31;
    int[] pow2;
    int N, lastRow;
    boolean[] useRow;

    pascalwalk(BufferedReader in, PrintWriter out, int tn) throws IOException {
        pow2 = new int[MAX_POW];
        pow2[0] = 1;
        for (int i = 1; i < MAX_POW; i++) pow2[i] = pow2[i-1] * 2;
        N = Integer.parseInt(in.readLine());
        // Figure out last row of Pascal's triangle to go to
        for (int i = 1; i < MAX_POW; i++) {
            if (pow2[i] > N) {
                // This row alone would work; last row to consider
                lastRow = i;
                break;
            }
        }

        useRow = new boolean[lastRow];
        int currN = N - lastRow;
        for (int r = lastRow; r > 0; r--) {
            if (currN >= pow2[r] - 1) {
                // Use this row
                useRow[r] = true;
                currN -= pow2[r] - 1;
            }
        }

//        System.out.println("Last row: " + lastRow);
//        System.out.println(Arrays.toString(useRow));
//        System.out.println("Left over: " + currN);

        // Now, print out the walk, switching sides in the desired rows
        boolean onLeft = true;
        out.println("Case #" + tn + ":");
        out.println("1 1");
        for (int r = 1; r < lastRow; r++) {
            if (useRow[r]) {
                if (onLeft) {
                    // Go to right
                    for (int j = 0; j < r + 1; j++) out.println((r+1) + " " + (j+1));
                    onLeft = false;
                } else {
                    // Go to left
                    for (int j = r; j >= 0; j--) out.println((r+1) + " " + (j+1));
                    onLeft = true;
                }
            } else {
                // Stay on this side
                if (onLeft) out.println((r+1) + " 1");
                else out.println((r+1) + " " + (r+1));
            }
        }

        // Handle left over
        int r = lastRow;
        while (currN > 0) {
            if (onLeft) out.println((r+1) + " 1");
            else out.println((r+1) + " " + (r+1));
            currN--;
            r++;
        }

        out.flush();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new pascalwalk(in, out, i);
        in.close();
        out.close();
    }
}
