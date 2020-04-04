import java.util.*;
import java.io.*;

public class shiftandreplace {
    int N, Q;
    int[] arr, arrShifts, shiftVals;
    TreeSet<Pair> ts;

    shiftandreplace(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(in.readLine());
        arr = new int[N];
        for (int i = 0; i < N; i++) arr[i] = Integer.parseInt(st.nextToken());

        // Generate starting cyclic values
        shiftVals = new int[N];
        arrShifts = new int[N];
        for (int i = 0; i < N; i++) {
            int shift = findShift(i, arr[i]);
            arrShifts[i] = shift;
            if (shift != -1) shiftVals[shift]++;
        }
        ts = new TreeSet<>(new Comparator<Pair>() {
            @Override
            public int compare(Pair o1, Pair o2) {
                if (o1.actualV == o2.actualV) return o1.i - o2.i;
                else return o1.actualV - o2.actualV;
            }
        });
        for (int i = 0; i < N; i++) ts.add(new Pair(i, shiftVals[i]));

        Q = Integer.parseInt(in.readLine());
        int x, b;
        for (int i = 0; i < Q; i++) {
            st = new StringTokenizer(in.readLine());
            x = Integer.parseInt(st.nextToken()) - 1;
            b = Integer.parseInt(st.nextToken());
            int currShift = arrShifts[x];
            int newShift = findShift(x, b);
            if (currShift != newShift) {
                // Remove previous shift value
                if (currShift != -1) {
                    ts.remove(new Pair(currShift, shiftVals[currShift]));
                    shiftVals[currShift]--;
                    ts.add(new Pair(currShift, shiftVals[currShift]));
                }
                // Adjust shift value
                arrShifts[x] = newShift;
                if (newShift != -1) {
                    // Also adjust this shift value
                    ts.remove(new Pair(newShift, shiftVals[newShift]));
                    shiftVals[newShift]++;
                    ts.add(new Pair(newShift, shiftVals[newShift]));
                }
            }

            // Answer query
            int answer = ts.first().actualV + N;
            out.println(answer);
        }
    }

    class Pair {
        int i, v, actualV;
        Pair(int i, int v) {
            this.i = i;
            this.v = v;
            this.actualV = i - v;
        }
    }

    int findShift(int i, int v) {
        if (v > N) return -1;  // No shift at all
        int shift = i+1-v;
        if (shift < 0) shift += N;
        return shift;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        new shiftandreplace(in, out);
        in.close();
        out.close();
    }
}
