/*
ID: sunnyky1
LANG: JAVA
TASK: nuggets

Solution: If M nuggets can be purchased, then M + i nuggets can also be purchased (where
i is the # of nuggets in any kind of box). So, this suggests that the minimum # of
nuggets will form a cycle of length [# nuggets in that box]. Therefore, the maximum
impossible number cannot be greater than 256^2 (since all the cycle values would be
filled by then). So, you only need to search up to 65536. Just try transitioning from
all 10 box types. If it goes over 65536, then there is no bound to the number.
Runtime: O(655360)
*/

import javax.swing.event.MenuKeyListener;
import java.util.*;
import java.io.*;

public class nuggets {
    final int MAX_CHECK = 65537 + 1000;
    int N, maxImpossible = 0;
    int[] sizes;
    boolean[] possible = new boolean[MAX_CHECK];

    nuggets(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        sizes = new int[N];
        for (int i = 0; i < N; i++) sizes[i] = Integer.parseInt(in.readLine());

        possible[0] = true;
        for (int i = 1; i < MAX_CHECK; i++) {
            for (int s : sizes) {
                if (i-s >= 0 && possible[i-s]) {
                    possible[i] = true;
                    break;
                }
            }
            if (!possible[i]) maxImpossible = i;
        }

        if (maxImpossible > 65536) out.println(0);
        else out.println(maxImpossible);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("nuggets.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nuggets.out")));
        new nuggets(in, out);
        in.close();
        out.close();
    }
}
