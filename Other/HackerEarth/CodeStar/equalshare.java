package CodeStar;/*
Solution: Sort points, multiply each in between to get answer
*/

import java.util.*;
import java.io.*;

public class equalshare {
    int N, K;
    int[] gems;

    equalshare() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        gems = new int[N];
        for (int i = 0; i < N; i++) {
            gems[i] = Integer.parseInt(st.nextToken());
        }
        in.close();
        Arrays.sort(gems);

        int numToSkip = N / K;
        long answer = 1;
        for (int i = numToSkip; i < N; i += numToSkip) {
            answer *= (gems[i] - gems[i-1] - 1);
            answer %= 1000007;
        }

        System.out.println(answer);
    }

    public static void main(String[] args) throws IOException {
        new equalshare();
    }
}
