/*
ID: sunnyky1
LANG: JAVA
TASK: skidesign

Solution: Try every range that's exactly 17.
 */

import java.util.*;
import java.io.*;

public class skidesign {
    int N;
    int[] hills;

    skidesign() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        hills = new int[N];
        for (int i = 0; i < N; i++) {
            hills[i] = Integer.parseInt(fin.readLine());
        }
        fin.close();

        // Try all possible ranges
        int answer = 999999999;
        for (int i = 0; i < 84; i++) {
            answer = Math.min(check(i), answer);
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("skidesign.out")));
        fout.println(answer);
        fout.close();
    }

    int check(int min) {
        int cost = 0;
        int max = min + 17;
        for (int hill : hills) {
            if (hill < min) cost += (min - hill) * (min - hill);
            else if (hill > max) cost += (hill - max) * (hill - max);
        }
        return cost;
    }

    public static void main(String[] args) throws IOException {
        new skidesign();
    }
}
