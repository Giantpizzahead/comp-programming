/*
Implementation of a 2D BIT.
(Theoretical) runtime: O(N^2 + Q * log(N)^2), Q = # of queries
Since the # of queries isn't given, I can only hope that this is quick enough (especially since it's in Java).
*/

import java.util.*;
import java.io.*;

public class MATSUM {
    int T, N;
    BIT2D bit2d = new BIT2D(1024);

    MATSUM() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            testCase(in, out);
            if (i != T - 1) out.println();
            out.flush();
        }
        in.close();
        out.close();
    }

    void testCase(BufferedReader in, PrintWriter out) throws IOException {
        N = Integer.parseInt(in.readLine());
        commandLoop:
        while (true) {
            StringTokenizer st = new StringTokenizer(in.readLine());
            switch (st.nextToken()) {
                case "SET":
                    int x = Integer.parseInt(st.nextToken());
                    int y = Integer.parseInt(st.nextToken());
                    int n = Integer.parseInt(st.nextToken());
                    bit2d.set(x, y, n);
                    break;
                case "SUM":
                    int x1 = Integer.parseInt(st.nextToken());
                    int y1 = Integer.parseInt(st.nextToken());
                    int x2 = Integer.parseInt(st.nextToken());
                    int y2 = Integer.parseInt(st.nextToken());
                    out.println(bit2d.sum(x1, y1, x2, y2));
                    break;
                default:
                    break commandLoop;
            }
        }
        bit2d.clear();
    }

    public static void main(String[] args) throws IOException {
        new MATSUM();
    }
}

// Outside BIT will store y values, inside BITs store x values
class BIT2D {
    int size;
    BIT[] v;

    BIT2D(int size) {
        this.size = size;
        v = new BIT[size + 1];
        for (int i = 1; i <= size; i++) v[i] = new BIT(size);
    }

    void set(int x, int y, int n) {
        x++;
        y++;
        while (y <= size) {
            v[y].add(x, n);
            y += Integer.lowestOneBit(y);
        }
    }

    int sum(int x1, int y1, int x2, int y2) {
        x1++;
        y1++;
        x2++;
        y2++;
        return sumFromStart(y2, x1, x2) - ((y1 == 1) ? 0 : sumFromStart(y1 - 1, x1, x2));
    }

    int sumFromStart(int end, int x1, int x2) {
        int result = 0;
        while (end != 0) {
            result += v[end].query(x1, x2);
            end -= Integer.lowestOneBit(end);
        }
        return result;
    }

    void clear() {
        for (int i = 1; i <= size; i++) Arrays.fill(v[i].v, 0);
    }
}

class BIT {
    int size;
    int[] v;

    BIT(int size) {
        this.size = size;
        v = new int[size + 1];
    }

    void set(int index, int val) {
        int prevVal = query(index, index);
        int delta = val - prevVal;
        add(index, delta);
    }

    void add(int index, int val) {
        while (index <= size) {
            v[index] += val;
            index += Integer.lowestOneBit(index);
        }
    }

    int query(int start, int end) {
        return queryFromStart(end) - ((start == 1) ? 0 : queryFromStart(start - 1));
    }

    int queryFromStart(int end) {
        int result = 0;
        while (end != 0) {
            result += v[end];
            end -= Integer.lowestOneBit(end);
        }
        return result;
    }
}