/*
Solution: Go in a snake-like pattern.
Runtime: O(NM)
*/

import java.util.*;
import java.io.*;

public class tolik {
    int N, M;
    Point snakeTop, snakeBot;

    tolik(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        snakeTop = new Point(0, 0, 1);
        snakeBot = new Point(M-1, N-1, -1);
        int numVisited = 0;
        boolean topTurn = true;
        while (numVisited != N * M) {
            if (topTurn) {
                out.println(snakeTop);
                numVisited++;
                // Move top
                snakeTop.x += snakeTop.d;
                if (snakeTop.x < 0 || snakeTop.x == M) {
                    // Reverse
                    snakeTop.x -= snakeTop.d;
                    snakeTop.y++;
                    snakeTop.d *= -1;
                }
            } else {
                out.println(snakeBot);
                numVisited++;
                // Move bot
                snakeBot.x += snakeBot.d;
                if (snakeBot.x < 0 || snakeBot.x == M) {
                    // Reverse
                    snakeBot.x -= snakeBot.d;
                    snakeBot.y--;
                    snakeBot.d *= -1;
                }
            }
            topTurn = !topTurn;
        }
    }

    class Point {
        int x, y, d;
        Point(int xx, int yy, int dd) {
            x = xx;
            y = yy;
            d = dd;
        }

        @Override
        public String toString() {
            return (y+1) + " " + (x+1);
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new tolik(in, out);
        in.close();
        out.close();
    }
}
