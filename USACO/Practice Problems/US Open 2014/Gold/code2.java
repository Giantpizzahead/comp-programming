import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class code2 {
    // After contest
    final long MOD = 1234567;
    int N, M;
    int[] parent;
    HashSet<String>[] codes;
    HashSet<String>[] neededStates;
    ArrayList<Integer>[] children;

    code2(BufferedReader fin, PrintWriter fout) throws IOException {
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        parent = new int[N];
        parent[0] = -1;
        children = new ArrayList[N];
        codes = new HashSet[N];
        neededStates = new HashSet[N];
        for (int i = 0; i < N; i++) {
            children[i] = new ArrayList<>(2);
            codes[i] = new HashSet<>(2);
            neededStates[i] = new HashSet<>(2);
            neededStates[i].add("");
        }
        for (int i = 1; i < N; i++) {
            int p = Integer.parseInt(fin.readLine());
            parent[i] = p;
            children[p].add(i);
        }
        int v;
        String s;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            v = Integer.parseInt(st.nextToken());
            s = new StringBuilder(st.nextToken()).reverse().toString();
            codes[v].add(s);
            // Add only needed states
            addStates(v, s);
        }

        dp = new HashMap[N];
        for (int i = 0; i < N; i++) dp[i] = new HashMap<>(2);
        long totalCodes = 1;
        for (int i = 0; i < N; i++) totalCodes = totalCodes * 10 % MOD;
        long validCodes = solve(0, "");
        long answer = totalCodes - validCodes;
        if (answer < 0) answer += MOD;

//        for (int i = 0; i < N; i++) {
//            System.out.println(i + ": " + neededStates[i]);
//            System.out.println(dp[i]);
//        }

        fout.println(answer);
    }

    void addStates(int n, String code) {
        code = code.substring(0, code.length() - 1);
        if (code.length() > 0) {
            neededStates[n].add(code);
            addStates(parent[n], code);
        }
    }

    HashMap<String, Integer>[] dp;
    long solve(int n, String code) {
        if (dp[n].containsKey(code)) return dp[n].get(code);
        long numWays = 0;
        for (int i = 0; i < 10; i++) {
            String newCode = code + (char) (i + '0');
            if (!codes[n].contains(newCode)) {
                String tempCode;
                long currWays = 1, tempResult;
                for (int e : children[n]) {
                    tempCode = newCode;
                    // Find most specific state to evaluate
                    while (true) {
                        if (neededStates[e].contains(tempCode)) {
                            if (dp[e].containsKey(tempCode)) tempResult = dp[e].get(tempCode);
                            else tempResult = solve(e, tempCode);
                            currWays = currWays * tempResult % MOD;
                            break;
                        } else {
                            // Make state less specific
                            tempCode = tempCode.substring(1);
                        }
                    }
                }
                numWays += currWays;
            }
        }
        numWays %= MOD;
        dp[n].put(code, (int) numWays);
        return numWays;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("code.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("code.out")));
        new code2(fin, fout);
        fin.close();
        fout.close();
    }
}
