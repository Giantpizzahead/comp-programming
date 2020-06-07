import java.io.*;
import java.util.*;

public class datacenter {
    int R, C;
    char[][] grid, diags;
    DisjointSet ds;

    datacenter(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        grid = new char[R][];
        ds = new DisjointSet(R * C);

        for (int i = 0; i < R; i++) {
            grid[i] = in.readLine().toCharArray();
        }

        // Initial unions
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (i != 0 && grid[i-1][j] == grid[i][j]) {
                    ds.union(hash(i-1, j), hash(i, j));
                }
                if (j != 0 && grid[i][j-1] == grid[i][j]) {
                    ds.union(hash(i, j-1), hash(i, j));
                }
            }
        }

        // Greedily add diagonals
        diags = new char[R-1][C-1];
        for (int i = 0; i < R-1; i++) {
            for (int j = 0; j < C-1; j++) {
                if (grid[i][j] == grid[i+1][j+1] && ds.find(hash(i, j)) != ds.find(hash(i+1, j+1))) {
                    ds.union(hash(i, j), hash(i+1, j+1));
                    diags[i][j] = '\\';
                } else if (grid[i][j+1] == grid[i+1][j] && ds.find(hash(i, j+1)) != ds.find(hash(i+1, j))) {
                    ds.union(hash(i, j+1), hash(i+1, j));
                    diags[i][j] = '/';
                } else diags[i][j] = '.';
            }
        }

        if (ds.numComps == 2) {
            out.printf("Case #%d: POSSIBLE\n", tn);
            for (int i = 0; i < R-1; i++) {
                for (int j = 0; j < C-1; j++) {
                    out.print(diags[i][j]);
                }
                out.println();
            }
        } else {
            out.printf("Case #%d: IMPOSSIBLE\n", tn);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new datacenter(in, out, i);
        in.close();
        out.close();
    }

    int hash(int i, int j) {
        return i * C + j;
    }

    class DisjointSet {
        int size, numComps;
        int[] arr;
        DisjointSet(int size) {
            this.size = size;
            this.numComps = size;
            arr = new int[size];
            Arrays.fill(arr, -1);
        }

        void union(int a, int b) {
            int setA = find(a);
            int setB = find(b);
            if (setA == setB) return;
            else if (arr[setA] < arr[setB]) {
                if (arr[setA] == arr[setB]) arr[setA]--;
                arr[setB] = setA;
            } else {
                if (arr[setB] == arr[setA]) arr[setB]--;
                arr[setA] = setB;
            }
            numComps--;
        }

        int find(int i) {
            if (arr[i] < 0) return i;
            else {
                int res = find(arr[i]);
                arr[i] = res;
                return res;
            }
        }
    }
}
