/*
Solution: Ad-hoc problem; just simulate the garage.
Runtime: O(MN)
*/

import java.util.*;
import java.io.*;

public class garage {
    int N, M;
    int[] rates, currSpaces, weights;

    garage(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        rates = new int[N];
        weights = new int[M];
        for (int i = 0; i < N; i++) rates[i] = Integer.parseInt(in.readLine());
        for (int i = 0; i < M; i++) weights[i] = Integer.parseInt(in.readLine());
        // Simulate car arrivals and departures
        long answer = 0;
        currSpaces = new int[N];
        Arrays.fill(currSpaces, -1);
        Queue<Integer> waiting = new LinkedList<>();
        for (int i = 0; i < 2 * M; i++) {
            int c = Integer.parseInt(in.readLine());
            if (c > 0) {
                // Car entering lot
                c--;
                waiting.add(c);
            } else {
                // Car leaving lot
                c = -c - 1;
                // Find the car
                for (int j = 0; j < N; j++) {
                    if (currSpaces[j] == c) {
                        // Found
                        currSpaces[j] = -1;
                    }
                }
            }

            // Park more cars if you can
            for (int j = 0; j < N; j++) {
                if (currSpaces[j] == -1 && !waiting.isEmpty()) {
                    int toPark = waiting.poll();
                    answer += weights[toPark] * rates[j];
                    currSpaces[j] = toPark;
                }
            }
        }

        out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("garage.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("garage.out")));
        new garage(in, out);
        in.close();
        out.close();
    }
}
