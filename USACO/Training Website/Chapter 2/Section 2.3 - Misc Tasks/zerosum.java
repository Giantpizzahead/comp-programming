/*
ID: sunnyky1
LANG: JAVA
TASK: zerosum

Solution: Generate all possible things and try them.
Runtime: O(3^N * N)
*/

import java.util.*;
import java.io.*;

public class zerosum {
    int N;
    ArrayList<String> valid;

    enum Ops {
        NONE, ADD, MINUS;
    }

    zerosum() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("zerosum.in"));
        N = Integer.parseInt(fin.readLine());
        fin.close();

        // Order: None, +, -
        valid = new ArrayList<>();
        gen(0, new Ops[N-1]);

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("zerosum.out")));
        valid.forEach(fout::println);
        fout.close();
    }

    void gen(int i, Ops[] ops) {
        if (i == N - 1) {
            test(ops);
            return;
        }
        for (Ops op : Ops.values()) {
            ops[i] = op;
            gen(i + 1, ops);
        }
    }

    void test(Ops[] ops) {
        ArrayList<Integer> tokens = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        sb.append(1);
        for (int i = 0; i < N - 1; i++) {
            if (ops[i] == Ops.ADD) {
                tokens.add(Integer.parseInt(sb.toString()));
                tokens.add(-1);
                sb = new StringBuilder();
            } else if (ops[i] == Ops.MINUS) {
                tokens.add(Integer.parseInt(sb.toString()));
                tokens.add(-2);
                sb = new StringBuilder();
            }
            sb.append(i+2);
        }
        tokens.add(Integer.parseInt(sb.toString()));

        // Try doing the operations
        int total = 0;
        Ops lastOp = Ops.ADD;
        for (int token : tokens) {
            if (token == -1) lastOp = Ops.ADD;
            else if (token == -2) lastOp = Ops.MINUS;
            else if (lastOp == Ops.ADD) {
                total += token;
            } else {
                total -= token;
            }
        }

        if (total == 0) {
            // Add to valid
            sb = new StringBuilder();
            sb.append(1);
            for (int i = 0; i < N - 1; i++) {
                sb.append((ops[i] == Ops.NONE) ? ' ' : (ops[i] == Ops.ADD) ? '+' : '-');
                sb.append(i+2);
            }
            valid.add(sb.toString());
        }
    }

    public static void main(String[] args) throws IOException {
        new zerosum();
    }
}