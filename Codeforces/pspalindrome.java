import java.util.*;
import java.io.*;

public class pspalindrome {
    int N;
    String str;
    String revStr;

    pspalindrome(BufferedReader in, PrintWriter out) throws IOException {
        str = in.readLine();
        revStr = new StringBuilder(str).reverse().toString();
        N = str.length();
        // Find longest palindrome involving prefix and suffix
        int splitLength = 0;
        for (; splitLength < N/2; splitLength++) {
            if (str.charAt(splitLength) != revStr.charAt(splitLength)) break;
        }

        // System.out.println("splitLength: " + splitLength);

        // Now, find the longest palindromes starting at the end of the left or right sides
        int longestLeft = palinKMP(str, splitLength, revStr, splitLength);
        int longestRight = palinKMP(revStr, splitLength, str, splitLength);
        // System.out.println(longestLeft + " " + longestRight);

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < splitLength; i++) sb.append(str.charAt(i));
        if (longestLeft > longestRight) {
            for (int i = 0; i < longestLeft; i++) sb.append(str.charAt(splitLength + i));
        } else {
            for (int i = 0; i < longestRight; i++) sb.append(revStr.charAt(splitLength + i));
        }
        for (int i = splitLength - 1; i >= 0; i--) sb.append(revStr.charAt(i));
        out.println(sb.toString());
    }

    int palinKMP(String patStr, int startLoc, String searchStr, int searchStartLoc) {
        String pat = patStr.substring(startLoc);
        int[] kmp = new int[pat.length()];
        kmp[0] = -1;
        int currKMP = -1;
        for (int i = 1; i < pat.length(); i++) {
            while (currKMP != -1 && pat.charAt(currKMP + 1) != pat.charAt(i)) {
                currKMP = kmp[currKMP];
            }
            if (pat.charAt(currKMP + 1) == pat.charAt(i)) currKMP++;
            kmp[i] = currKMP;
        }
        // System.out.println(Arrays.toString(kmp));

        int matchLoc = -1;
        for (int i = searchStartLoc; i < searchStr.length(); i++) {
            while (matchLoc != -1 && pat.charAt(matchLoc + 1) != searchStr.charAt(i)) {
                matchLoc = kmp[matchLoc];
            }
            if (pat.charAt(matchLoc + 1) == searchStr.charAt(i)) matchLoc++;
            // Check if palindrome has been found
            // System.out.println("loc " + matchLoc);
            int palinLength = (N - 1 - i) - startLoc + 1 + matchLoc;
            if ((matchLoc + 1) >= palinLength / 2) return palinLength;  // Yes!
        }

        // System.err.println("what");
        return -1;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) new pspalindrome(in, out);
        in.close();
        out.close();
    }
}