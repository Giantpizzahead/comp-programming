/*
Solution: This is a really complicated DP problem. The idea is simple, but... let's just say the
implementation is gonna be a bit of an issue.

dp[i][j][state] = Min cost escape plan including all nodes from row 1 to i-1, and all nodes in row
i from 1 to j. Row i's connectivity is currently in the given state (remaining unevaluated nodes
contain connectivity from previous row). Also track the # of min cost escape plans.

BC: dp[0][K][1 2 3 4 5 6] = 0 cost, 1 way
Note: To make implementation easier, add an extra row at the start with all 0 cost vert edges.

Transitions: I don't wanna list them in detail, but it's on my drafting paper so... yeah.
(Forward DP)
dp[i][j][state] -> If j == K, dp[i+1][1][state] and dp[i+1][1][state with down edge]
Else, dp[i][j+1][state], dp[i][j+1][state with down edge], dp[i][j+1][state with left edge], and
dp[i][j+1][state with both edges].

Answer: dp[N][K][1 1 1 1 1 1] (# ways)

For implementation purposes, use a HashMap to track the states.

Runtime: O(133NK)

Optimization: Precompute all the transitions so you don't have to simulate making the array at every single one.
*/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

@SuppressWarnings("unchecked")
public class escapeArr {
    int N, K, currDPI, onRow, time = 0;
    // hCost[2][3] contains horizontal edge in row 2 joining nodes in columns 3 and 4.
    // vCost[2][3] contains vertical edge in column 3 joining nodes in rows 2 and 3.
    int[][] hCost, vCost;
    Pair[][] dp;
    HashMap<Integer, Integer> newNums = new HashMap<>(), hashToI = new HashMap<>(500);
    int[] iToHash = new int[133];
    HashMap<Integer, Transition[][]> transitions = new HashMap<>(500);
    final long MOD = 1000000007;

    escapeArr() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("escape.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        hCost = new int[N+1][K+1];
        for (int y = 1; y <= N; y++) {
            st = new StringTokenizer(fin.readLine());
            for (int x = 1; x < K; x++) {
                hCost[y][x] = Integer.parseInt(st.nextToken());
            }
        }
        vCost = new int[N+1][K+1];
        for (int x = 1; x <= K; x++) {
            st = new StringTokenizer(fin.readLine());
            for (int y = 1; y < N; y++) {
                vCost[y][x] = Integer.parseInt(st.nextToken());
            }
        }
        fin.close();

//        for (int i = 0; i <= N; i++) System.out.println(Arrays.toString(hCost[i]));
//        System.out.println();
//        for (int i = 0; i <= N; i++) System.out.println(Arrays.toString(vCost[i]));

        // Precompute all possible transitions
        precompTrans(0, new int[K]);
        // System.out.println(transitions.size());

        // Do the most complex DP I think I've ever done
        long answer = doDP();

        PrintWriter fout = new PrintWriter("escape.out");
        fout.println(answer);
        fout.close();
    }

    void precompTrans(int i, int[] arr) {
        if (i == arr.length) {
            // Generate transitions if needed
            if (!check(arr)) return;
            int hash = hashArr(arr);
            Transition[][] currTransitions = new Transition[K][];
            // Iterate through each column
            for (int j = 0; j < K; j++) {
                if (j == K - 1) {
                    // Last column
                    currTransitions[j] = new Transition[2];
                    // Take first down edge
                    currTransitions[j][0] = takeDownEdgeTrans(decodeHash(hash));
                    // Don't take edge
                    currTransitions[j][1] = takeNoEdgesTrans(decodeHash(hash), 0);
                } else {
                    currTransitions[j] = new Transition[4];
                    // Take first down edge
                    currTransitions[j][0] = takeDownEdgeTrans(decodeHash(hash));
                    // Take both edges
                    currTransitions[j][1] = takeBothEdgesTrans(decodeHash(hash), j + 1);
                    // Take first left edge
                    currTransitions[j][2] = takeLeftEdgeTrans(decodeHash(hash), j + 1);
                    // Don't take edge
                    if (currTransitions[j][2] != null) currTransitions[j][3] = takeNoEdgesTrans(decodeHash(hash), j + 1);
                }
            }

            // Add transitions to HashMap
            transitions.put(hash, currTransitions);
        } else {
            for (int j = 1; j <= i + 1; j++) {
                arr[i] = j;
                precompTrans(i + 1, arr);
            }
        }
    }

