/*
Solution: Binary search on max speed ran.
*/

import java.util.*;
import java.io.*;

public class race {
    int N, K;

    race(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        K = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        for (int i = 0; i < N; i++) {
            int X = Integer.parseInt(in.readLine());
            out.println(solve(X));
        }
    }

    int solve(int X) {
        int low = 0, high = K;
        long bestTime = 99999999;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            long result = check(mid, X);
            if (result == -1) {
                high = mid - 1;
            } else {
                bestTime = Math.min(result, bestTime);
                // System.out.println(mid + " " + X + " works -> " + result);
                low = mid;
            }
        }
        return (int) bestTime;
    }

    long check(int mid, int X) {
        if (mid <= X) {
            // No worries of overspeeding; just calculate the time taken
            long distToRun = K - sumFrom1(mid);
            if (distToRun < 0) return -1;
            else return mid + (distToRun + mid - 1) / mid;
        }

        long timeTaken = mid;
        long initDistRan = sumFrom1(mid);

        // Slow down to X speed
        long finalDistRan;
        if (mid - 1 <= X) finalDistRan = 0;  // No need to slow down
        else {
            finalDistRan = sumFrom1(mid-1) - sumFrom1(X);
            timeTaken += mid - X - 1;
        }

        // Get dist in between
        long distInBetween = K - initDistRan - finalDistRan - Math.min(mid, X);
        // System.out.println(distInBetween);
        if (distInBetween <= 0) return -1;  // Can't speed up / slow down fast enough
        else {
            long extraTimeTaken = (distInBetween + mid - 1) / mid;  // Distance ran in between
            return timeTaken + extraTimeTaken + 1;
        }
    }

    long sumFrom1(int x) {
        return (long) x * (x + 1) / 2;
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("race.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("race.out")));
        new race(in, out);
        in.close();
        out.close();
    }
}