/*
ID: sunnyky1
LANG: JAVA
TASK: pprime

Solution: Generate and test all the possible palindromes. There aren't
that many possible palindromes, so as long as you test using an efficient
method, it'll work.

Runtime: O(~12000 * sqrt(b))
*/

import java.util.*;
import java.io.*;

public class pprime {
    int a, b;
    PrintWriter fout;

    pprime() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        a = Integer.parseInt(st.nextToken());
        b = Integer.parseInt(st.nextToken());
        fin.close();

        fout = new PrintWriter(new BufferedWriter(new FileWriter("pprime.out")));

        // Generate & test all palindromes from a to b
        for (int i = 1; i < 9; i++) {
            genPalindromes(0, i, i % 2 == 1, 0,0);
        }

        fout.close();
    }

    void genPalindromes(int index, int maxSize, boolean odd, int front, int back) {
        // Try this plaindrome if needed
        if (index == maxSize / 2 && !odd) {
            test(front, back, maxSize);
        } else if (index == maxSize / 2 && odd) {
            // Generate last number (middle) and test
            for (int i = 0; i < 10; i++) {
                front = front * 10 + i;
                test(front, back, maxSize);
                front /= 10;
            }
        } else {
            // Gen next number and continue
            for (int i = 0; i < 10; i++) {
                front = front * 10 + i;
                int toAdd = i * (int) Math.pow(10, index);
                back += toAdd;
                genPalindromes(index + 1, maxSize, odd, front, back);
                front /= 10;
                back -= toAdd;
            }
        }
    }

    void test(int front, int back, int size) {
        if (back % 10 == 0 && size != 1) return;
        int n = front * (int) Math.pow(10, size / 2) + back;
        if (n < a || n > b) return;

        // Test if the number is prime
        for (int d = 2; d <= (int) Math.sqrt(n); d++) {
            if (n % d == 0) return;
        }

        fout.println(n);
    }

    public static void main(String[] args) throws IOException {
        new pprime();
    }
}