/*
Solution: 

Runtime: 
*/

import java.util.*;
import java.io.*;

public class triangleFinder {
    int N, T;
    char[][] grid;

    triangleFinder(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        // T = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int i = 0; i < N; i++) {
            grid[i] = in.readLine().toCharArray();
        }
        for (int x1 = 0; x1 < N; x1++) {
            for (int x2 = 0; x2 < N; x2++) {
                for (int x3 = 0; x3 < N; x3++) {
                    for (int y1 = 0; y1 < N; y1++) {
                        for (int y2 = 0; y2 < N; y2++) {
                            for (int y3 = 0; y3 < N; y3++) {
                                if (dist(x1, y1, x2, y2) == dist(x1, y1, x3, y3) &&
                                    dist(x1, y1, x2, y2) == dist(x2, y2, x3, y3) &&
                                    dist(x1, y1, x2, y2) != 0) {
                                    printTri(x1, y1, x2, y2, x3, y3);
                                }
                            }
                        }
                    }
                }
            }
        }

        System.out.println("Num tris: " + numTris / 6);
    }

    int numTris = 0;
    void printTri(int x1, int y1, int x2, int y2, int x3, int y3) {
        if (grid[y1][x1] == '*' && grid[y2][x2] == '*' && grid[y3][x3] == '*') {
            numTris++;
            char[][] grid = new char[N][N];
            for (int i = 0; i < N; i++) Arrays.fill(grid[i], '.');
            grid[y1][x1] = '*';
            grid[y2][x2] = '*';
            grid[y3][x3] = '*';
            System.out.println();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) System.out.print(grid[i][j]);
                System.out.println();
            }
            System.out.println();
        }

    }

    int dist(int x1, int y1, int x2, int y2) {
        return Math.abs(x2 - x1) + Math.abs(y2 - y1);
    }

    String point(int x, int y) {
        return "(" + x + "," + y + ")";
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("triangleFinder.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("triangleFinder.out")));
        new triangleFinder(in, out);
        in.close();
        out.close();
    }
}
