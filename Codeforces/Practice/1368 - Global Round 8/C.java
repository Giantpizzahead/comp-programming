import java.util.*;
import java.io.*;

public class evenpicture {
    static PrintWriter out;
    int N, currDrawn;
    ArrayList<Pair> toPrint;

    static class Pair {
        int x, y;
        Pair(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    evenpicture(BufferedReader in) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        currDrawn = 0;
        toPrint = new ArrayList<>();

        drawSquare(2, 2, true);

        out.println(toPrint.size());
        for (Pair p : toPrint) out.printf("%d %d\n", p.x, p.y);
    }

    void drawSquare(int x, int y, boolean isFirst) {
        if (isFirst) printCell(x, y);
        printCell(x+1, y);
        printCell(x+2, y);
        printCell(x+2, y+1);
        printCell(x+2, y+2);
        printCell(x+1, y+2);
        printCell(x, y+2);
        printCell(x, y+1);
        if (currDrawn < N) {
            currDrawn++;
            printCell(x, y+3);
            printCell(x-1, y+3);
            printCell(x-1, y+2);
        }
        if (currDrawn < N) {
            currDrawn++;
            printCell(x+3, y);
            printCell(x+3, y-1);
            printCell(x+2, y-1);
        }
        if (currDrawn < N) {
            currDrawn++;
            drawSquare(x+2, y+2, false);
        }
    }

    void printCell(int x, int y) {
        toPrint.add(new Pair(x, y));
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(new BufferedOutputStream(System.out));
        new evenpicture(in);
        in.close();
        out.close();
    }
}
