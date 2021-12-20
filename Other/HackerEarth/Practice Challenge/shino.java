/*
Solution: Find the GCF of the two numbers, and find the prime factorization of that number.
*/

import java.util.*;
import java.io.*;

public class shino {
    long A, B;

    shino() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        A = Long.parseLong(st.nextToken());
        B = Long.parseLong(st.nextToken());
        long GCF = findGCF(A, B);
        // System.out.println("GCF: " + GCF);

        int numFactors = findFactors(GCF);
        System.out.println(numFactors);

        in.close();
    }

    int findFactors(long n) {
        int answer = 0;
        for (int i = 1; i < (int) (Math.sqrt(n) + 1); i++) {
            if (n % i == 0) {
                answer++;
                if (!(Math.abs(i - Math.sqrt(n)) < 0.00001)) answer++;
            }
        }
        return answer;
    }

    long findGCF(long a, long b) {
        if (a == b) return a;
        else if (a == 0) return b;
        else if (b == 0) return a;
        else if (a > b) return findGCF(a % b, b);
        else return findGCF(a, b % a);
    }

    public static void main(String[] args) throws IOException {
        new shino();
    }
}
