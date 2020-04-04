/*
Solution: Sliding window with math. I haven't proven that sliding window
works, but it seems to. So I'm gonna try it. It's quite easy to implement, so
if this doesn't get the problem right I'll try something else.

Runtime: O(N)
*/

import java.util.*;
import java.io.*;

public class cowdate {
    int N;
    double[] probs;
    double[] prefixMults;

    cowdate() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowdate.in"));
        N = Integer.parseInt(fin.readLine());
        probs = new double[N];
        for (int i = 0; i < N; i++) {
            probs[i] = Integer.parseInt(fin.readLine()) / 1000000d;
        }
        fin.close();

        // Do sliding window
        int back = 0;
        double maxSoFar = 0;
        double total = 0;
        double runningMultiple = 1;
        double sum = 0;
        for (int front = 0; front < N; front++) {
            total *= (1 - probs[front]);
            total += probs[front] * runningMultiple;
            runningMultiple *= (1 - probs[front]);
            sum += probs[front];
            maxSoFar = Math.max(total, maxSoFar);
            while (sum > 1 && back != front) {
                // This answer is worse; shorten the sliding window
                sum -= probs[back];
                runningMultiple /= (1 - probs[back]);
                total -= probs[back] * runningMultiple;
                total /= (1 - probs[back]);
                back++;
            }
            maxSoFar = Math.max(total, maxSoFar);
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("cowdate.out")));
        fout.println((int) (maxSoFar * 1000000));
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new cowdate();
    }
}
