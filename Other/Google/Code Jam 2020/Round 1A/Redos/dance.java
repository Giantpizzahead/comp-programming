import java.util.*;
import java.io.*;

public class dance {
    long currSum, answer;
    int R, C;
    Queue<Point> toCheck, toElim;
    int[][] skill, up, right, down, left;

    dance(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        currSum = 0;
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        skill = new int[R][C];
        up = new int[R][C];
        right = new int[R][C];
        down = new int[R][C];
        left = new int[R][C];
        toCheck = new LinkedList<>();
        toElim = new LinkedList<>();
        for (int i = 0; i < R; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < C; j++) {
                toCheck.add(new Point(i, j));
                skill[i][j] = Integer.parseInt(st.nextToken());
                currSum += skill[i][j];
                if (i == 0) up[i][j] = -1;
                else up[i][j] = i-1;
                if (i == R - 1) down[i][j] = -1;
                else down[i][j] = i+1;
                if (j == 0) left[i][j] = -1;
                else left[i][j] = j-1;
                if (j == C - 1) right[i][j] = -1;
                else right[i][j] = j+1;
            }
        }

        int currTurn = 0;
        int i, j;
        Point p;
        do {
            if (currTurn != 0) answer += currSum;
            currTurn++;

            // Eliminate people
            while (!toElim.isEmpty()) {
                p = toElim.poll();
                i = p.i;
                j = p.j;
                if (skill[i][j] == -1) continue;  // Already elimed

                // Mark as elimed / update sum
                currSum -= skill[i][j];
                skill[i][j] = -1;

                // Remove from linked list / add to required checks
                if (up[i][j] != -1) {
                    toCheck.add(new Point(up[i][j], j));
                    down[up[i][j]][j] = down[i][j];
                }
                if (down[i][j] != -1) {
                    toCheck.add(new Point(down[i][j], j));
                    up[down[i][j]][j] = up[i][j];
                }
                if (left[i][j] != -1) {
                    toCheck.add(new Point(i, left[i][j]));
                    right[i][left[i][j]] = right[i][j];
                }
                if (right[i][j] != -1) {
                    toCheck.add(new Point(i, right[i][j]));
                    left[i][right[i][j]] = left[i][j];
                }
            }

            // Check for new eliminations
            while (!toCheck.isEmpty()) {
                p = toCheck.poll();
                i = p.i;
                j = p.j;
                if (skill[i][j] == -1) continue;  // Already elimed

                long adjSkill = 0, soloSkill = 0;
                if (up[i][j] != -1) {
                    adjSkill += skill[up[i][j]][j];
                    soloSkill += skill[i][j];
                }
                if (down[i][j] != -1) {
                    adjSkill += skill[down[i][j]][j];
                    soloSkill += skill[i][j];
                }
                if (left[i][j] != -1) {
                    adjSkill += skill[i][left[i][j]];
                    soloSkill += skill[i][j];
                }
                if (right[i][j] != -1) {
                    adjSkill += skill[i][right[i][j]];
                    soloSkill += skill[i][j];
                }

                if (soloSkill != 0 && adjSkill > soloSkill) {
                    // This competitor is eliminated
                    toElim.add(p);
                }
            }
        } while (!toElim.isEmpty());

        // Off-by-one
        answer += currSum;

        out.println("Case #" + tn + ": " + answer);
    }

    static class Point {
        int i, j;
        Point(int i, int j) {
            this.i = i;
            this.j = j;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new dance(in, out, i);
        in.close();
        out.close();
    }
}