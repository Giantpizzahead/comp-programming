import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class code {
    final long MOD = 1234567;
    int N, M;
    int[] parent;
    HashSet<Integer>[] codes;
    HashSet<State>[] neededStates;
    ArrayList<Integer>[] children;

    code(BufferedReader fin, PrintWriter fout) throws IOException {
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
            neededStates[i].add(new State(0, 0));
        }
        for (int i = 1; i < N; i++) {
            int p = Integer.parseInt(fin.readLine());
            parent[i] = p;
            children[p].add(i);
        }
        int v, s;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            v = Integer.parseInt(st.nextToken());
            s = Integer.parseInt(new StringBuilder(st.nextToken()).reverse().toString());
            System.out.println(s);
            codes[v].add(s);
            // Add only needed states
            addStates(v, s, 5);
        }

        pow10 = new int[5];
        pow10[0] = 1;
        for (int i = 1; i < 5; i++) pow10[i] = pow10[i-1] * 10;

        dp = new HashMap[N];
        for (int i = 0; i < N; i++) dp[i] = new HashMap<>(2);
        long totalCodes = 1;
        for (int i = 0; i < N; i++) totalCodes = totalCodes * 10 % MOD;
        long validCodes = solve(0, new State(0, 0));
        long answer = totalCodes - validCodes;
        if (answer < 0) answer += MOD;

//        for (int i = 0; i < N; i++) {
//            System.out.println(i + ": " + neededStates[i]);
//            System.out.println(dp[i]);
//        }

        fout.println(answer);
    }

    void addStates(int n, int code, int numDigits) {
        code /= 10;
        numDigits--;
        if (numDigits > 0) {
            neededStates[n].add(new State(code, numDigits));
            addStates(parent[n], code, numDigits);
        }
    }

    HashMap<State, Integer>[] dp;
    int[] pow10;
    long solve(int n, State state) {
        if (dp[n].containsKey(state)) return dp[n].get(state);
        long numWays = 0;
        for (int i = 0; i < 10; i++) {
            int newDigits = state.code * 10 + i;
            if (codes[n].contains(newDigits)) continue;  // Invalid
            else {
                long currWays = 1;
                for (int e : children[n]) {
                    // Find most specific state to evaluate
                    State newState = new State(newDigits, state.numDigits + 1);
                    while (newState.numDigits >= 0) {
                        if (neededStates[e].contains(newState)) {
                            currWays = currWays * solve(e, newState) % MOD;
                            break;
                        } else {
                            // Make state less specific
                            newState.numDigits--;
                            newState.code %= pow10[newState.numDigits];
                        }
                    }
                }
                numWays = (numWays + currWays) % MOD;
            }
        }
        dp[n].put(state, (int) numWays);
        return numWays;
    }

    class State {
        int code, numDigits;
        State(int code, int numDigits) {
            this.code = code;
            this.numDigits = numDigits;
        }

        @Override
        public boolean equals(Object o) {
            State state = (State) o;
            return code == state.code && numDigits == state.numDigits;
        }

        @Override
        public int hashCode() {
            return Objects.hash(code, numDigits);
        }

        @Override
        public String toString() {
            return "(" + code + ", " + numDigits + ")";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("code.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("code.out")));
        new code(fin, fout);
        fin.close();
        fout.close();
    }
}