    boolean check(int[] arr) {
        int[] locEnd = new int[K];
        int onNum = -1, x;
        for (int i = 0; i < arr.length; i++) {
            x = arr[i] - 1;
            if (locEnd[x] == 0) onNum++;
            if (x > onNum) return false;
            locEnd[x] = i+1;
        }

        boolean[] started = new boolean[K];
        Stack<Integer> s = new Stack<>();
        for (int i = 0; i < arr.length; i++) {
            x = arr[i]-1;
            if (!started[x]) {
                started[x] = true;
                s.push(x);
            }
            if (locEnd[x]-1 == i) {
                if (s.pop() != x) return false;
            }
        }
        return true;
    }

    long doDP() {
        // 132 max states
        dp = new Pair[2][133];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 133; j++) dp[i][j] = new Pair(0, 0, -1);
        }
        currDPI = 0;
        onRow = 1;
        // Make base cases
        // Take first down edge
        int[] base = new int[K];
        Arrays.fill(base, 1);
        addState(hashArr(base), 0, 1);
        onRow = 0;
        int hash, ways;
        long cost;
        for (int i = 1; i <= N; i++) {
            if (i % 2000 == 0) System.out.println("DP " + i);
            for (int j = 1; j <= K; j++) {
                time++;
                // System.out.println("\ni=" + i + ", j=" + j);
                // System.out.println(Arrays.toString(dp[onRow]));
                // Evaluate current states
                for (int k = 0; k < 133; k++) {
                    if (dp[onRow][k].lastUsed != time - 1) continue;
                    cost = dp[onRow][k].cost;
                    ways = dp[onRow][k].ways;
                    // System.out.println(Arrays.toString(decodeHash(hash)) + " = (" + cost + ", " + ways + ")");
                    Transition[] currTrans = transitions.get(iToHash[k])[j-1];
                    // System.out.println(Arrays.toString(currTrans));
                    if (j == K) {
                        // Last column
                        // Take first down edge
                        addState(currTrans[0].newHash, cost + vCost[i][1], ways);
                        // Don't take edge
                        if (currTrans[1] != null) addState(currTrans[1].newHash, cost, ways);
                    } else {
                        // Not last column
                        if (i != 1) {
                            // Take first down edge
                            addState(currTrans[0].newHash, cost + vCost[i-1][j+1], ways);
                            // Take both edges
                            addState(currTrans[1].newHash, cost + vCost[i-1][j+1] + hCost[i][j], ways);
                        }
                        if (currTrans[2] != null) {
                            // Take first left edge
                            addState(currTrans[2].newHash, cost + hCost[i][j], ways);
                            // Don't take edge
                            addState(currTrans[3].newHash, cost, ways);
                        }
                    }
                }

                // Transfer dp row
                onRow = 1 - onRow;
            }
        }

        Arrays.fill(base, 1);
        // System.out.println("Answer: " + currStates.get(hashArr(wanted)));
        return dp[1 - onRow][hashToI.get(hashArr(base))].ways;
    }

    void addState(int hash, long cost, int ways) {
        if (time < 16 && !hashToI.containsKey(hash)) {
            // Add new index to dp
            hashToI.put(hash, currDPI);
            iToHash[currDPI++] = hash;
            // System.out.println(hashToI);
            // System.out.println(Arrays.toString(iToHash));
        }
        int i = hashToI.get(hash);
        Pair pair = dp[1 - onRow][i];
        if (pair.lastUsed != time) {
            // Reset everything
            pair.cost = cost;
            pair.ways = ways;
            pair.lastUsed = time;
        } else {
            if (pair.cost > cost) {
                // This cost is better
                pair.cost = cost;
                pair.ways = ways;
            } else if (pair.cost == cost) {
                // Sum # of ways
                pair.ways += ways;
                if (pair.ways > MOD) pair.ways -= MOD;
            }
        }
    }

    Transition takeDownEdgeTrans(int[] arr) {
        // System.out.println("Down edge = " + Arrays.toString(decodeHash(hash)) + " -> " + cost);
        return new Transition(hashArr(arr), false, true);
    }

    Transition takeBothEdgesTrans(int[] arr, int column) {
        newNums.clear();
        int currNum = 1, numToSwitch = arr[column], numToSwitchTo = arr[column - 1];
        for (int i = 0; i < arr.length; i++) {
            // Adjust number if needed
            if (arr[i] == numToSwitch) arr[i] = numToSwitchTo;
            if (!newNums.containsKey(arr[i])) {
                newNums.put(arr[i], currNum++);
            }
            arr[i] = newNums.get(arr[i]);
        }

        // System.out.println("Both edges = " + Arrays.toString(arr) + " -> " + cost);
        return new Transition(hashArr(arr), true, true);
    }

    Transition takeLeftEdgeTrans(int[] arr, int column) {
        newNums.clear();
        int currNum = 1, numToChange = arr[column];
        arr[column] = arr[column - 1];
        boolean numChanged = false;
        for (int i = 0; i < arr.length; i++) {
            // Adjust number if needed
            if (arr[i] == numToChange) numChanged = true;
            if (!newNums.containsKey(arr[i])) {
                newNums.put(arr[i], currNum++);
            }
            arr[i] = newNums.get(arr[i]);
        }

        if (!numChanged) return null;

        // System.out.println("Left edge = " + Arrays.toString(arr) + " -> " + cost);
        return new Transition(hashArr(arr), true, false);
    }

    Transition takeNoEdgesTrans(int[] arr, int column) {
        newNums.clear();
        int currNum = 1, numToChange = arr[column];
        arr[column] = 7;  // This node is now isolated since no edges were taken
        boolean numChanged = false;
        for (int i = 0; i < arr.length; i++) {
            // Adjust number if needed
            if (arr[i] == numToChange) numChanged = true;
            if (!newNums.containsKey(arr[i])) {
                newNums.put(arr[i], currNum++);
            }
            arr[i] = newNums.get(arr[i]);
        }

        if (!numChanged) return null;
        // System.out.println("No edge = " + Arrays.toString(arr) + " -> " + cost);
        return new Transition(hashArr(arr), false, false);
    }

    int hashArr(int[] arr) {
        int hash = 0;
        for (int i = 0, j = 1; i < arr.length; i++, j *= 7) hash += arr[i] * j;
        return hash;
    }

    int[] decodeHash(int hash) {
        int[] decoded = new int[K];
        for (int i = 0; i < K; i++) {
            decoded[i] = hash % 7;
            hash /= 7;
        }
        return decoded;
    }

    public static void main(String[] args) throws IOException {
        new escapeArr();
    }

    class Pair {
        long cost;
        int ways, lastUsed = 0;
        Pair(long cost, int ways, int lastUsed) {
            this.cost = cost;
            this.ways = ways;
            this.lastUsed = lastUsed;
        }
        @Override
        public String toString() {
            return "(" + cost + ", " + ways + ")";
        }
    }

    class Transition {
        int newHash;
        boolean needHCost, needVCost;
        public Transition(int newHash, boolean needHCost, boolean needVCost) {
            this.newHash = newHash;
            this.needHCost = needHCost;
            this.needVCost = needVCost;
        }
        @Override
        public String toString() {
            return "(" + Arrays.toString(decodeHash(newHash)) + ")";
        }
    }
}
