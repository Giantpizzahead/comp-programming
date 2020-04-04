/*
Solution: If gcd(a, m) != 1, divide both the #s by that GCD to get the same
problem, but with a GCD of 1. Now, just check how many #s from [a, a+m) are
coprime with m to get your answer. m will never be 1 (a < m), so no need to
worry about this case.

To count the numbers that are coprime with x, find the prime factorization
of x. Split the check up into coprime(1, a+m-1) - coprime(1, a-1). Then, use
PIE to evaluate each of these.

Coprime with 30 in range [1, 30] = 30 - # that are NOT coprime with 30
30 = 2*3*5
2 4 6 8 10 12 14 16 18 20 22 24 26 28 30 = 30/2 = 15
3 6 9 12 15 18 21 24 27 30 = 30 / 3 = 10
5 10 15 20 25 30 = 30 / 5 = 6
-
6 12 18 24 30 = 30 / 6 = 5
10 20 30 = 30 / 10 = 3
15 30 = 30 / 15 = 2
+
30 = 30 / 30 = 1
=
31 - 10 + 1 = 22

30 - 22 = 8 #s are coprime!

Check:
1 7 11 13 17 19 23 29 = 8 #s are coprime

Runtime: O(T * (log(m) + sqrt(m) + 2^(# prime factors of m)))
This is fine, since the max # of prime factors of m <= 10^10 is 10.
2^10 = 1024, which is less than the sqrt(m) term.
*/

import java.util.*;
import java.io.*;

public class samegcds {
    int T;
    long A, M;

    samegcds(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            st = new StringTokenizer(in.readLine());
            A = Long.parseLong(st.nextToken());
            M = Long.parseLong(st.nextToken());
            out.println(solve());
        }
    }

    long solve() {
        // First, divide by gcd(A, M) to reduce problem into coprime counting
        long gcd = findGCD(A, M);
        A /= gcd;
        M /= gcd;
        // System.out.println("GCD: " + gcd);

        // Now, find the prime factorization of M
        ArrayList<Long> factors = new ArrayList<>();
        long tempM = M;
        int sqrtM = (int) Math.sqrt(M);
        for (int i = 2; tempM != 1 && i < sqrtM + 1; i++) {
            if (tempM % i == 0) {
                factors.add((long) i);
                while (tempM % i == 0) tempM /= i;
            }
        }
        if (tempM != 1) factors.add(tempM);
        // System.out.println("Prime factors of " + M + ": " + factors);

        // Finally, count the # of coprime numbers
        return coprime(A, A + M - 1, factors);
    }

    long coprime(long a, long b, ArrayList<Long> factors) {
        // System.out.println("a = " + a + ", b = " + b + ", factors = " + factors);
        return coprimeFrom1(A + M - 1, factors) - coprimeFrom1(A - 1, factors);
    }

    long notCoprime;
    long coprimeFrom1(long a, ArrayList<Long> factorList) {
        factorArr = new long[factorList.size()];
        for (int i = 0; i < factorList.size(); i++) factorArr[i] = factorList.get(i);
        // Use PIE to find the answer
        targetNum = a;
        notCoprime = 0;
        runPIE(0, 1, 0);
        return a - notCoprime;
    }

    long targetNum;
    long[] factorArr;
    void runPIE(int i, long n, int numUsed) {
        if (i == factorArr.length) {
            // Update notCoprime count
            if (numUsed == 0) return;
            else if (numUsed % 2 == 1) {
                // Add to notCoprime
                notCoprime += targetNum / n;
            } else {
                // Subtract from notCoprime
                notCoprime -= targetNum / n;
            }
        } else {
            // Continue PIE
            runPIE(i+1, n, numUsed);
            runPIE(i+1, n*factorArr[i], numUsed+1);
        }
    }

    long findGCD(long a, long b) {
        if (a == 0) return b;
        else return findGCD(b % a, a);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new samegcds(in, out);
        in.close();
        out.close();
    }
}