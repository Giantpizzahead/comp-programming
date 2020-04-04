/*
Solution: 1st cow decides the rest, so try every single first cow.
Runtime: O(N^2)
*/

import java.util.*;
import java.io.*;

public class photo {
    int N;
    int[] sums, cows;

    photo(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        sums = new int[N - 1];
        for (int i = 0; i < N - 1; i++) {
            sums[i] = Integer.parseInt(st.nextToken());
        }

        for (int i = 1; i <= N; i++) {
            cows = new int[N];
            cows[0] = i;
            boolean[] used = new boolean[N + 1];
            used[i] = true;
            boolean valid = true;
            for (int j = 1; j < N; j++) {
                cows[j] = sums[j-1] - cows[j-1];
                if (cows[j] > N || cows[j] < 1 || used[cows[j]]) {
                    valid = false;
                    break;
                } else used[cows[j]] = true;
            }

            // System.out.println(Arrays.toString(cows));

            if (valid) {
                for (int j = 0; j < N; j++) {
                    if (j != 0) out.print(' ');
                    out.print(cows[j]);
                }
                break;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("photo.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("photo.out")));
        new photo(in, out);
        in.close();
        out.close();
    }
}