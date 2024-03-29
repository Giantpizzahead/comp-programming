/*
Solution: All equilateral triples must have two points on the same diagonal line. So, count them
using the diagonals. Make sure to not overcount the triples with a straight line as one of their
sides.
Runtime: O(N^3)
*/

import java.io.*;
import java.util.StringTokenizer;

public class triangles2 {
    int N;
    char[][] grid;

    triangles2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new char[N][];
        for (int i = 0; i < N; i++) {
            grid[i] = in.readLine().toCharArray();
        }

        // System.out.println(moveUL(new Point(2, 3), 4));

        long totalCount = 0;
        for (int i = 0; i < 4; i++) {
            // Count # of triples with at least 1 / diagonal on bottom right
            long diagCount = countDiags();
            // System.out.println("Diag count: " + diagCount);
            totalCount += diagCount;

            // Rotate the board 90 degrees
            char[][] newGrid = new char[N][N];
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    newGrid[y][x] = grid[x][N - 1 - y];
                }
            }
            grid = newGrid;
            // printGrid(newGrid);
        }

        // Finally, count the # of overcounted triples
        long overcount = 0;
        for (int i = 0; i < 4; i++) {
            overcount += countOvercount();

            // Rotate the board 90 degrees
            char[][] newGrid = new char[N][N];
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    newGrid[y][x] = grid[x][N - 1 - y];
                }
            }
            grid = newGrid;
            // printGrid(newGrid);
        }

        out.println(totalCount - overcount);
    }

    long countOvercount() {
        long count = 0;
        for (int y = 0; y < N; y++) {
            for (int x1 = 0; x1 < N; x1++) {
                if (grid[y][x1] == '.') continue;
                for (int x2 = x1 + 2; x2 < N; x2 += 2) {
                    if (grid[y][x2] == '.') continue;
                    int targetY = y - (x2-x1)/2;
                    int targetX = (x1+x2)/2;
                    if (targetY >= 0 && grid[targetY][targetX] == '*') count++;
                }
            }
        }
        return count;
    }

    // Diagonals are shaped like /
    Point[][] locToDiag;
    Point[][] diagToLoc;
    int[] numCellsInDiag;
    int[][] diagPre;
    long countDiags() {
        // Fill prefix sum diagonal array
        numCellsInDiag = new int[N*2];
        diagPre = new int[N*2][N];
        locToDiag = new Point[N][N];
        diagToLoc = new Point[N*2][N];
        for (int d = 0; d < N * 2 - 1; d++) {
            int currPre = 0;
            for (int i = 0, x = Math.min(N-1, d), y = Math.max(0, d-N+1); x >= 0 && y < N; i++, x--, y++) {
                if (grid[y][x] == '*') currPre++;
                diagPre[d][i] = currPre;
                locToDiag[y][x] = new Point(d, i);
                diagToLoc[d][i] = new Point(x, y);
                numCellsInDiag[d]++;
            }
        }
        // for (int d = 0; d < N * 2 - 1; d++) System.out.println(Arrays.toString(diagPre[d]));

        // Now do the counting
        long count = 0;
        for (int d = 0; d < N * 2 - 1; d++) {
            for (int i = 0; i < numCellsInDiag[d]; i++) {
                Point loci = diagToLoc[d][i];
                if (grid[loci.b][loci.a] == '.') continue;
                for (int j = i+1; j < numCellsInDiag[d]; j++) {
                    Point locj = diagToLoc[d][j];
                    if (grid[locj.b][locj.a] == '.') continue;
                    // System.out.println(loci + " " + locj);
                    int diagDist = j - i;
                    // Check on top-left
                    Point otherloci = moveUL(loci, diagDist);
                    Point otherlocj = moveUL(locj, diagDist);
                    if (otherloci.a != -1 && otherlocj.b != -1) {
                        Point otherdiagi = locToDiag[otherloci.b][otherloci.a];
                        Point otherdiagj = locToDiag[otherlocj.b][otherlocj.a];
                        count += preSum(otherdiagi.a, otherdiagi.b, otherdiagj.b);
                    }

                    // Check on bottom-right
                }
            }
        }
        return count;
    }

    int preSum(int d, int i, int j) {
        return diagPre[d][j] - ((i == 0) ? 0 : diagPre[d][i-1]);
    }

    // Prevents from going out of bounds.
    Point moveUL(Point loc, int dist) {
        int newX = loc.a - dist;
        int newY = loc.b - dist;
        if (newY < 0) {
            newX += newY;
            newY = 0;
        } else if (newX < 0) {
            newY += newX;
            newX = 0;
        }

        if (newX < 0 || newY < 0) {
            // Still out of bounds
            return new Point(-1, -1);
        } else return new Point(newX, newY);
    }

    void printGrid(char[][] grid) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) System.out.print(grid[i][j]);
            System.out.println();
        }
    }

    class Point {
        int a, b;
        Point(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("triangles.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("triangles.out")));
        new triangles2(in, out);
        in.close();
        out.close();
    }
}
