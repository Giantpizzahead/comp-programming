/*
Solution: Do a Dijkstra-like algorithm, branching out from each christmas tree. Greedily place people at the closest
points possible, and continue to branch out until enough people have been placed.

Since the coordinate space is way too big, use a HashSet to determine which locations have already been visited.

Runtime: O(N + M)
*/

import java.io.*;
import java.util.*;

public class xmastrees {
    int N, M;
    HashSet<Integer> visited = new HashSet<>();
    int[] trees;
    long distSum;
    ArrayList<Integer> peopleLocs;

    xmastrees() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        trees = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            trees[i] = Integer.parseInt(st.nextToken());
            visited.add(trees[i]);
        }
        in.close();
        placePeople();
        PrintWriter out = new PrintWriter(System.out);
        out.println(distSum);
        for (int i = 0; i < M; i++) {
            out.print(peopleLocs.get(i));
            if (i != M - 1) out.print(' ');
            else out.println();
        }
        out.close();
    }

    void placePeople() {
        distSum = 0;
        peopleLocs = new ArrayList<>(M);
        int currCost = 1, currLeft = 0, nextLeft = 0;
        Queue<Integer> q = new LinkedList<>();
        for (int tree : trees) {
            if (!visited.contains(tree - 1)) {
                visited.add(tree - 1);
                q.add(tree - 1);
                currLeft++;
            }
            if (!visited.contains(tree + 1)) {
                visited.add(tree + 1);
                q.add(tree + 1);
                currLeft++;
            }
        }

        int numPlaced = 0;
        while (!q.isEmpty()) {
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;
            int c = q.poll();
            peopleLocs.add(c);
            distSum += currCost;
            if (++numPlaced == M) break;
            // Search neighbors
            if (!visited.contains(c-1)) {
                visited.add(c-1);
                q.add(c-1);
                nextLeft++;
            }
            if (!visited.contains(c+1)) {
                visited.add(c+1);
                q.add(c+1);
                nextLeft++;
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new xmastrees();
    }
}
