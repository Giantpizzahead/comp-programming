/*
Solution: Segment tree storing sum and min left sum. To query, check sum == 0 and min left
sum >= 0 (if less, then at some point )( happened).

Runtime: O((N + M) * log(N))
*/

import java.io.*;

public class BRCKTS {
    int N, M;
    String brackets;
    GSS.SegmentTree st;

    BRCKTS() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        for (int c = 1; c <= 10; c++) {
            out.printf("Test %d:\n", c);
            N = Integer.parseInt(in.readLine());
            brackets = in.readLine();
            st = new GSS.SegmentTree(N, brackets);
            M = Integer.parseInt(in.readLine());
            for (int i = 0; i < M; i++) {
                int op = Integer.parseInt(in.readLine());
                if (op == 0) {
                    out.println(st.query() ? "YES" : "NO");
                } else {
                    st.changeBracket(op - 1);
                }
            }
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new BRCKTS();
    }
}

class SegmentTree {
    int size;
    int[] s, mls;
    String brackets;

    SegmentTree(int size, String brackets) {
        this.size = size;
        this.brackets = brackets;
        s = new int[size * 4 + 1];
        mls = new int[size * 4 + 1];
        initTree(1, 0, size - 1);
    }

    void changeBracket(int i) {
        changeBracket(1, 0, size-1, i);
    }

    void changeBracket(int n, int lb, int ub, int i) {
        if (lb > i || ub < i) return;
        else if (lb == i && ub == i) {
            s[n] *= -1;
            mls[n] *= -1;
            return;
        }
        
        changeBracket(n*2, lb, (lb+ub)/2, i);
        changeBracket(n*2+1, (lb+ub)/2+1, ub, i);
        update(n);
    }

    boolean query() {
//        System.out.println(Arrays.toString(s));
//        System.out.println(Arrays.toString(mls));
        return s[1] == 0 && mls[1] >= 0;
    }

    void initTree(int n, int lb, int ub) {
        if (lb == ub) {
            s[n] = brackets.charAt(lb) == '(' ? 1 : -1;
            mls[n] = s[n];
        } else {
            initTree(n * 2, lb, (lb + ub) / 2);
            initTree(n * 2 + 1, (lb + ub) / 2 + 1, ub);
            update(n);
        }
    }

    void update(int n) {
        s[n] = s[n*2] + s[n*2+1];
        mls[n] = Math.min(mls[n*2], s[n*2] + mls[n*2+1]);
    }
}