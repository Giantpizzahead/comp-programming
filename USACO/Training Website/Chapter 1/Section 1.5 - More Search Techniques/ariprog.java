/*
ID: sunnyky1
LANG: JAVA
TASK: ariprog

Solution: For each bisquare in the set S, try starting an arithmetic progression from that
bisquare with a common difference equal to every next element in the set of bisquaresSet.

Runtime: O(S^2*N) -> A bit slow, but by stopping early (once your common difference reaches
a value too high to yield anything), this should pass.
 */

import java.io.*;
import java.util.*;

public class ariprog {
    int N, M, numBisquares, maxBisquare;
    Integer[] sortedBisquares;
    HashSet<Integer> bisquaresSet;

    ariprog() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        M = Integer.parseInt(fin.readLine());
        fin.close();

        // Generate bisquaresSet
        bisquaresSet = new HashSet<>();
        for (int p = 0; p <= M; p++) {
            for (int q = p; q <= M; q++) {
                bisquaresSet.add(p*p + q*q);
            }
        }
        sortedBisquares = bisquaresSet.toArray(new Integer[0]);
        Arrays.sort(sortedBisquares);
        numBisquares = sortedBisquares.length;
        int maxBisquare = 2 * M * M;

        // Find all arithmetic progressions by starting from each element in the set of bisquares
        // Try all common differences based on the next element in the set of bisquares
        boolean seqFound = false;
        int cd;
        ArrayList<Seq> foundSequences = new ArrayList<>();
        for (int i = 0; i < numBisquares; i++) {
            for (int j = i+1; j < numBisquares; j++) {
                cd = sortedBisquares[j] - sortedBisquares[i];
                // If the common difference is too high to be right, stop checking
                if (sortedBisquares[i] + (N-1) * cd > (maxBisquare)) break;
                // Try making a sequence
                if (validSeq(sortedBisquares[i], cd)) {
                    foundSequences.add(new Seq(sortedBisquares[i], cd));
                    seqFound = true;
                }
            }
        }

        // Sort found sequences
        foundSequences.sort((a, b) -> {
            if (a.b == b.b) return a.a - b.a;
            else return a.b - b.b;
        });

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("ariprog.out")));
        if (!seqFound) fout.println("NONE");
        else {
            for (Seq s : foundSequences) fout.println(s.a + " " + s.b);
        }
        fout.close();
    }

    boolean validSeq(int start, int cd) {
        int curr = start;
        for (int i = 0; i < N; i++) {
            if (!bisquaresSet.contains(curr)) return false;
            curr += cd;
        }
        return true;
    }

    public static void main(String[] args) throws IOException {
        new ariprog();
    }

    static class Seq {
        int a, b;
        Seq(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }
}
