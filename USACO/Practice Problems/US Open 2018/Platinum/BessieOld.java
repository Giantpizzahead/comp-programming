import java.io.IOException;

public class BessieOld extends Grader {
    final int INF = 1000000007;

    public static void main(String[] args) throws IOException { new BessieOld().run(); }

    @Override
    public void helpBessie(int ID) {
        if (getCurrentPassIndex() == 1) return;
        int K = getWindowLength();
        int i = getCurrentCarIndex();
        if (K > 5500) {
            shoutMinimum(0);
            return;
        }
        if (i < K) {
            set(i, ID);
            if (i == K - 1) {
                // Off-by-one
                int minimum = INF;
                for (int j = 0; j < K; j++) {
                    minimum = Math.min(get(j), minimum);
                }
                shoutMinimum(minimum);
            }
        } else {
            set(i % K, ID);
            int minimum = INF;
            for (int j = 0; j < K; j++) {
                minimum = Math.min(get(j), minimum);
            }
            shoutMinimum(minimum);
        }
    }
}