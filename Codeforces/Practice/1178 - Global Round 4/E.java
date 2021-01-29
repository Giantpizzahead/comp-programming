/*
Solution: In the outermost 4 chars, there is always at least a length-2 palindrome sequence. Use one
letter in the middle to always meet the t requirement.
Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class archaeology {
    int N;
    String str;

    archaeology(BufferedReader in, PrintWriter out) throws IOException {
        str = in.readLine();
        N = str.length();
        int l = 0, r = N-1;
        Queue<Character> front = new LinkedList<>();
        Stack<Character> back = new Stack<>();
        while (r - l >= 3) {
            // Check first and last 2 chars
            if (str.charAt(l) == str.charAt(r)) {
                front.add(str.charAt(l));
                back.push(str.charAt(r));
            } else if (str.charAt(l+1) == str.charAt(r)) {
                front.add(str.charAt(l+1));
                back.push(str.charAt(r));
            } else if (str.charAt(l) == str.charAt(r-1)) {
                front.add(str.charAt(l));
                back.push(str.charAt(r-1));
            } else {
                front.add(str.charAt(l+1));
                back.push(str.charAt(r-1));
            }
            l += 2;
            r -= 2;
        }
        while (!front.isEmpty()) out.print(front.poll());
        // Add random middle character if needed
        if (r - l > 0) out.print(str.charAt(l));
        while (!back.isEmpty()) out.print(back.pop());
        out.println();
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new archaeology(in, out);
        in.close();
        out.close();
    }
}
