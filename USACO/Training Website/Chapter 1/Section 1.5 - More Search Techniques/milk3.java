/*
ID: sunnyky1
LANG: JAVA
TASK: milk3

Solution: DFS through all possible states, keeping a visited array to not look at each
state more than once. A state is (a, b, c), where those are the amounts of milk in each
bucket.

Runtime: O(20^3)
*/

import java.util.*;
import java.io.*;

public class milk3 {
    int A, B, C;
    boolean[] possible;
    boolean[][][] visited;

    milk3() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        A = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        fin.close();
        
        // DFS through all possible states
        visited = new boolean[A+1][B+1][C+1];
        possible = new boolean[C+1];
        dfs(0, 0, C);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk3.out")));
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < C+1; i++) {
            if (possible[i]) {
                sb.append(i).append(" ");
            }
        }
        fout.println(sb.substring(0, sb.length() - 1));
        fout.close();
    }
    
    void dfs(int a, int b, int c) {
        if (visited[a][b][c]) return;
        visited[a][b][c] = true;

        if (a == 0) possible[c] = true;
        
        // Try pouring from each bucket in turn
        int diff = Math.min(a, B-b);
        dfs(a - diff, b + diff, c);
        diff = Math.min(a, C-b);
        dfs(a - diff, b, c + diff);
        diff = Math.min(b, A-a);
        dfs(a + diff, b - diff, c);
        diff = Math.min(b, C-c);
        dfs(a, b - diff, c + diff);
        diff = Math.min(c, A-a);
        dfs(a + diff, b, c - diff);
        diff = Math.min(c, B-b);
        dfs(a, b + diff, c - diff);
    }

    public static void main(String[] args) throws IOException {
        new milk3();
    }
}
