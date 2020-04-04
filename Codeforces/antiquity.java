/*
Solution: Use a 2D BIT, hashing the rectangles with 'random' values.
*/

import java.util.*;
import java.io.*;

public class antiquity {
    int N, M, Q;

    antiquity() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        Q = Integer.parseInt(st.nextToken());
        BIT2D field = new BIT2D(N, M);
        int t, x1, y1, x2, y2;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            t = Integer.parseInt(st.nextToken());
            y1 = Integer.parseInt(st.nextToken());
            x1 = Integer.parseInt(st.nextToken());
            y2 = Integer.parseInt(st.nextToken());
            x2 = Integer.parseInt(st.nextToken());
            if (t == 1) {
                // Add barrier
                field.addToArea(x1, y1, x2, y2, hash(x1, y1, x2, y2));
            } else if (t == 2) {
                // Remove barrier
                field.addToArea(x1, y1, x2, y2, -hash(x1, y1, x2, y2));
            } else {
                // Query
                if (field.query(x1, y1) == field.query(x2, y2)) out.println("Yes");
                else out.println("No");
            }
        }
        in.close();
        out.close();
    }

    int hash(int x1, int y1, int x2, int y2) {
        return x1 * 1234177 + y1 * 785293 + x2 * 563919 + y2 * 279141;
    }

    public static void main(String[] args) throws IOException {
        new antiquity();
    }
}

class BIT2D {
    int rows, cols;
    BIT[] v;
    BIT2D(int rows, int cols) {
        this.rows = rows;
        this.cols = cols;
        v = new BIT[rows + 1];
        for (int i = 1; i <= rows; i++) v[i] = new BIT(cols);
    }

    void addToArea(int x1, int y1, int x2, int y2, int val) {
        add(y1, x1, x2, val);
        add(y2 + 1, x1, x2, -val);
    }

    void add(int y, int x1, int x2, int val) {
        while (y <= rows) {
            v[y].addRange(x1, x2, val);
            y += Integer.lowestOneBit(y);
        }
    }

    int query(int x, int y) {
        int result = 0;
        while (y != 0) {
            result += v[y].query(x);
            y -= Integer.lowestOneBit(y);
        }
        return result;
    }
}

class BIT {
    int size;
    int[] v;
    BIT(int size) {
        this.size = size;
        v = new int[size + 1];
    }

    void addRange(int lb, int ub, int val) {
        add(lb, val);
        add(ub + 1, -val);
    }

    void add(int i, int val) {
        while (i <= size) {
            v[i] += val;
            i += Integer.lowestOneBit(i);
        }
    }

    int query(int i) {
        int result = 0;
        while (i != 0) {
            result += v[i];
            i -= Integer.lowestOneBit(i);
        }
        return result;
    }
}