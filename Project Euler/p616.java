import java.util.*;

public class p616 {
    ArrayList<Integer> primes;
    boolean[] isComposite;
    int SQRT_N;
    long N = 1000000000000L;

    public p616() {
        SQRT_N = (int) Math.sqrt(N);

        // Find primes up to sqrt(N)
        isComposite = new boolean[SQRT_N + 1];
        for (int i = 2; i < (int) Math.sqrt(SQRT_N) + 2; i++) {
            if (!isComposite[i]) for (int j = i * 2; j <= SQRT_N; j += i) isComposite[j] = true;
        }
        primes = new ArrayList<>();
        for (int i = 2; i <= SQRT_N; i++) if (!isComposite[i]) primes.add(i);

        // Test all integers in range [2, N] that are powers of another number
        long answer = 0;
        for (int p : primes) {
            answer += testPower(p);
            // System.out.println(p + " -> " + testPower(p));
        }

        // -16 for special case (4^2 does not work)
        answer -= 16;

        System.out.println(answer);
    }

    HashSet<Long> seen = new HashSet<>();
    long testPower(int p) {
        long sum = 0, currNum;
        int currBase = 1;
        while (true) {
            currBase++;
            currNum = currBase;
            for (int i = 1; i < p; i++) {
                currNum *= currBase;
                if (currNum > N) return sum;
            }

            if (seen.contains(currNum)) continue;
            else seen.add(currNum);

            // This number fits in the range, but can it split into at least 3 numbers?
            if (isComposite[currBase]) {
                // System.out.println(currNum + " works");
                sum += currNum;
            }
        }
    }

    // Finds the rth root of n (when floored).
    int floorRoot(long n, int r) {
        int low = 1, high = SQRT_N;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            boolean tooHigh = false;
            long temp = 1;
            for (int i = 0; i < r; i++) {
                temp *= mid;
                if (temp > n) {
                    tooHigh = true;
                    break;
                }
            }
            if (tooHigh) {
                high = mid - 1;
            } else {
                low = mid;
            }
        }
        return low;
    }

    public static void main(String[] args) {
        new p616();
    }
}
