import java.util.*;
import java.io.*;

public class gourmet {
    int N, M, nodeN, compN;
    int[] compID, inEdges, dishScores;
    boolean[][] adj, rawAdj, equalAdj;

    gourmet(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        nodeN = N + M;
        rawAdj = new boolean[nodeN][nodeN];
        equalAdj = new boolean[nodeN][nodeN];
        for (int i = 0; i < N; i++) {
            String str = in.readLine();
            for (int j = 0; j < M; j++) {
                char c = str.charAt(j);
                if (c == '>') {
                    rawAdj[N+j][i] = true;
                } else if (c == '<') {
                    rawAdj[i][N+j] = true;
                } else {
                    equalAdj[N+j][i] = true;
                    equalAdj[i][N+j] = true;
                }
            }
        }

        // Generate components
        compN = 0;
        compID = new int[nodeN];
        Arrays.fill(compID, -1);
        for (int i = 0; i < nodeN; i++) {
            if (compID[i] == -1) dfsComp(i, compN++);
        }

        // Now, create the actual graph using these components
        adj = new boolean[compN][compN];
        inEdges = new int[compN];
        for (int i = 0; i < nodeN; i++) {
            for (int j = 0; j < nodeN; j++) {
                if (rawAdj[i][j] && !adj[compID[i]][compID[j]]) {
                    inEdges[compID[j]]++;
                    adj[compID[i]][compID[j]] = true;
                }
            }
        }

        // Generate topological ordering (if possible)
        dishScores = new int[compN];
        for (int i = 0; i < compN; i++) {
            if (inEdges[i] == 0) {
                toEval.add(i);
                dishScores[i] = 1;
            }
        }

        int c;
        while (!toEval.isEmpty()) {
            c = toEval.poll();
            // Spread to neighbors
            for (int i = 0; i < compN; i++) {
                if (adj[c][i]) {
                    inEdges[i]--;
                    if (inEdges[i] == 0) {
                        dishScores[i] = dishScores[c] + 1;
                        toEval.add(i);
                    }
                }
            }
        }

        // If it got here, this is probably valid...?
        // System.out.println(Arrays.toString(inEdges));
        for (int i = 0; i < compN; i++) {
            if (inEdges[i] != 0) {
                // Not all dishes were rated (cycle exists)
                out.println("No");
                return;
            }
        }

        // Valid
        out.println("Yes");
        for (int i = 0; i < nodeN; i++) {
            if (i == N) out.println();
            else if (i != 0) out.print(' ');
            out.print(dishScores[compID[i]]);
        }
        out.println();
    }

    void dfsComp(int n, int id) {
        compID[n] = id;
        for (int i = 0; i < nodeN; i++) {
            if (equalAdj[n][i] && compID[i] == -1) dfsComp(i, id);
        }
    }

    boolean[] checked;
    boolean checkEqual(int n) {
        checked[n] = true;
        for (int i = 0; i < nodeN; i++) {
            if (equalAdj[n][i] && !checked[i]) {
                if (dishScores[i] != dishScores[n]) return false;
                else if (!checkEqual(i)) return false;
            }
        }
        return true;
    }

    Queue<Integer> toEval = new LinkedList<>();

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new gourmet(in, out);
        in.close();
        out.close();
    }
}
