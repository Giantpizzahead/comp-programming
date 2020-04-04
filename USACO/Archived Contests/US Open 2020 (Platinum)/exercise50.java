import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class exercise50 {
    int N, MOD, numPrimes;
    boolean[] notPrime;
    int[] factorials;
    Integer[] primes;
    HashMap<Long, Integer>[] dp;

    exercise50(BufferedReader in, PrintWriter out) throws IOException {
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

        dp = new HashMap[N + 1];
        for (int i = 0; i <= N; i++) dp[i] = new HashMap<>();
        dp[0].put(1L, 1);

        factorials = new int[N + 1];
        factorials[0] = 1;
        factorials[1] = 1;
        for (int i = 2; i <= N; i++) factorials[i] = (int) ((long) factorials[i-1] * i % MOD);

        // Try every length cycle
        Stack<Change> changes = new Stack<>();
        for (int cycleLen = N; cycleLen > 0; cycleLen--) {
            // System.out.println("Cycle length " + cycleLen);
            // Add a new cycle at every location
            for (int i = N - cycleLen; i >= 0; i--) {
                // Transition from every state
                long currLCM;
                int ways;
                for (Map.Entry<Long, Integer> entry : dp[i].entrySet()) {
                    currLCM = entry.getKey();
                    ways = entry.getValue();
                    // Add cycle(s) at this location
                    long newLCM = lcm(currLCM, cycleLen);
                    long toMult = ways;
                    for (int numCycles = 1; numCycles <= (N-i) / cycleLen; numCycles++) {
                        // System.out.println("Adding " + numCycles + " cycles at loc " + i + " lcm " + currLCM);
                        long moreMult = moddiv(permutations(N-i-(cycleLen * (numCycles - 1)), cycleLen), cycleLen) % MOD;
                        long toDivide = numCycles;
                        toMult = moddiv(toMult * moreMult % MOD, toDivide);
                        int newLoc = i + cycleLen * numCycles;
                        // System.out.println("New loc " + newLoc + ", new lcm " + newLCM + ", change " + toMult);
                        changes.add(new Change(newLoc, newLCM, toMult));
                    }
                }
            }

            // Apply all changes
            // TODO: Exponents don't work well with mod :(
            while (!changes.isEmpty()) {
                Change c = changes.pop();
                dp[c.newLoc].put(c.lcm, (int) ((dp[c.newLoc].getOrDefault(c.lcm, 0) + c.toMult) % MOD));
            }
        }

//        for (int i = 0; i <= N; i++) {
//            System.out.println(dp[i]);
//            // System.out.println(dp[i].size());
//        }

        System.out.println(dp[N]);

        // Do final calculation
        long answer = 1;
        for (Map.Entry<Long, Integer> entry : dp[N].entrySet()) {
            answer = answer * powmod(entry.getKey(), entry.getValue()) % MOD;
        }
        out.println(answer);
    }

    class Change {
        int newLoc;
        long lcm, toMult;
        Change(int newLoc, long lcm, long toMult) {
            this.newLoc = newLoc;
            this.lcm = lcm;
            this.toMult = toMult;
        }
    }

    long permutations(int n, int k) {
        return moddiv(factorials[n], factorials[n-k]);
    }

    long choose(int n, int k) {
        return moddiv(moddiv(factorials[n], factorials[n-k]), factorials[k]);
    }

    long powmod(long n, int p) {
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
        if (b == 1) inv = 1;
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
        new exercise50(in, out);
        in.close();
        out.close();
    }
}
