/*
ID: sunnyky1
LANG: JAVA
TASK: msquare

Solution: Really annoying BFS. There are only 8! = 40320 states, so this
will work fine.

Runtime: O(8! * some constant)

For some bit training, let's try working in bits... MWAHAHAHAHAHAHHAA
*/

import java.util.*;
import java.io.*;

public class msquare {
    int target = 0;
    final int CMASK = 0b11110000000011111111000000001111;

    msquare(BufferedReader in, PrintWriter out) throws IOException {
        // Store target configuration as a set of bits
        StringTokenizer st = new StringTokenizer(in.readLine());
        for (int i = 0; i < 8; i++) {
            target += (Integer.parseInt(st.nextToken()) - 1) << (i * 4);
        }
        doBFS();

        // Trace path
        Stack<Character> stack = new Stack<>();
        int c = target;
        From f = visited.get(c);
        while (f.state != -1) {
            stack.add(f.move);
            c = f.state;
            f = visited.get(c);
        }

        out.println(stack.size());
        int i = 0;
        while (!stack.isEmpty()) {
            if (i == 60) {
                out.println();
            }
            out.print(stack.pop());
            i++;
        }
        out.println();
    }

    HashMap<Integer, From> visited = new HashMap<>(40320);
    void doBFS() {
        int initConfig = 0;
        for (int i = 0; i < 8; i++) initConfig += i << (i * 4);

        Queue<Integer> q = new LinkedList<>();
        q.add(initConfig);
        visited.put(initConfig, new From(-1, 'N'));
        int currLeft = 1, nextLeft = 0, currCost = 0;

        int c;
        while (!q.isEmpty()) {
            c = q.poll();
            if (c == target) return;

            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                currCost++;
            }
            currLeft--;

            int[] carr = decode(c);
            // System.out.println(Arrays.toString(carr));

            // Trans A
            int[] narr = new int[8];
            for (int i = 0; i < 8; i++) narr[i] = carr[7 - i];
            int ns = hash(narr);
            if (!visited.containsKey(ns)) {
                visited.put(ns, new From(c, 'A'));
                q.add(ns);
                nextLeft++;
            }

            // Trans B
            narr[0] = carr[3];
            for (int i = 1; i < 4; i++) narr[i] = carr[i - 1];
            for (int i = 4; i < 7; i++) narr[i] = carr[i + 1];
            narr[7] = carr[4];
            ns = hash(narr);
            if (!visited.containsKey(ns)) {
                visited.put(ns, new From(c, 'B'));
                q.add(ns);
                nextLeft++;
            }

            // Trans C
            narr[0] = carr[0];
            narr[1] = carr[6];
            narr[2] = carr[1];
            narr[3] = carr[3];
            narr[4] = carr[4];
            narr[5] = carr[2];
            narr[6] = carr[5];
            narr[7] = carr[7];
            ns = hash(narr);
            if (!visited.containsKey(ns)) {
                visited.put(ns, new From(c, 'C'));
                q.add(ns);
                nextLeft++;
            }
        }
    }

    int[] decode(int s) {
        int[] sarr = new int[8];
        for (int i = 0; i < 8; i++) sarr[i] = (s >> (i * 4)) % 8;
        return sarr;
    }

    int hash(int[] sarr) {
        int s = 0;
        for (int i = 0; i < 8; i++) s += sarr[i] << (i * 4);
        return s;
    }

    public static void main(String[] args) throws IOException {
        // BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        // PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        BufferedReader in = new BufferedReader(new FileReader("msquare.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("msquare.out")));
        new msquare(in, out);
        in.close();
        out.close();
    }

    static class From {
        int state;
        char move;
        From(int state, char move) {
            this.state = state;
            this.move = move;
        }
    }
}