/*
Solution: Separate the regions into "light" and "heavy" regions. Then, do some precomp
to process queries involving at least 1 heavy region in O(1) time. Do light to light
queries online in O(N) time (where N is the # of nodes with those light regions).

Assuming a heavy region is >=500 nodes (motivated by subtasks).
Runtime: O(1000Q + 400N)
*/

import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class regions2 {
    final int HEAVY = 625;
    int N, R, Q, numHeavy = 0, numLight = 0;
    int[] region, regionCount;
    int[][] heavyToAny, lightToHeavy;
    ArrayList<Integer>[] adj;
    ArrayList<Pair>[] lightData;

    regions2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        R = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        adj = new ArrayList[N];
        for (int i = 0; i < N; i++) adj[i] = new ArrayList<>(2);

        region = new int[N];
        regionCount = new int[R];
        region[0] = Integer.parseInt(in.readLine()) - 1;
        regionCount[region[0]]++;
        int p;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            p = Integer.parseInt(st.nextToken()) - 1;
            region[i] = Integer.parseInt(st.nextToken()) - 1;
            regionCount[region[i]]++;
            adj[p].add(i);
        }

        // Figure out which regions are heavy
        int[] regionToNewI = new int[R];
        for (int i = 0; i < R; i++) {
            if (regionCount[i] >= HEAVY) {
                // Heavy region
                regionToNewI[i] = numHeavy++;
            } else {
                // Light region
                regionToNewI[i] = R - 1 - numLight++;
            }
        }
        // System.out.println(Arrays.toString(regionToNewI));

        // Relabel regions in the new ordering (heavy regions are first)
        for (int i = 0; i < N; i++) region[i] = regionToNewI[region[i]];

        // Precomputation for (H, H) and (H, L) queries
        heavyToAny = new int[numHeavy][R];
        heavyAnc = new int[numHeavy];
        precompHeavy(0);

        // Precomputation for (L, H) [and technically (H, H)] queries
        lightToHeavy = new int[R][numHeavy];
        precompLightToHeavy(0);

        // Precomputation for (L, L) queries
        lightData = new ArrayList[R];
        for (int i = 0; i < R; i++) lightData[i] = new ArrayList<>(2);
        genLightData(0);

        // Finally, answer the queries!
        int a, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            a = regionToNewI[Integer.parseInt(st.nextToken()) - 1];
            b = regionToNewI[Integer.parseInt(st.nextToken()) - 1];
            if (a < numHeavy) {
                // Heavy to any
                // System.out.println("hta");
                out.println(heavyToAny[a][b]);
                out.flush();
            } else if (b < numHeavy) {
                // Light to heavy
                // System.out.println("lth");
                out.println(lightToHeavy[a][b]);
                out.flush();
            } else {
                // Light to light; calculate answer
                // System.out.println("ltl");
                out.println(calcLTL(a, b));
                out.flush();
            }
        }
    }

    int calcLTL(int a, int b) {
        ArrayList<Pair> aRanges = lightData[a];
        ArrayList<Pair> bRanges = lightData[b];
        if (bRanges.size() == 0) return 0;
        int currCount = 0, bi = 0, answer = 0;
        Pair p;
        for (Pair aRange : aRanges) {
            p = aRange;
            while (bRanges.get(bi).i <= p.i) {
                if (bRanges.get(bi).v == 1) answer += currCount;
                bi++;
                if (bi == bRanges.size()) return answer;
            }
            currCount += p.v;
        }
        return answer;
    }

    int[] heavyAnc;
    void precompHeavy(int n) {
        // Update this node's region count by # heavy ancestors
        for (int i = 0; i < numHeavy; i++) heavyToAny[i][region[n]] += heavyAnc[i];
        // Add this node (if appropriate) to ancestor count
        if (region[n] < numHeavy) heavyAnc[region[n]]++;
        for (int e : adj[n]) {
            precompHeavy(e);
        }
        // Backtracking
        if (region[n] < numHeavy) heavyAnc[region[n]]--;
    }

    HashMap<Integer, Integer> precompLightToHeavy(int n) {
        if (adj[n].size() == 0) {
            // Leaf node
            HashMap<Integer, Integer> currST = new HashMap<>(2);
            if (region[n] < numHeavy) currST.put(region[n], 1);
            return currST;
        }
        // Find # nodes from each heavy region in subtree
        int maxSize = -1, maxI = -1;
        HashMap<Integer, Integer>[] childSTs = new HashMap[adj[n].size()];
        for (int i = 0; i < adj[n].size(); i++) {
            int e = adj[n].get(i);
            childSTs[i] = precompLightToHeavy(e);
            if (childSTs[i].size() > maxSize) {
                maxSize = childSTs[i].size();
                maxI = i;
            }
        }
        // Merge child maps
        HashMap<Integer, Integer> currST = childSTs[maxI];
        for (int i = 0; i < adj[n].size(); i++) {
            if (i != maxI) {
                for (Map.Entry<Integer, Integer> entry : childSTs[i].entrySet()) {
                    currST.put(entry.getKey(), currST.getOrDefault(entry.getKey(), 0) + entry.getValue());
                }
                childSTs[i].clear();
            }
        }
        // Update light to heavy query counts
        for (Map.Entry<Integer, Integer> entry : currST.entrySet()) {
            lightToHeavy[region[n]][entry.getKey()] += entry.getValue();
        }
        // Add this node (if appropriate)
        if (region[n] < numHeavy) currST.put(region[n], currST.getOrDefault(region[n], 0) + 1);
        return currST;
    }

    int clabel = 0;
    void genLightData(int n) {
        lightData[region[n]].add(new Pair(clabel++, 1));
        for (int e : adj[n]) genLightData(e);
        lightData[region[n]].add(new Pair(clabel - 1, -1));
    }

    static class Pair {
        int i, v;
        Pair(int i, int v) {
            this.i = i;
            this.v = v;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("regions.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("regions.out")));
        new regions2(in, out);
        in.close();
        out.close();
    }
}