import java.io.*;
import java.util.*;

public class thermometers {
    int K, N;
    int[] X;

    thermometers(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        K = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        X = new int[N + 1];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) X[i] = Integer.parseInt(st.nextToken());
        X[N] = X[0] + K;
        st = new StringTokenizer(in.readLine());

        // Try starting at each midpoint
        int answer = 2087654321;
        for (int i = 0; i < N; i++) {
            answer = Math.min(startAt(i), answer);
            // System.out.println(startAt(i));
        }
        out.printf("Case #%d: %d\n", tn, answer);
    }

    int startAt(int i) {
        // Start at midpoint of this
        int numUsed = 1;
        double bestLeft = (X[i+1] - X[i]) / 2D, bestRight = (X[i+1] - X[i]) / 2D;
        for (int ns = 1; ns < N; ns++) {
            int ci = (i + ns) % N;
            double rangeSize = X[ci+1] - X[ci];
            // System.out.println(rangeSize);
            if (bestRight > rangeSize) bestRight = rangeSize;
            if (bestLeft + 0.01 > rangeSize) {
                // Issues (equal to or past valid range); add thermometer on previous
                bestLeft = 0;
                bestRight = rangeSize;
                numUsed++;
            }
            if (bestLeft - 0.01 > bestRight) {
                // Two thermometers must be placed here
                bestRight = rangeSize - bestLeft;
                bestLeft = 0;
                numUsed += 2;
            } else {
                if (ns == N - 1) {
                    // Add 1 or 2 if final two cannot be joined (for last segment)
                    // Get optimal location (for 1 added)
                    double origMid = rangeSize - ((X[i+1] - X[i]) / 2D);
//                    System.out.println("orig: " + origMid);
//                    System.out.println("lr " + bestLeft + " " + bestRight);
//                    System.out.println("nu " + numUsed);
                    if (bestLeft > origMid + 0.01 || bestRight < origMid - 0.01) numUsed += 2;
                    else numUsed++;
                } else {
                    // One is enough
                    double temp = bestLeft;
                    bestLeft = rangeSize - bestRight;
                    bestRight = rangeSize - temp;
                    numUsed++;
                }
            }
        }
        return numUsed;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new thermometers(in, out, i);
        in.close();
        out.close();
    }
}
