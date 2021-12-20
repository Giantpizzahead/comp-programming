import java.awt.*;
import java.io.*;
import java.util.*;

@SuppressWarnings("unchecked")
public class squaresim {
    long answer = 0, currSum = 0;
    int R, C;
    int[][] skill;
    long[][] neighborSum;
    boolean[][] isOut;

    squaresim(BufferedReader in, PrintWriter out, int tn) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        R = Integer.parseInt(st.nextToken());
        C = Integer.parseInt(st.nextToken());
        skill = new int[R][C];
        isOut = new boolean[R][C];
        for (int i = 0; i < R; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < C; j++) {
                skill[i][j] = Integer.parseInt(st.nextToken());
                currSum += skill[i][j];
            }
        }

        boolean elimOccurred;
        do {
            answer += currSum;
            genNeighborSums();
            elimOccurred = false;
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (!isOut[i][j] && considerElim(j, i)) {
                        isOut[i][j] = true;
                        elimOccurred = true;
                        currSum -= skill[i][j];
                    }
                }
            }
        } while (elimOccurred);

        out.println("Case #" + tn + ": " + answer);
        out.flush();
    }

    void genNeighborSums() {
        neighborSum = new long[R][C];
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                for (int k = i-1; k >= -1; k--) {
                    if (k == -1) neighborSum[i][j] += skill[i][j];
                    else if (!isOut[k][j]) {
                        neighborSum[i][j] += skill[k][j];
                        break;
                    }
                }
                for (int k = i+1; k <= R; k++) {
                    if (k == R) neighborSum[i][j] += skill[i][j];
                    else if (!isOut[k][j]) {
                        neighborSum[i][j] += skill[k][j];
                        break;
                    }
                }
                for (int k = j-1; k >= -1; k--) {
                    if (k == -1) neighborSum[i][j] += skill[i][j];
                    else if (!isOut[i][k]) {
                        neighborSum[i][j] += skill[i][k];
                        break;
                    }
                }
                for (int k = j+1; k <= C; k++) {
                    if (k == C) neighborSum[i][j] += skill[i][j];
                    else if (!isOut[i][k]) {
                        neighborSum[i][j] += skill[i][k];
                        break;
                    }
                }
            }
        }
    }

    boolean considerElim(int x, int y) {
        return (neighborSum[y][x] + 3) / 4 > skill[y][x];
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new squaresim(in, out, i);
        in.close();
        out.close();
    }
}
