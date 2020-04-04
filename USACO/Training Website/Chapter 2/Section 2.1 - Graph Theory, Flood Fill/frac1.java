/*
ID: sunnyky1
LANG: JAVA
TASK: frac1

Solution: Generate all the possible fractions, and sort them using their
double values. Output these fractions in order.

Runtime: O(N^2 * log(N))
*/

import java.util.*;
import java.io.*;

public class frac1 {
    int N;
    TreeSet<Fraction> fractions;

    frac1() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        fin.close();

        // Generate all fractions
        fractions = new TreeSet<>();
        for (int d = 1; d <= N; d++) {
            for (int n = 0; n <= d; n++) {
                fractions.add(new Fraction(n, d));
            }
        }

        // Print all fractions
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("frac1.out")));
        for (Fraction f : fractions) fout.println(f);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new frac1();
    }
}

class Fraction implements Comparable<Fraction> {
    int n, d;
    double value;
    Fraction(int n, int d) {
        this.n = n;
        this.d = d;
        value = (double) n / d;
    }

    @Override
    public int compareTo(Fraction o) {
        if (value == o.value) return 0;
        else return (value < o.value) ? -1 : 1;
    }

    @Override
    public String toString() {
        return n + "/" + d;
    }
}