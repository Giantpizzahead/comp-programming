/*
Solution: Do a dp-like thing, storing the amount of farmers needed at any given time for each node.
Do one dp for a node's subtrees, and one for everything except the node's subtrees. Base cases are
1 farmer needed at time 0. To merge times from multiple nodes, offset all the node times by 1 (time 4
becomes 3, 0 stays 0), and put all the values into a new TreeSet. This TreeSet only contains partial
sums; to make the final merged values, sum all the values in the TreeSet, making sure to stop once
you reach the min subtree depth. Add a final 1 at the end to track the # needed if 1 farmer can
reach this node at time t.

To generate the up values (all but subtree), at node r, the up value for r's child (n) is either 1
if r's min subtree depth is <= 1, or the result when merging r.up (time offset -1), r.down (time
offset -1), and subtracting n.down (subtraction means time offset -2, value * -1).

Runtime: O(N * sqrt(N) * log(N)) - This is not really possible in worst case, so it's probably ok
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class atlarge {
    int N, root;
    int[] distToLeaf, answers;
    // Keeping a relative dp makes it easier to merge values, so do that
    TreeMap<Integer, Integer>[] dpDownRelative, dpDown, dpUpRelative;
    ArrayList<Integer>[] graph;
    final int INF = 987654321;

    atlarge() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("atlarge.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("atlarge.out")));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        graph = new ArrayList[N];
        for (int i = 0; i < N; i++) graph[i] = new ArrayList<>(2);
        int a, b;
        for (int i = 1; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            a = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken()) - 1;
            graph[a].add(b);
            graph[b].add(a);
        }
        fin.close();

        // Special case: Root is an exit
        root = 0;
        if (graph[root].size() == 1) {
            if (N == 2) {
                // Special special case: Just hardcode this one (output 1 1)
                fout.println("1\n1");
                fout.close();
                return;
            } else root = graph[root].get(0);  // Root is no longer a 'leaf'
        }

        distToLeaf = new int[N];
        Arrays.fill(distToLeaf, INF);
        dpDownRelative = new TreeMap[N];
        dpDown = new TreeMap[N];
        genDPDown(root, root);

        // System.out.println(Arrays.toString(dpDown));
        // System.out.println(Arrays.toString(dpDownRelative));

        dpUpRelative = new TreeMap[N];
        dpUpRelative[root] = new TreeMap<>();
        dpUpRelative[root].put(0, 0);
        answers = new int[N];
        genDPUp(root, root);

        // System.out.println(Arrays.toString(dpUpRelative));

        genAnswers(root, root);

        Arrays.stream(answers).forEach(fout::println);
        fout.close();
    }

    void genAnswers(int n, int p) {
        // Answer is just dpDown[0] + dpUp[0] or 1 if this node is a leaf
        if (distToLeaf[n] == 0) answers[n] = 1;
        else answers[n] = dpDownRelative[n].get(0) + dpUpRelative[n].get(0);

        for (int e : graph[n]) {
            if (e != p) genAnswers(e, n);
        }
    }

    void genDPUp(int n, int p) {
        TreeMap<Integer, Integer> newDPUp = new TreeMap<>();
        // Merge this node's dpUpRelative (time offset -1) and this node's dpDownRelative (time offset -1)
        // if distToLeft > 1
        if (distToLeaf[n] <= 1) {
            // Anything coming up will be stopped here
            newDPUp.put(0, 1);
        } else {
            // Merge the 2 dps
            for (Map.Entry<Integer, Integer> entry : dpDownRelative[n].entrySet()) {
                int newKey = Math.max(entry.getKey() - 1, 0);
                newDPUp.put(newKey, newDPUp.getOrDefault(newKey, 0) + entry.getValue());
            }
            for (Map.Entry<Integer, Integer> entry : dpUpRelative[n].entrySet()) {
                int newKey = Math.max(entry.getKey() - 1, 0);
                newDPUp.put(newKey, newDPUp.getOrDefault(newKey, 0) + entry.getValue());
            }
        }

        // Make dpUp values for children
        for (int e : graph[n]) {
            if (e != p) {
                dpUpRelative[e] = new TreeMap<>(newDPUp);
                if (distToLeaf[n] > 1) {
                    // Subtract this node's dpDownRelative (time offset -2, value *-1)
                    for (Map.Entry<Integer, Integer> entry : dpDownRelative[e].entrySet()) {
                        int newKey = Math.max(entry.getKey() - 2, 0);
                        dpUpRelative[e].put(newKey, dpUpRelative[e].getOrDefault(newKey, 0) - entry.getValue());
                    }
                }

                genDPUp(e, n);
            }
        }
    }

    void genDPDown(int n, int p) {
        TreeMap<Integer, Integer> newDPRelative = new TreeMap<>();
        boolean isLeaf = true;
        for (int e : graph[n]) {
            if (e != p) {
                genDPDown(e, n);
                isLeaf = false;
                // Merge child values with current values; remember the -1 offset!
                for (Map.Entry<Integer, Integer> entry : dpDownRelative[e].entrySet()) {
                    int newKey = Math.max(entry.getKey() - 1, 0);
                    newDPRelative.put(newKey, newDPRelative.getOrDefault(newKey, 0) + entry.getValue());
                }
                // To save memory, delete relative as it's not needed anymore
                // dpDownRelative[e].clear();
                // Update distance to leaf
                distToLeaf[n] = Math.min(distToLeaf[e] + 1, distToLeaf[n]);
            }
        }

        if (isLeaf) {
            // Base case
            newDPRelative.put(0, 1);
            distToLeaf[n] = 0;
            dpDown[n] = newDPRelative;
        } else {
            // Make actual dpDown
            dpDown[n] = new TreeMap<>();
            int currSum = 0;
            for (Map.Entry<Integer, Integer> entry : newDPRelative.entrySet()) {
                if (entry.getKey() >= distToLeaf[n]) break;  // No need to add any more entries
                // Add new entry
                currSum += entry.getValue();
                dpDown[n].put(entry.getKey(), currSum);
            }

            // Remove extra relative entries
            Map.Entry<Integer, Integer> tempEntry = newDPRelative.lastEntry();
            while (tempEntry != null && tempEntry.getKey() >= distToLeaf[n]) {
                newDPRelative.pollLastEntry();
                tempEntry = newDPRelative.lastEntry();
            }

            // Add final entry to both absolute and relative
            if (currSum != 1) {
                newDPRelative.put(distToLeaf[n], -currSum + 1);
                dpDown[n].put(distToLeaf[n], 1);
            }
        }

        dpDownRelative[n] = newDPRelative;
    }

    public static void main(String[] args) throws IOException {
        new atlarge();
    }
}
