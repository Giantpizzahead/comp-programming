/*
ID: sunnyky1
LANG: JAVA
TASK: combo

Solution: Generate all possible combos that unlock with Farmer John's combo. Then, generate
all possible combos that unlock with the master combo. Put these both into a HashSet to avoid
duplicates. Find the size of that HashSet to get your answer. This works since the # of valid
combos is at most 250 (5*5*5*2).
 */

import java.util.*;
import java.io.*;

public class combo {
    int N;
    int[] combo1, combo2;
    HashSet<Integer> workingCombos;

    combo() throws IOException {
        // Input
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        StringTokenizer st = new StringTokenizer(fin.readLine());
        combo1 = new int[3];
        for (int i = 0; i < 3; i++) combo1[i] = Integer.parseInt(st.nextToken());
        st = new StringTokenizer(fin.readLine());
        combo2 = new int[3];
        for (int i = 0; i < 3; i++) combo2[i] = Integer.parseInt(st.nextToken());
        fin.close();

        // Generate possible combos for each
        workingCombos = new HashSet<>();
        genCombos(combo1);
        genCombos(combo2);

        int answer = workingCombos.size();
        PrintWriter fout = new PrintWriter("combo.out");
        fout.println(answer);
        fout.close();
    }

    void genCombos(int[] correct) {
        int fixedA, fixedB, fixedC;
        for (int a = correct[0] - 2; a <= correct[0] + 2; a++) {
            fixedA = fix(a);
            for (int b = correct[1] - 2; b <= correct[1] + 2; b++) {
                fixedB = fix(b);
                for (int c = correct[2] - 2; c <= correct[2] + 2; c++) {
                    fixedC = fix(c);
                    /*
                    System.out.println(a + " " + b + " " + c);
                    System.out.println("Combo: " + fixedA + " " + fixedB + " " + fixedC);
                     */
                    addCombo(fixedA, fixedB, fixedC);
                }
            }
        }
    }

    int fix(int n) {
        if (n < 1) return (n + N - 1) % N + 1;
        else return (n - 1) % N + 1;
    }

    void addCombo(int a, int b, int c) {
        workingCombos.add(a + b * (N + 1) + c * (N + 1) * (N + 1));
    }

    public static void main(String[] args) throws IOException {
        new combo();
    }
}
