/*
Solution: Everything's drafted on paper. Basically BFS to find farm track lengths, and DP to solve the problem.
Refer to the paper for more details.

Runtime: O(N/12 * Y^2) -> Probably ok......?
*/

import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class mooriokartredo2 {
    int N, M, X, Y, numFarms;
    long numOver, sumOver;
    int[] numWays;
    ArrayList<Pair>[] graph;
    ArrayList<FarmTrack> farmTracks;
    final long MOD = 1000000007;

    mooriokartredo2() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("cowdate.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        X = Integer.parseInt(st.nextToken());
        Y = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int n1, n2, c;
        for (int i = 0; i < M; i++) {
            st = new StringTokenizer(fin.readLine());
            n1 = Integer.parseInt(st.nextToken()) - 1;
            n2 = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            graph[n1].add(new Pair(n2, c));
            graph[n2].add(new Pair(n1, c));
        }
        fin.close();

        // Generate all farmTracks
        genFarmTracks();

        // System.out.println(farmTracks);

        // Do the DP
        int answer = doDP();

        // for (int i = 0; i < 1000; i++) System.out.println(numCompleteGraphs(i));

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("mooriokart.out")));
        fout.println(answer);
        fout.close();
    }

    int doDP() {
        numFarms = farmTracks.size();
        long[][] dp = new long[numFarms][Y];

        // Base cases
        for (Pair pair : farmTracks.get(0).numWays) {
            dp[0][(int) pair.a] = pair.b;
        }
        numOver = farmTracks.get(0).numOver;
        sumOver = farmTracks.get(0).sumOver;
        long oldNumOver, oldSumOver, tempNumWays;

        // Main DP loop
        for (int i = 0; i < numFarms - 1; i++) {
            // Update over values first
            oldNumOver = numOver;
            oldSumOver = sumOver;
            numOver = 0;
            sumOver = 0;
            /*
            for (Pair pair : farmTracks.get(i+1).numWays) {
                tempNumWays = oldNumOver * pair.b % MOD;
                numOver = (numOver + tempNumWays) % MOD;
                sumOver = (sumOver + tempNumWays * pair.a) % MOD;
            }
             */
            for (int j = 0; j < Y; j++) {
                if (dp[i][j] == 0) continue;
                for (Pair pair : farmTracks.get(i+1).numWays) {
                    int newVal = (int) (j + pair.a);
                    tempNumWays = dp[i][j] * pair.b % MOD;
                    if (newVal < Y) {
                        dp[i+1][newVal] = (dp[i+1][newVal] + tempNumWays) % MOD;
                    } else {
                        // Add to over values
                        numOver = (numOver + tempNumWays) % MOD;
                        sumOver = (sumOver + tempNumWays * newVal) % MOD;
                    }
                }

                // Handle numOver and sumOver of this farm track
                tempNumWays = dp[i][j] * farmTracks.get(i+1).numOver % MOD;
                numOver = (numOver + tempNumWays) % MOD;
                sumOver = (sumOver + dp[i][j] *
                          ((farmTracks.get(i+1).sumOver + farmTracks.get(i+1).numOver * j) % MOD)) % MOD;
            }

            // Consider case of adding each pair to numOver and sumOver
            for (Pair pair : farmTracks.get(i+1).numWays) {
                tempNumWays = oldNumOver * pair.b % MOD;
                numOver = (numOver + tempNumWays) % MOD;
                sumOver = (sumOver + pair.b * (oldNumOver * pair.a % MOD + oldSumOver)) % MOD;
            }

            // Consider case of adding numOver and sumOver of the farm track directly to
            // the numOver and sumOver of the answer
            tempNumWays = oldNumOver * farmTracks.get(i+1).numOver % MOD;
            numOver = (numOver + tempNumWays) % MOD;
            sumOver = (sumOver + (oldNumOver * farmTracks.get(i+1).sumOver) % MOD +
                      (farmTracks.get(i+1).numOver * oldSumOver) % MOD) % MOD;

            /*
            System.out.println("After DP #" + i);
            System.out.println("Next row: " + Arrays.toString(dp[i+1]));
            System.out.println("numOver=" + numOver);
            System.out.println("sumOver=" + sumOver);
             */
        }

        // Multiply by the # of complete graphs possible
        long answer = sumOver * numCompleteGraphs(numFarms) % MOD;

        // Find final power of 2 to multiply by
        long num = 1;
        if (numFarms > 2) {
            for (int i = 0; i < numFarms; i++) {
                num *= 2;
                if (num >= MOD) num -= MOD;
            }
        } else if (numFarms == 2) num = 2;

        return (int) ((answer * num) % MOD);
    }

    int numCompleteGraphs(int numNodes) {
        if (numNodes <= 3) return 1;
        long currFact = 1;
        for (int i = 3; i < numNodes; i++) {
            currFact = currFact * i % MOD;
        }
        return (int) currFact;
    }

    void genFarmTracks() {
        // Floodfill to find all farms
        farmTracks = new ArrayList<>();
        boolean[] visited = new boolean[N];
        for (int i = 0; i < N; i++) {
            if (visited[i]) continue;
            // BFS this farm
            exploreFarm(i, visited);
        }
    }

    void exploreFarm(int start, boolean[] globalVisited) {
        // Run an initial BFS to find all nodes inside the farm
        HashSet<Integer> inFarm = new HashSet<>();
        HashMap<Integer, Integer> nodeToIndex = new HashMap<>();
        Queue<Integer> q = new LinkedList<>();
        q.add(start);
        globalVisited[start] = true;
        int curr, currI = 0;

        while (!q.isEmpty()) {
            curr = q.poll();
            inFarm.add(curr);
            nodeToIndex.put(curr, currI);
            currI++;
            // Neighbors
            for (Pair edge : graph[curr]) {
                if (!globalVisited[(int) edge.a]) {
                    globalVisited[(int) edge.a] = true;
                    q.add((int) edge.a);
                }
            }
        }

        // Store # ways to make different track lengths in int[] array
        numWays = new int[Y];
        numOver = 0;
        sumOver = 0;

        // inFarm now contains all the nodes inside the current farm
        // Run a BFS from each of these nodes
        int numNodesInFarm = nodeToIndex.size();
        for (int n : inFarm) {
            farmBFS(n, numNodesInFarm, nodeToIndex);
        }

        // Remove the paths found with only 1 node
        if (X < Y) numWays[X] -= numNodesInFarm;
        else {
            numOver -= numNodesInFarm;
            sumOver -= numNodesInFarm * X;
        }

        // Each path has been counted twice; divide everything by 2
        for (int i = 0; i < Y; i++) {
            numWays[i] /= 2;
        }
        numOver /= 2;
        sumOver /= 2;

        // Mod sumOver just in case
        sumOver %= MOD;

        // Convert information to FarmTrack instance
        FarmTrack ft = new FarmTrack();
        for (int i = 0; i < Y; i++) {
            if (numWays[i] != 0) ft.numWays.add(new Pair(i, numWays[i]));
        }
        ft.numOver = numOver;
        ft.sumOver = sumOver;
        farmTracks.add(ft);

        // System.out.println(Arrays.toString(numWays));
    }

    void farmBFS(int start, int numNodes, HashMap<Integer, Integer> nti) {
        // Add appropriate numbers to numWays, numOver, and sumOver
        Queue<Pair> q = new LinkedList<>();
        q.add(new Pair(start, 0));
        boolean[] visited = new boolean[numNodes];
        visited[nti.get(start)] = true;
        Pair curr;

        // Main BFS loop
        while (!q.isEmpty()) {
            curr = q.poll();
            // Add to numWays
            int actualTrackLength = (int) (curr.b + X);
            if (actualTrackLength < Y) numWays[actualTrackLength]++;
            else {
                // Over; add to numOver and sumOver values
                numOver++;
                sumOver += actualTrackLength;
            }

            // Neighbors
            for (Pair edge : graph[(int) curr.a]) {
                if (!visited[nti.get((int) edge.a)]) {
                    visited[nti.get((int) edge.a)] = true;
                    q.add(new Pair(edge.a, curr.b + edge.b));
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new mooriokartredo2();
    }

    static class Pair {
        long a, b;
        Pair(long a, long b) {
            this.a = a;
            this.b = b;
        }
        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }

    static class FarmTrack {
        ArrayList<Pair> numWays;
        long numOver, sumOver;
        FarmTrack() {
            numWays = new ArrayList<>();
        }
        @Override
        public String toString() {
            return "FT[" + numWays + ", numOver=" + numOver + ", sumOver=" + sumOver + "]";
        }
    }
}
