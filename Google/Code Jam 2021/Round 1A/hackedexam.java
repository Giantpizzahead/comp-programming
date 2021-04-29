import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class hackedexam {

    int N, Q;
    int[] S;
    boolean[][] A;
    BigInteger[][] nCk;

    void solve(Scanner sc) {
        N = sc.nextInt();
        Q = sc.nextInt();
        S = new int[N];
        A = new boolean[N][Q];
        for (int i = 0; i < N; i++) {
            String str = sc.next();
            for (int j = 0; j < Q; j++) {
                A[i][j] = (str.charAt(j) == 'T');
            }
            S[i] = sc.nextInt();
        }
        
        if (N == 1) {
            // Either copy or do the reverse
            if (S[0] > Q/2) {
                for (int i = 0; i < Q; i++) System.out.print(A[0][i] ? 'T' : 'F');
                System.out.println(" " + S[0] + "/1");
            } else {
                for (int i = 0; i < Q; i++) System.out.print(A[0][i] ? 'F' : 'T');
                System.out.println(" " + (Q-S[0]) + "/1");
            }
            return;
        }

        if (N == 2) {
            int numSame = 0, numDiff = 0;
            for (int i = 0; i < Q; i++) {
                if (A[0][i] == A[1][i]) numSame++;
                else numDiff++;
            }
            int aDiff = Math.max(S[0] - S[1], 0);
            int bDiff = Math.max(S[1] - S[0], 0);
            while (aDiff + bDiff != numDiff) {
                aDiff++;
                bDiff++;
            }
            int same = S[0] - aDiff;
            // System.out.println(aDiff + " " + bDiff + " " + same);
            int score = 0;
            for (int i = 0; i < Q; i++) {
                if (A[0][i] == A[1][i]) {
                    if (same > numSame/2) System.out.print(A[0][i] ? 'T' : 'F');
                    else System.out.print(A[0][i] ? 'F' : 'T');
                } else {
                    if (aDiff > bDiff) System.out.print(A[0][i] ? 'T' : 'F');
                    else System.out.print(A[1][i] ? 'T' : 'F');
                }
            }
            System.out.println(" " + (Math.max(aDiff, bDiff) + Math.max(same, numSame-same)) + "/1");
            return;
        }

        // N == 3

        int same = 0, aOut = 0, bOut = 0, cOut = 0;
        for (int i = 0; i < Q; i++) {
            if (A[0][i] == A[1][i] && A[1][i] == A[2][i]) same++;
            else if (A[0][i] != A[1][i] && A[0][i] != A[2][i]) aOut++;
            else if (A[1][i] != A[0][i] && A[1][i] != A[2][i]) bOut++;
            else if (A[2][i] != A[0][i] && A[2][i] != A[1][i]) cOut++;
        }

        // Try all combinations
        BigInteger totalWays = BigInteger.ZERO;
        BigInteger aGood = BigInteger.ZERO;
        BigInteger aBad = BigInteger.ZERO;
        BigInteger bGood = BigInteger.ZERO;
        BigInteger bBad = BigInteger.ZERO;
        BigInteger cGood = BigInteger.ZERO;
        BigInteger cBad = BigInteger.ZERO;
        BigInteger sGood = BigInteger.ZERO;
        BigInteger sBad = BigInteger.ZERO;
        for (int a = 0; a <= aOut; a++) {
            for (int b = 0; b <= bOut; b++) {
                for (int c = 0; c <= cOut; c++) {
                    // Does this work?
                    int aScore = a + (bOut - b) + (cOut - c);
                    int bScore = (aOut - a) + b + (cOut - c);
                    int cScore = (aOut - a) + (bOut - b) + c;
                    int s = S[0] - aScore;
                    if (s < 0 || s > same || S[1] - bScore != s || S[2] - cScore != s) continue;
                    // Yes! Record it
                    BigInteger ways = nCk[aOut][a].multiply(nCk[bOut][b]).multiply(nCk[cOut][c]).multiply(nCk[same][s]);
                    totalWays = totalWays.add(ways);
                    aGood = aGood.add(ways.multiply(BigInteger.valueOf(a)));
                    aBad = aBad.add(ways.multiply(BigInteger.valueOf(aOut-a)));
                    bGood = bGood.add(ways.multiply(BigInteger.valueOf(b)));
                    bBad = bBad.add(ways.multiply(BigInteger.valueOf(bOut-b)));
                    cGood = cGood.add(ways.multiply(BigInteger.valueOf(c)));
                    cBad = cBad.add(ways.multiply(BigInteger.valueOf(cOut-c)));
                    sGood = sGood.add(ways.multiply(BigInteger.valueOf(s)));
                    sBad = sBad.add(ways.multiply(BigInteger.valueOf(same-s)));
                }
            }
        }

        // Find the best choice
        boolean fa, fb, fc, fs;
        BigInteger expected = BigInteger.ZERO;
        if (aGood.compareTo(aBad) > 0) {
            fa = true;
            expected = expected.add(aGood);
        } else {
            fa = false;
            expected = expected.add(aBad);
        }
        if (bGood.compareTo(bBad) > 0) {
            fb = true;
            expected = expected.add(bGood);
        } else {
            fb = false;
            expected = expected.add(bBad);
        }
        if (cGood.compareTo(cBad) > 0) {
            fc = true;
            expected = expected.add(cGood);
        } else {
            fc = false;
            expected = expected.add(cBad);
        }
        if (sGood.compareTo(sBad) > 0) {
            fs = true;
            expected = expected.add(sGood);
        } else {
            fs = false;
            expected = expected.add(sBad);
        }

        BigInteger gcd = totalWays.gcd(expected);
        totalWays = totalWays.divide(gcd);
        expected = expected.divide(gcd);

        for (int i = 0; i < Q; i++) {
            if (A[0][i] == A[1][i] && A[1][i] == A[2][i]) {
                if (fs) System.out.print(A[0][i] ? 'T' : 'F');
                else System.out.print(A[0][i] ? 'F' : 'T');
            } else if (A[0][i] != A[1][i] && A[0][i] != A[2][i]) {
                if (fa) System.out.print(A[0][i] ? 'T' : 'F');
                else System.out.print(A[1][i] ? 'T' : 'F');
            } else if (A[1][i] != A[0][i] && A[1][i] != A[2][i]) {
                if (fb) System.out.print(A[1][i] ? 'T' : 'F');
                else System.out.print(A[2][i] ? 'T' : 'F');
            } else if (A[2][i] != A[0][i] && A[2][i] != A[1][i]) {
                if (fc) System.out.print(A[2][i] ? 'T' : 'F');
                else System.out.print(A[0][i] ? 'T' : 'F');
            }
        }
        System.out.println(" " + expected + "/" + totalWays);
    }

    void genNCK() {
        final int MAXN = 150;
        nCk = new BigInteger[MAXN][MAXN];
        for (int i = 0; i < MAXN; i++) {
            nCk[i][0] = BigInteger.valueOf(1);
            nCk[i][i] = BigInteger.valueOf(1);
            for (int j = 1; j < i; j++) {
                nCk[i][j] = nCk[i-1][j-1].add(nCk[i-1][j]);
            }
        }
        // System.out.println(Arrays.deepToString(nCk));
    }

    public static void main(String[] args) {
        hackedexam sol = new hackedexam();
        sol.genNCK();
        Scanner sc = new Scanner(System.in);
        int T = sc.nextInt();
        for (int i = 1; i <= T; i++) {
            System.out.print("Case #" + i + ": ");
            sol.solve(sc);
        }
    }
}