/*
ID: sunnyky1
LANG: JAVA
TASK: fracdec

Solution: Simulate long division, tracking the previously seen 'remainders'.
Once a previously seen remainder is seen, that means a cycle has formed, so
you can stop there.

Runtime: O(10D) since there are 10D possible remainders (any higher would be
invalid)
*/

import java.util.*;
import java.io.*;

public class fracdec {
    int N, D;

    fracdec() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("fracdec.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        D = Integer.parseInt(st.nextToken());
        fin.close();

        // First, find the integer part
        int intPart = N / D;
        N -= intPart * D;

        // Now, do the long division
        String decPart = longDivison();

        String toPrint = Integer.toString(intPart) + '.' + decPart;

        PrintWriter fout = new PrintWriter("fracdec.out");
        for (int i = 0; i < toPrint.length(); i += 76) {
            fout.println(toPrint.substring(i, Math.min(i + 76, toPrint.length())));
        }
        fout.close();
    }

    String longDivison() {
        ArrayList<Integer> digits = new ArrayList<>();
        int[] seenRemainders = new int[D * 10];
        Arrays.fill(seenRemainders, -1);
        seenRemainders[0] = 0;
        int remainder = N;
        for (int i = 0;; i++) {
            remainder *= 10;
            if (seenRemainders[remainder] != -1) break;  // Reached end
            seenRemainders[remainder] = i;
            int newDigit = remainder / D;
            digits.add(newDigit);
            remainder -= newDigit * D;
        }

        if (digits.size() == 0) return "0";

        StringBuilder sb = new StringBuilder();
        if (remainder == 0) {
            // Not an infinite expansion
            digits.forEach(sb::append);
        } else {
            // Infinite expansion; find start of cycle / put parentheses there
            for (int i = 0; i < digits.size(); i++) {
                if (seenRemainders[remainder] == i) sb.append('(');
                sb.append(digits.get(i));
            }
            sb.append(')');
        }

        return sb.toString();
    }

    public static void main(String[] args) throws IOException {
        new fracdec();
    }
}