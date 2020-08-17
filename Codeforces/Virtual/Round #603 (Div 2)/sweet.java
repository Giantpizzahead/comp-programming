/*
Solution: Either max value or sum of two smaller values.
*/

import java.util.*;
import java.io.*;

public class sweet {
    int T, N;
    int[] colors = new int[3];

    sweet() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        T = Integer.parseInt(st.nextToken());
        for (int i = 0; i < T; i++) {
            // System.out.println("sep");
            st = new StringTokenizer(in.readLine());
            colors[0] = Integer.parseInt(st.nextToken());
            colors[1] = Integer.parseInt(st.nextToken());
            colors[2] = Integer.parseInt(st.nextToken());
            int answer = 0;
            Arrays.sort(colors);
            // Eat two most candies
            int numToDecr = colors[1] - colors[0];
            colors[2] -= numToDecr;
            colors[1] -= numToDecr;
            answer += numToDecr;
            // Now 2 min are equal; alternate eating those and most candies
            // To make all 3 equal
            numToDecr = Math.min(colors[0] + colors[1], colors[2]);
            answer += numToDecr;
            if (numToDecr == colors[2]) {
                // Remove from the final 2 candies evenly
                colors[0] -= (numToDecr + 1) / 2;
                colors[1] -= numToDecr / 2;
                // Calculate final answer
                answer += Math.min(colors[0], colors[1]);
            } else {
                // Final answer reached
            }
            System.out.println(answer);
        }
        in.close();
    }

    public static void main(String[] args) throws IOException {
        new sweet();
    }
}
