import java.util.*;
import java.io.*;

public class cardgame1 {
    int T, X;
    double[] expected;

    cardgame1() throws IOException {
        Scanner fin = new Scanner(new FileReader("ipsc2012/c1.in"));
        PrintWriter fout = new PrintWriter("c.out");
        T = fin.nextInt();
        for (int i = 0; i < T; i++) {
            X = fin.nextInt();
            expected = new double[X];
            // Go backwards
            for (int j = 0; j < X; j++) {
                expected[j] = eval(j);
            }
            fout.printf("%.10f\n", expected[X-1]);
        }
        fin.close();
        fout.close();
    }

    double eval(int turnsLeft) {
        if (turnsLeft == 0) return 7;
        else {
            // Depending on what card you get, choose whether or not to continue
            double bestExpected = 0;
            for (int card = 1; card <= 13; card++) {
                if (expected[turnsLeft-1] > card) bestExpected += expected[turnsLeft-1] / 13;  // Don't take it
                else bestExpected += (double) card / 13;  // Take the card
            }
            return bestExpected;
        }
    }

    public static void main(String[] args) throws IOException {
        new cardgame1();
    }
}
