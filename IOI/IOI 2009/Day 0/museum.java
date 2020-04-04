/*
Solution: You can solve this problem using divide and conquer. First, split the vases into even and odd vases. Even and
odd vases will never block any vase in between, since the average of those is a decimal. So, you can split the problem
up there. Also, (1, 3, ..) can be reduced to (1, 2, ..), since the solution is the same. (2, 4, ..) becomes (1, 2, ..).
In this way, you can solve the problem for any N.

The simplest way to take advantage of this is calculating the answer for all N from 1 to the target, then printing out
the final answer.

Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class museum {
    int N = 2000;
    int[][] sols;

    museum() {
        sols = new int[N + 1][];
        sols[1] = new int[1];
        sols[1][0] = 1;
        for (int n = 2; n <= N; n++) {
            sols[n] = new int[n];
            // Split into 2 problems
            int left = (n + 1) / 2, right = n / 2;
            for (int j = 0; j < left; j++) {
                sols[n][j] = sols[left][j] * 2 - 1;
            }
            for (int j = 0; j < right; j++) {
                sols[n][left + j] = sols[right][j] * 2;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        museum m = new museum();
        for (int i = 1; i <= 5; i++) {
            BufferedReader fin = new BufferedReader(new FileReader("museum." + i + ".in"));
            PrintWriter fout = new PrintWriter("museum." + i + ".out");
            int target = Integer.parseInt(fin.readLine());
            for (int j = 0; j < m.sols[target].length; j++) {
                fout.println(m.sols[target][j]);
            }
            fout.close();
        }
    }
}
