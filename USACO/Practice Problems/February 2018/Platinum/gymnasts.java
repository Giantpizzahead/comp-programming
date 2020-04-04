/*
Solution: Calculate the factors of N, tracking how many 'starting sizes' they could create for the
cow stacks (any magic configs only use 2 #s). Then, sort them in decreasing order. Iterate through
the factors, updating the answer with 2^F - 2 (for all possible subsets of the 2 sizes used, minus
the ones where all the numbers are the same). Also, loop through the rest of the factors, removing
the same # of possible numbers if the other factors divides the current one.

Note: Max # of factors is 4096, so an N^2 solution involving factors is fine.

Runtime: O(sqrt(N) * log(4096) + 4096^2)
*/

import java.util.*;
import java.io.*;

public class gymnasts {
    long N;
    ArrayList<Factor> factors;
    final long MOD = 1000000007;

    gymnasts() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("gymnasts.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Long.parseLong(st.nextToken());
        fin.close();
        factors = new ArrayList<>();

        // for (int i = 1; i < 10; i++) System.out.println(pow2(i));

        // Find the number's factors
        for (long f = 2; f < Math.sqrt(N) + 1; f++) {
            if (N % f == 0) {
                // Factor
                long otherFactor = N / f;
                // System.out.println(f + " " + otherFactor);
                // Calculate # of start sizes
                factors.add(new Factor(f, numStartSizes(f)));
                if (f != otherFactor) factors.add(new Factor(otherFactor, numStartSizes(otherFactor)));
            }
        }
        factors.sort(Comparator.comparingLong(x -> -x.f));

        // Calculate all possible cycles
        long answer = 0;
        Factor curr, smaller;
        for (int i = 0; i < factors.size(); i++) {
            curr = factors.get(i);
            // System.out.println(curr);
            answer += curr.c * (pow2(curr.f) - 2);
            if (answer < 0) answer += MOD;
            answer %= MOD;

            // Update num start sizes for all smaller factors
            for (int j = i + 1; j < factors.size(); j++) {
                smaller = factors.get(j);
                if (curr.f % smaller.f == 0) {
                    smaller.c -= curr.c;
                }
            }

            curr.c = 0;
        }

        // Add N to the answer
        answer = (answer + N) % MOD;

        PrintWriter fout = new PrintWriter("gymnasts.out");
        fout.println(answer);
        fout.close();
    }

    long numStartSizes(long n) {
        return (N - 1) / n % MOD;
    }

    long pow2(long n) {
        long curr2 = 2;
        long answer = 1;
        while (n > 0) {
            if (n % 2 == 1) answer = answer * curr2 % MOD;
            curr2 = curr2 * curr2 % MOD;
            n /= 2;
        }
        return answer;
    }

    public static void main(String[] args) throws IOException {
        new gymnasts();
    }

    class Factor {
        long f, c;
        Factor(long f, long c) {
            this.f = f;
            this.c = c;
        }
        @Override
        public String toString() {
            return "(" + f + ", " + c + ")";
        }
    }
}