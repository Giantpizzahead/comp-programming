import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class cardgame2 {
    int T, X;
    HashMap<Long, Double>[] expected = new HashMap[53];

    cardgame2() throws IOException {
        Scanner fin = new Scanner(new FileReader("ipsc2012/c-example.in"));
        PrintWriter fout = new PrintWriter("c.out");
        for (int i = 1; i < 53; i++) expected[i] = new HashMap<>(1000000);

        // Precompute all the states
        int[] cards = new int[13];
        for (int i = 0; i < 13; i++) cards[i] = 4;

        T = fin.nextInt();
        for (int i = 0; i < T; i++) {
            X = fin.nextInt();

            // Get result for this hash
            fout.printf("%.10f\n", eval(cards, X));
            fout.flush();
        }
        fin.close();
        fout.close();
    }

    long hash(int[] arr) {
        long toMult = 1, currHash = 0;
        for (int value : arr) {
            currHash += (long) (value - 1) * toMult;
            toMult *= 4;
        }
        return currHash;
    }

    double eval(int[] cards, int turns) {
        long arrHash = hash(cards);
        // Memoization
        if (expected[turns].containsKey(arrHash)) return expected[turns].get(arrHash);

        if (turns == 1) {
            // Base case
            int numCards = 53 - turns;
            double val = 0;
            for (int i = 0; i < 13; i++) {
                val += (double) (i + 1) * (cards[i]) / numCards;
            }
            expected[turns].put(arrHash, val);
            return val;
        } else {
            // Try taking all cards
            double val = 0;
            for (int i = 0; i < 13; i++) {
                if (cards[i] == 0) continue;
                cards[i]--;
                double bestChoice = Math.max(eval(cards, turns - 1), i+1);
                cards[i]++;
                val += bestChoice / 13;
            }
            expected[turns].put(arrHash, val);
            return val;
        }
    }

    public static void main(String[] args) throws IOException {
        new cardgame2();
    }
}
