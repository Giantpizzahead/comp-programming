/*
Solution: Use a divide-and-conquer like approach. Root the tree at node 0,
then split the problem up into the # of paths that include the root, and
the # of paths that stay in each subtree. Use a DFS along with a TreeMap
and deltaing to accomplish this in (I think) amortized O(N * log(N)) time.

Runtime: Theoretically O(N * log(N))
*/

import java.io.*;
import java.util.*;

public class yinyang {
    int N;
    long answer;
    boolean[] visited;
    ArrayList<Edge>[] graph;

    yinyang() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("yinyang.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b, c;
        for (int i = 0; i < N - 1; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            c = Integer.parseInt(st.nextToken());
            graph[a].add(new Edge(b, c == 1));
            graph[b].add(new Edge(a, c == 1));
        }
        fin.close();

        // Divide and conquer!
        visited = new boolean[N];
        visited[0] = true;
        divideAndConquer(0);

        PrintWriter fout = new PrintWriter("yinyang.out");
        fout.println(answer);
        fout.close();
    }

    Data divideAndConquer(int n) {
        // First, divide and conquer child nodes
        ArrayList<Data> stData = new ArrayList<>();
        boolean isLeaf = true;
        int mostValues = 0, mostValuesI = 0;
        for (Edge e : graph[n]) {
            if (!visited[e.n]) {
                visited[e.n] = true;
                isLeaf = false;
                Data currData = divideAndConquer(e.n);
                currData.adjustAll((e.isAngus) ? 1 : -1);
                // System.out.println(currData);
                int dataSize = currData.redBlueRest.size() + currData.redBlueNoRest.size();
                if (dataSize > mostValues) {
                    mostValues = dataSize;
                    mostValuesI = stData.size();
                }
                stData.add(currData);
            }
        }

        if (isLeaf) {
            // Return base data
            Data base = new Data();
            base.add(0, 1);
            return base;
        } else {
            // Combine data of subtrees, adding to answer when needed
            // Goal is to combine data to sum to 0
            Data combinedData = new Data();
            Data currData;
            for (int i = 0; i < stData.size(); i++) {
                if (i == mostValuesI) continue;  // Handle the one with most data last
                currData = stData.get(i);
                // System.out.println("Current: " + currData);
                // System.out.println("Combined: " + combinedData);
                // First, count # of ways to make path ending at curr node
                answer += currData.countRest(0);

                // Next, count # of ways to make path with rest point at curr node
                // (No rest for both subtrees)
                answer += (long) combinedData.countNoRest(0) * currData.countNoRest(0);

                // Now count # of ways to make path between two different subtrees
                // For a valid path to exist, at least 1 st must have rest point
                for (Map.Entry<Integer, Integer> e : currData.redBlueNoRest.entrySet()) {
                    answer += (long) combinedData.countRest(-(e.getKey() - currData.delta)) * e.getValue();
                }
                for (Map.Entry<Integer, Integer> e : currData.redBlueRest.entrySet()) {
                    answer += (long) (combinedData.countRest(-(e.getKey() - currData.delta)) + combinedData.countNoRest(-(e.getKey() - currData.delta)))
                              * e.getValue();
                }

                // Update combinedData
                for (Map.Entry<Integer, Integer> e : currData.redBlueNoRest.entrySet()) {
                    combinedData.add(e.getKey() - currData.delta, e.getValue());
                }
                for (Map.Entry<Integer, Integer> e : currData.redBlueRest.entrySet()) {
                    combinedData.addRest(e.getKey() - currData.delta, e.getValue());
                }

                currData.updateRest();
            }

            // Only update answer for the data with the largest size, to avoid linear time complexity
            currData = stData.get(mostValuesI);

            // First, count # of ways to make path ending at curr node
            answer += currData.countRest(0);

            // Next, count # of ways to make path with rest point at curr node
            // (No rest for both subtrees)
            answer += (long) combinedData.countNoRest(0) * currData.countNoRest(0);

            // Now count # of ways to make path between two different subtrees
            // For a valid path to exist, at least 1 st must have rest point
            for (Map.Entry<Integer, Integer> e : combinedData.redBlueNoRest.entrySet()) {
                answer += (long) currData.countRest(-(e.getKey() - combinedData.delta)) * e.getValue();
            }
            for (Map.Entry<Integer, Integer> e : combinedData.redBlueRest.entrySet()) {
                answer += (long) (currData.countRest(-(e.getKey() - combinedData.delta)) + currData.countNoRest(-(e.getKey() - combinedData.delta)))
                        * e.getValue();
            }

            currData.updateRest();

            // Now merge all the datas and return the merged result
            // Merge into the data with the most values
            Data mergedData = stData.get(mostValuesI);
            for (int i = 0; i < stData.size(); i++) {
                if (i == mostValuesI) continue;

                // Just add everything
                currData = stData.get(i);
                for (Map.Entry<Integer, Integer> e : currData.redBlueNoRest.entrySet()) {
                    mergedData.add(e.getKey() - currData.delta, e.getValue());
                }
                for (Map.Entry<Integer, Integer> e : currData.redBlueRest.entrySet()) {
                    mergedData.addRest(e.getKey() - currData.delta, e.getValue());
                }
            }

            // Add current node
            mergedData.add(0, 1);
//            System.out.println("Data at " + (n+1));
//            System.out.println(mergedData);
//            System.out.println(answer);
            return mergedData;
        }
    }

    public static void main(String[] args) throws IOException {
        new yinyang();
    }
    
    class Data {
        // Store red-blue counts using (#blue - #red) edges
        // Angus edges are blue edges
        TreeMap<Integer, Integer> redBlueNoRest;
        TreeMap<Integer, Integer> redBlueRest;
        Queue<Integer> toUpdate;
        int delta;

        Data() {
            redBlueNoRest = new TreeMap<>();
            redBlueRest = new TreeMap<>();
            toUpdate = new LinkedList<>();
            delta = 0;
        }

        void add(int val, int amount) {
            val += delta;
            redBlueNoRest.put(val, redBlueNoRest.getOrDefault(val, 0) + amount);
        }

        void addRest(int val, int amount) {
            val += delta;
            redBlueRest.put(val, redBlueRest.getOrDefault(val, 0) + amount);
        }
        
        void adjustAll(int val) {
            delta -= val;
            // Move any that now have a rest stop (0 val) to the rest category
            toUpdate.add(delta);
        }

        void updateRest() {
            while (!toUpdate.isEmpty()) {
                int c = toUpdate.poll();
                if (redBlueNoRest.containsKey(delta)) {
                    redBlueRest.put(c, redBlueRest.getOrDefault(c, 0) + redBlueNoRest.remove(c));
                }
            }
        }

        int countNoRest(int val) {
            val += delta;
            return redBlueNoRest.getOrDefault(val, 0);
        }

        int countRest(int val) {
            val += delta;
            return redBlueRest.getOrDefault(val, 0);
        }

        @Override
        public String toString() {
            return "(noRest=" + redBlueNoRest.toString() + ", rest=" + redBlueRest.toString() + ", delta=" + delta + ")";
        }
    }
    
    class Edge {
        int n;
        boolean isAngus;
        Edge(int n, boolean isAngus) {
            this.n = n;
            this.isAngus = isAngus;
        }
    }
}