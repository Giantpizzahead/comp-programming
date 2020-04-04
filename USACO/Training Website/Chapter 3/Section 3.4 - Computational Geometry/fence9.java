/*
ID: sunnyky1
LANG: JAVA
TASK: fence9

Solution: Sweep through the triangle, tracking the top and bottom points as doubles. At
every x coordinate, compute the # of cows that can be placed at that x inside the
triangle.
Runtime: O(max(N, P))
*/

import java.util.*;
import java.io.*;

public class fence9 {
    int N, M, P;

    fence9(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());
        long answer = 0;
        for (int i = 1; i < Math.max(N, P); i++) {
            int topFloor = (int) (findTopLoc(i) - 0.000000001);
            int botCeil = (int) Math.ceil(findBotLoc(i) + 0.000000001);
            // System.out.println(i + " -> " + topFloor + ", " + botCeil);
            answer += Math.max(topFloor - botCeil + 1, 0);
        }
        out.println(answer);
    }

    double findTopLoc(int i) {
        if (i <= N) return (double) i * M / N;
        else return (double) M + (double) (i - N) * M / (N - P);
    }

    double findBotLoc(int i) {
        if (i <= P) return 0;
        else return (double) (i - P) * M / (N - P);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("fence9.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fence9.out")));
        new fence9(in, out);
        in.close();
        out.close();
    }
}
