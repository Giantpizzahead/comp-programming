/*
Solution: Simple ad-hoc problem.
Runtime: O(NT)
*/

import java.util.*;
import java.io.*;

public class poi {
    int N, T, P;
    int[][] whichSolved;
    int[] contScore, contNumSolved;
    int[] taskScore;

    poi(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        T = Integer.parseInt(st.nextToken());
        P = Integer.parseInt(st.nextToken());
        taskScore = new int[T];
        whichSolved = new int[N][T];
        contScore = new int[N];
        contNumSolved = new int[N];
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            for (int j = 0; j < T; j++) {
                int a = Integer.parseInt(st.nextToken());
                whichSolved[i][j] = a;
                if (a == 0) taskScore[j]++;
                else contNumSolved[i]++;
            }
        }

        // Calculate scores
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < T; j++) {
                if (whichSolved[i][j] == 1) contScore[i] += taskScore[j];
            }
        }

        // Sort contestants by their scores
        Contestant[] conts = new Contestant[N];
        for (int i = 0; i < N; i++) conts[i] = new Contestant(contScore[i], contNumSolved[i], i);
        Arrays.sort(conts, new Comparator<Contestant>() {
            @Override
            public int compare(Contestant o1, Contestant o2) {
                if (o1.s != o2.s) return o2.s - o1.s;
                else if (o1.t != o2.t) return o2.t - o1.t;
                else return o1.id - o2.id;
            }
        });

        // Find Philip's location
        for (int i = 0; i < N; i++) {
            if (conts[i].id + 1 == P) {
                out.printf("%d %d\n", conts[i].s, i+1);
                break;
            }
        }
    }

    class Contestant {
        int s, t, id;
        Contestant(int ss, int tt, int i) {
            s = ss;
            t = tt;
            id = i;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("poi.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("poi.out")));
        new poi(in, out);
        in.close();
        out.close();
    }
}
