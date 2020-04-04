/*
ID: sunnyky1
LANG: JAVA
TASK: prefix

Solution: Use dp to check if the sequence can be extended up to a certain length. At
each dp state, loop through all primitives to check if they can extend the sequence.

Runtime: O(2000S) - This may need to be optimized a bit to work
*/

import java.util.*;
import java.io.*;

public class prefix {
    ArrayList<String> primitives;
    String sequence;

    prefix() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("prefix.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        primitives = new ArrayList<>();
        outerLoop:
        while (true) {
            while (st.hasMoreTokens()) {
                String next = st.nextToken();
                if (next.equals(".")) break outerLoop;
                primitives.add(next);
            }
            st = new StringTokenizer(fin.readLine());
        }

        StringBuilder sb = new StringBuilder();
        while (true) {
            String line = fin.readLine();
            if (line == null) break;
            sb.append(line);
        }
        sequence = sb.toString();
        fin.close();

        // System.out.println(primitives);
        // System.out.println(sequence);

        boolean[] dp = new boolean[sequence.length() + 1];
        dp[0] = true;
        int maxPrefix = 0;
        for (int i = 1; i <= sequence.length(); i++) {
            // Check all primitives to see if they could be used here
            for (String p : primitives) {
                if (i - p.length() >= 0 && dp[i - p.length()] && sequence.startsWith(p, i - p.length())) {
                    // System.out.println(i);
                    dp[i] = true;
                    maxPrefix = i;
                    break;
                }
            }
        }

        PrintWriter fout = new PrintWriter("prefix.out");
        fout.println(maxPrefix);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new prefix();
    }
}
