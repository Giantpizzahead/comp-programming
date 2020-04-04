/*
ID: sunnyky1
LANG: JAVA
TASK: ariprog
 */

import java.util.*;
import java.io.*;

public class ariprogold {
    int N, M;
    ArrayList<Integer> sortedBisquares;
    HashSet<Integer> bisquares;

    ariprogold() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        M = Integer.parseInt(fin.readLine());
        fin.close();

        // Generate bisquares
        bisquares = new HashSet<>();
        for (int p = 0; p <= M; p++) {
            for (int q = p; q <= M; q++) {
                bisquares.add(p*p + q*q);
            }
        }
        sortedBisquares = new ArrayList<Integer>(bisquares);
        Collections.sort(sortedBisquares);
        // System.out.println(bisquares.size());
        // System.out.println(2*M*M/(N-1));

        // Find all arithmetic progressions
        // Find the sequences by filtering using common difference
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("ariprog.out")));
        boolean seqFound = false;
        for (int cd = 1; cd <= 2*M*M / (N-1); cd++) {
            for (int bisquare : sortedBisquares) {
                // Try making a sequence
                if (validSeq(bisquare, cd)) {
                    fout.println(bisquare + " " + cd);
                    seqFound = true;
                }
            }
        }
        if (!seqFound) fout.println("NONE");
        fout.close();
    }

    boolean validSeq(int start, int cd) {
        int curr = start;
        for (int i = 0; i < N; i++) {
            if (!bisquares.contains(curr)) return false;
            curr += cd;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        new ariprogold();
    }
}
