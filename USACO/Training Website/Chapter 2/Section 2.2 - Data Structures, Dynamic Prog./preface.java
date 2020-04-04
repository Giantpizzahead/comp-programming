/*
ID: sunnyky1
LANG: JAVA
TASK: preface

Solution: Do dynamic programming on the # of each letter needed to print
the ith page. Transition based on the maximum allowed character sequence
for the new page.
*/

import java.util.*;
import java.io.*;

public class preface {
    int N;
    Letters[] dp;
    TreeMap<Integer, Letters> allowedPairs = new TreeMap<Integer, Letters>();

    preface() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("preface.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        fin.close();

        allowedPairs.put(1, new Letters("I"));
        allowedPairs.put(5, new Letters("V"));
        allowedPairs.put(10, new Letters("X"));
        allowedPairs.put(50, new Letters("L"));
        allowedPairs.put(100, new Letters("C"));
        allowedPairs.put(500, new Letters("D"));
        allowedPairs.put(1000, new Letters("M"));
        allowedPairs.put(4, new Letters("IV"));
        allowedPairs.put(9, new Letters("IX"));
        allowedPairs.put(40, new Letters("XL"));
        allowedPairs.put(90, new Letters("XC"));
        allowedPairs.put(400, new Letters("CD"));
        allowedPairs.put(900, new Letters("CM"));

        dp = new Letters[N + 1];
        dp[0] = new Letters();
        for (int i = 1; i <= N; i++) {
            Map.Entry<Integer, Letters> toUse = allowedPairs.floorEntry(i);
            dp[i] = dp[i-toUse.getKey()].combine(toUse.getValue());
        }

        // Sum letters
        Letters lettersUsed = new Letters();
        for (int i = 1; i <= N; i++) {
            lettersUsed = lettersUsed.combine(dp[i]);
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("preface.out")));
        char[] letters = new char[] {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
        for (int i = 0; i < 7; i++) {
            if (lettersUsed.v[i] == 0) break;
            fout.println(letters[i] + " " + lettersUsed.v[i]);
        }
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new preface();
    }
}

class Letters {
    // i, v, x, l, c, d, m
    int[] v;
    static HashMap<Character, Integer> charToI;

    Letters() {
        v = new int[7];
    }

    Letters(String s) {
        if (charToI == null) {
            charToI = new HashMap<>();
            charToI.put('I', 0);
            charToI.put('V', 1);
            charToI.put('X', 2);
            charToI.put('L', 3);
            charToI.put('C', 4);
            charToI.put('D', 5);
            charToI.put('M', 6);
        }
        v = new int[7];
        for (char ch : s.toCharArray()) {
            v[charToI.get(ch)]++;
        }
    }

    Letters combine(Letters other) {
        Letters newLetters = new Letters();
        for (int i = 0; i < 7; i++) {
            newLetters.v[i] = v[i] + other.v[i];
        }
        return newLetters;
    }
}