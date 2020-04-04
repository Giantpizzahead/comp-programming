/*
ID: sunnyky1
LANG: JAVA
TASK: crypt1

Solution: Do a complete search on all possible solutions.
O(9^5 * K) where K is some constant representing how long it takes to check solutions
O(59049K), so K isn't an issue.
*/

import java.util.*;
import java.io.*;

public class crypt1 {
    int N;
    char[] digits;
    HashSet<Character> hashDigits;

    crypt1() throws IOException {
        // Parse input
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        String line = fin.readLine();
        digits = new char[N];
        hashDigits = new HashSet<>();
        for (int i = 0; i < N; i++) {
            digits[i] = line.charAt(i*2);
            hashDigits.add(digits[i]);
        }
        fin.close();

        int answer = solve();
        PrintWriter fout = new PrintWriter("crypt1.out");
        fout.println(answer);
        fout.close();
    }

    int solve() {
        // Generate all possible cryptarithms, and try each one
        int answer = 0;
        String str1, str2;
        for (char a : digits) {
            for (char b : digits) {
                for (char c : digits) {
                    for (char d : digits) {
                        for (char e : digits) {
                            str1 = "" + a + b + c;
                            str2 = "" + d + e;
                            answer += (check(str1, str2)) ? 1 : 0;
                            /*
                            if (check(str1, str2)) {
                                System.out.println("Solution " + str1 + " " + str2);
                                System.out.println("e * abc " + mult(str1, str2.substring(1, 2)));
                                System.out.println("d * abc " + mult(str1, str2.substring(0, 1)));
                                System.out.println("abc * de " + mult(str1, str2));
                            }
                             */
                        }
                    }
                }
            }
        }
        return answer;
    }

    boolean check(String a, String b) {
        // e * abc works
        String check1 = mult(a, b.substring(1, 2));
        if (check1.length() != 3) return false;
        for (int i = 0; i < check1.length(); i++) {
            if (!hashDigits.contains(check1.charAt(i))) return false;
        }

        // d * abc works
        String check2 = mult(a, b.substring(0, 1));
        if (check2.length() != 3) return false;
        for (int i = 0; i < check2.length(); i++) {
            if (!hashDigits.contains(check2.charAt(i))) return false;
        }

        // abc * de works
        String check3 = mult(a, b);
        if (check3.length() != 4) return false;
        for (int i = 0; i < check3.length(); i++) {
            if (!hashDigits.contains(check3.charAt(i))) return false;
        }

        // Everything works
        return true;
    }

    String mult(String a, String b) {
        return Integer.toString(Integer.parseInt(a) * Integer.parseInt(b));
    }

    public static void main(String[] args) throws IOException {
        new crypt1();
    }
}
