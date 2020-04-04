/*
ID: sunnyky1
LANG: JAVA
TASK: concom

Solution: Make a graph out of the given triples. Try starting from each
node (company), and recursively branching out to see which companies
that node controls.

Runtime: O(N^3)
*/

import java.util.*;
import java.io.*;

public class concom {
    int N;
    int[][] graph;
    final int NUM_COMPS = 100;

    concom() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("concom.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        graph = new int[NUM_COMPS][NUM_COMPS];
        N = Integer.parseInt(st.nextToken());
        int i, j, p;
        for (int x = 0; x < N; x++) {
            st = new StringTokenizer(fin.readLine());
            i = Integer.parseInt(st.nextToken()) - 1;
            j = Integer.parseInt(st.nextToken()) - 1;
            p = Integer.parseInt(st.nextToken());
            graph[i][j] += p;
        }
        fin.close();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("concom.out")));
        for (int x = 0; x < NUM_COMPS; x++) {
            ArrayList<Integer> comps = findComps(x);
            comps.sort(Comparator.naturalOrder());
            for (int o : comps) fout.println((x+1) + " " + (o+1));
        }
        fout.close();
    }

    ArrayList<Integer> findComps(int n) {
        ArrayList<Integer> comps = new ArrayList<>();
        int[] percentControlled = new int[NUM_COMPS];
        boolean[] controlled = new boolean[NUM_COMPS];
        percentControlled[n] = 100;
        controlled[n] = true;

        Queue<Integer> q = new LinkedList<>();
        q.add(n);
        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            for (int i = 0; i < NUM_COMPS; i++) {
                if (!controlled[i]) {
                    percentControlled[i] += graph[c][i];
                    if (percentControlled[i] > 50) {
                        controlled[i] = true;
                        comps.add(i);
                        q.add(i);
                    }
                }
            }
        }

        return comps;
    }

    public static void main(String[] args) throws IOException {
        new concom();
    }
}