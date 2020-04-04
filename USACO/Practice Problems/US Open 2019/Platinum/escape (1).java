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

Runtime: O(NK * ~100?)

Optimization: Precompute all the transitions so you don't have to simulate making the array at every single one.
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class escape {
    int N, K;
    // hCost[2][3] contains horizontal edge in row 2 joining nodes in columns 3 and 4.
    // vCost[2][3] contains vertical edge in column 3 joining nodes in rows 2 and 3.
    int[][] hCost, vCost;
    HashMap<Integer, Pair> map1, map2;
    HashMap<Integer, Integer> newNums = new HashMap<>();
    HashMap<Integer, Transition[][]> transitions = new HashMap<>();
    final long MOD = 1000000007;

    escape() throws IOException {
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

        // Do the most complex DP I think I've ever done
        long answer = doDP();

        PrintWriter fout = new PrintWriter("escape.out");
        fout.println(answer);
        fout.close();
    }

    void precompTrans(int i, int[] arr) {
        if (i == arr.length) {
            // Generate transitions
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
                    currTransitions[j][3] = takeNoEdgesTrans(decodeHash(hash), j + 1);
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

    long doDP() {
        // 132 max states
        map1 = new HashMap<>(133);
        map2 = new HashMap<>(133);
        // Make base cases
        // Take first down edge
        int[] base = new int[K];
        Arrays.fill(base, 1);
        addState(hashArr(base), 0, 1, map1);
        int hash;
        long cost, ways;
        HashMap<Integer, Pair> currStates = map1, nextStates = map2;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= K; j++) {
                // System.out.println("\ni=" + i + ", j=" + j);
                // Evaluate current states
                for (Map.Entry<Integer, Pair> e : currStates.entrySet()) {
                    hash = e.getKey();
                    cost = e.getValue().cost;
                    ways = e.getValue().ways;
                    // System.out.println(Arrays.toString(decodeHash(hash)) + " = (" + cost + ", " + ways + ")");
                    Transition[] currTrans = transitions.get(hash)[j-1];
                    if (j == K) {
                        // Last column
                        // Take first down edge
                        if (currTrans[0] != null) addState(currTrans[0].newHash, cost + vCost[i][1], ways, nextStates);
                        // Don't take edge
                        if (currTrans[1] != null) addState(currTrans[1].newHash, cost, ways, nextStates);
                    } else {
                        // Not last column
                        if (i != 1) {
                            // Take first down edge
                            if (currTrans[0] != null) addState(currTrans[0].newHash, cost + vCost[i-1][j+1], ways, nextStates);
                            // Take both edges
                            if (currTrans[1] != null) addState(currTrans[1].newHash, cost + vCost[i-1][j+1] + hCost[i][j], ways, nextStates);
                        }
                        // Take first left edge
                        if (currTrans[2] != null) addState(currTrans[2].newHash, cost + hCost[i][j], ways, nextStates);
                        // Don't take edge
                        if (currTrans[3] != null) addState(currTrans[3].newHash, cost, ways, nextStates);
                    }
                }

                // Transfer next states to curr states
                HashMap<Integer, Pair> temp = currStates;
                currStates = nextStates;
                nextStates = temp;
                nextStates.clear();
            }
        }

        int[] wanted = new int[K];
        Arrays.fill(wanted, 1);
        // System.out.println("Answer: " + currStates.get(hashArr(wanted)));
        return currStates.get(hashArr(wanted)).ways;
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

    void addState(int hash, long cost, long ways, HashMap<Integer, Pair> map) {
        Pair pair = map.get(hash);
        if (pair != null) {
            if (pair.cost > cost) {
                // This cost is better
                map.put(hash, new Pair(cost, ways));
            } else if (pair.cost == cost) {
                // Sum # of ways
                pair.ways = (pair.ways + ways) % MOD;
            }
        } else {
            // Add a new entry
            map.put(hash, new Pair(cost, ways));
        }
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
        new escape();
    }

    class Pair {
        long cost, ways;
        Pair(long cost, long ways) {
            this.cost = cost;
            this.ways = ways;
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
