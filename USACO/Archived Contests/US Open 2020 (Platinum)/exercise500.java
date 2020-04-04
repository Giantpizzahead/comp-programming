import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class exercise500 {
    final int MAXC = 14;
    int N, MOD, numPrimes;
    boolean[] notPrime;
    int[] factorials, inverses;
    Integer[] primes;
    HashMap<Integer, Integer>[] factored;
    // dp[i][p][c] = Location i, prime p, c # of that prime in the lcm
    int[][][] dp;

    exercise500(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        MOD = Integer.parseInt(st.nextToken());

        notPrime = new boolean[N + 1];
        ArrayList<Integer> primeList = new ArrayList<>(2);
        for (int i = 2; i <= N; i++) {
            if (!notPrime[i]) {
                primeList.add(i);
                for (int j = i * 2; j <= N; j += i) notPrime[j] = true;
            }
        }
        primes = primeList.toArray(new Integer[0]);
        numPrimes = primes.length;
        // System.out.println("Primes: " + Arrays.toString(primes));

        factored = new HashMap[N + 1];
        for (int i = 1; i <= N; i++) factored[i] = factorize(i);

        dp = new int[N + 1][numPrimes][MAXC];
        for (int p = 0; p < numPrimes; p++) dp[0][p][0] = 1;

        factorials = new int[N + 1];
        factorials[0] = 1;
        factorials[1] = 1;
        for (int i = 2; i <= N; i++) factorials[i] = (int) ((long) factorials[i-1] * i % MOD);

        inverses = new int[N + 1];
        inverses[1] = 1;
        for (int i = 2; i <= N; i++) inverses[i] = (int) modinv(MOD, i).b;

        // Try every length cycle
        Stack<Change> changes = new Stack<>();
        for (int cycleLen = N; cycleLen > 0; cycleLen--) {
            HashMap<Integer, Integer> factoredCycleLen = factored[cycleLen];
            // System.out.println("Cycle length " + cycleLen);
            // Add a new cycle at every location
            for (int i = N - cycleLen; i >= 0; i--) {
                // Transition from every prime
                for (int p = 0; p < numPrimes; p++) {
                    // Stop early once no numbers could possibly be this high
                    int val = 1;
                    for (int c = 0; val <= N; c++) {
                        val *= primes[p];
                        if (dp[i][p][c] == 0) continue;
                        // Add cycle(s) at this location
                        int newC = Math.max(c, factoredCycleLen.getOrDefault(p, 0));
                        long toAdd = dp[i][p][c];
                        for (int numCycles = 1; numCycles <= (N - i) / cycleLen; numCycles++) {
                            // System.out.println("Adding " + numCycles + " cycles at loc " + i + " lcm " + currLCM);
                            long moreAdd = moddiv(permutations(N - i - (cycleLen * (numCycles - 1)), cycleLen), cycleLen) % MOD;
                            toAdd = moddiv(toAdd * moreAdd % MOD, numCycles);
                            int newLoc = i + cycleLen * numCycles;
                            // System.out.println("New loc " + newLoc + ", new lcm " + newLCM + ", change " + toMult);
                            changes.add(new Change(newLoc, p, newC, (int) toAdd));
                        }
                    }
                }
            }

            // Apply all changes
            while (!changes.isEmpty()) {
                Change c = changes.pop();
                dp[c.i][c.p][c.c] = dp[c.i][c.p][c.c] + c.toAdd;
                if (dp[c.i][c.p][c.c] >= MOD) dp[c.i][c.p][c.c] -= MOD;
            }
        }

//        for (int i = 0; i <= N; i++) {
//            System.out.println("dp[" + i + "]:");
//            for (int p = 0; p < numPrimes; p++) {
//                System.out.println(Arrays.toString(dp[i][p]));
//            }
//        }

        // Do final calculation
        long answer = 1;
        for (int p = 0; p < numPrimes; p++) {
            long currMult = 1;
            for (int c = 1; c < MAXC; c++) {
                currMult = currMult * primes[p] % MOD;
                answer = answer * powmod(currMult, dp[N][p][c]) % MOD;
            }
        }
        out.println(answer);
    }

    class Change {
        int i, p, c, toAdd;
        Change(int i, int p, int c, int toAdd) {
            this.i = i;
            this.p = p;
            this.c = c;
            this.toAdd = toAdd;
        }
    }

    long permutations(int n, int k) {
        return moddiv(factorials[n], factorials[n-k]);
    }

    long choose(int n, int k) {
        return moddiv(moddiv(factorials[n], factorials[n-k]), factorials[k]);
    }

    long powmod(long n, long p) {
        long res = 1;
        while (p != 0) {
            if (p % 2 == 1) res = res * n % MOD;
            n = n * n % MOD;
            p /= 2;
        }
        return res;
    }

    long moddiv(long a, long b) {
        long inv;
        if (b <= N) inv = inverses[(int) b];
        else inv = modinv(MOD, b).b;
        return a * inv % MOD;
    }

    Pair modinv(long a, long b) {
        long c = a / b;
        long d = a % b;
        if (d == 1) {
            return new Pair(1, -c + MOD);
        } else {
            Pair res = modinv(b, d);
            long e = res.a;
            long f = res.b;
            long nf = (-c * f + e) % MOD;
            if (nf < 0) nf += MOD;
            return new Pair(f, nf);
        }
    }

    class Pair {
        long a, b;
        Pair(long a, long b) {
            this.a = a;
            this.b = b;
        }
    }

    long lcm(long a, long b) {
        return a / gcf(a, b) * b;
    }

    long gcf(long a, long b) {
        if (a == 0) return b;
        else return gcf(b % a, a);
    }

    HashMap<Integer, Integer> factorize(int n) {
        HashMap<Integer, Integer> factors = new HashMap<>(2);
        for (int i = 0; i < numPrimes; i++) {
            int p = primes[i];
            int count = 0;
            while (n != 1 && n % p == 0) {
                count++;
                n /= p;
            }
            if (count != 0) factors.put(i, count);
            if (n == 1) break;
        }
        return factors;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("exercise.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("exercise.out")));
        new exercise500(in, out);
        in.close();
        out.close();
    }
}
