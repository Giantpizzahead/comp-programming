import java.awt.*;
import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class squaredance {
    long answer, currSum;
    int R, C;
    TreeSet<Integer>[] dancersInRow, dancersInCol;
    Queue<Cell> toEliminate, nextElims;
    int[][] skill;
    long[][] neighborSum;

    squaredance(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        answer = 0;
        currSum = 0;
        nextElims = new LinkedList<>();
        skill = new int[R][C];
        for (int i = 0; i < R; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < C; j++) {
                skill[i][j] = Integer.parseInt(st.nextToken());
                currSum += skill[i][j];
            }
        }

        dancersInRow = new TreeSet[R];
        for (int i = 0; i < R; i++) {
            dancersInRow[i] = new TreeSet<>();
            for (int j = 0; j < C; j++) dancersInRow[i].add(j);
        }
        dancersInCol = new TreeSet[C];
        for (int j = 0; j < C; j++) {
            dancersInCol[j] = new TreeSet<>();
            for (int i = 0; i < R; i++) dancersInCol[j].add(i);
        }

        neighborSum = new long[R][C];
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (i != 0) neighborSum[i][j] += skill[i-1][j];
                else neighborSum[i][j] += skill[i][j];
                if (i != R-1) neighborSum[i][j] += skill[i+1][j];
                else neighborSum[i][j] += skill[i][j];
                if (j != 0) neighborSum[i][j] += skill[i][j-1];
                else neighborSum[i][j] += skill[i][j];
                if (j != C-1) neighborSum[i][j] += skill[i][j+1];
                else neighborSum[i][j] += skill[i][j];
                considerElim(j, i);
            }
        }
        // for (int i = 0; i < R; i++) System.out.println(Arrays.toString(neighborSum[i]));

        // Simulate the rounds in a smart way
        Stack<Update> changes = new Stack<>();
        int round = 0;
        while (true) {
            round++;
            // System.out.println("Round " + round);
            toEliminate = nextElims;
            nextElims = new LinkedList<>();
            answer += currSum;
            if (toEliminate.isEmpty()) break;  // No more elims will happen
            else while (!toEliminate.isEmpty()) {
                Cell c = toEliminate.poll();
                if (c.sum != neighborSum[c.y][c.x] || neighborSum[c.y][c.x] == -1) continue; // No longer up to date

                // Eliminate this dancer / update neighborSum for it's neighbors
                Integer left = dancersInRow[c.y].lower(c.x);
                Integer right = dancersInRow[c.y].higher(c.x);
                if (left != null) {
                    // Update val for left dancer
                    int newVal = (right == null) ? skill[c.y][left] : skill[c.y][right];
                    changes.add(new Update(left, c.y, newVal - skill[c.y][c.x]));
                }
                if (right != null) {
                    // Update val for right dancer
                    int newVal = (left == null) ? skill[c.y][right] : skill[c.y][left];
                    changes.add(new Update(right, c.y, newVal - skill[c.y][c.x]));
                }

                Integer top = dancersInCol[c.x].lower(c.y);
                Integer bot = dancersInCol[c.x].higher(c.y);
                if (top != null) {
                    // Update val for top dancer
                    int newVal = (bot == null) ? skill[top][c.x] : skill[bot][c.x];
                    changes.add(new Update(c.x, top, newVal - skill[c.y][c.x]));
                }
                if (bot != null) {
                    // Update val for bot dancer
                    int newVal = (top == null) ? skill[bot][c.x] : skill[top][c.x];
                    changes.add(new Update(c.x, bot, newVal - skill[c.y][c.x]));
                }

                // Remove this dancer
                // System.out.println("Elimed " + c.x + " " + c.y);
                dancersInRow[c.y].remove(c.x);
                dancersInCol[c.x].remove(c.y);
                neighborSum[c.y][c.x] = -1;
                currSum -= skill[c.y][c.x];
            }

            // Implement changes
            while (!changes.isEmpty()) {
                Update u = changes.pop();
                if (neighborSum[u.y][u.x] != -1) {
                    neighborSum[u.y][u.x] += u.change;
                    considerElim(u.x, u.y);
                }
            }
        }
        out.println("Case #" + tn + ": " + answer);
        out.flush();
    }

    void considerElim(int x, int y) {
        if ((neighborSum[y][x] + 3) / 4 > skill[y][x]) {
            nextElims.add(new Cell(x, y, neighborSum[y][x]));
        }
    }

    class Cell {
        int x, y;
        long sum;
        Cell(int x, int y, long sum) {
            this.x = x;
            this.y = y;
            this.sum = sum;
        }
    }

    class Update {
        int x, y, change;
        Update(int x, int y, int change) {
            this.x = x;
            this.y = y;
            this.change = change;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new squaredance(in, out, i);
        in.close();
        out.close();
    }
}
