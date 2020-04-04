/*
Solution: Simple dp.
dp[i] = Highest possible sum of skill levels of all groups before / including i
dp[0] = arr[0]
dp[i] = dp[i-k] + max(i-k+1, i) * (k - 1) for k = 0...K
Answer: dp[N-1]
By calculating the transition from 0 to K, you can find the max in O(1) (just add current one). So,
final runtime is N states * K to calc each state = O(NK).
*/

import java.util.*;
import java.io.*;

public class teamwork {
    int N, K;
    int[] arr;

    teamwork() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("teamwork.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        arr = new int[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(fin.readLine());
        }
        fin.close();

        int answer = doDP();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("teamwork.out")));
        fout.println(answer);
        fout.close();
    }

    int doDP() {
        int[] dp = new int[N];
        dp[0] = arr[0];
        for (int i = 1; i < N; i++) {
            int nextDP = 0;
            int currMax = 0;
            for (int j = 1; j <= K; j++) {
                currMax = Math.max(arr[i-j+1], currMax);
                if (i-j == -1) {
                    nextDP = Math.max(currMax * j, nextDP);
                    break;
                }
                nextDP = Math.max(dp[i-j] + currMax * j, nextDP);
            }
            dp[i] = nextDP;
        }
        return dp[N-1];
    }

    public static void main(String[] args) throws IOException {
        new teamwork();
    }
}
