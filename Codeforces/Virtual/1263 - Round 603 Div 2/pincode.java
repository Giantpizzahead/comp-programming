/*
Solution: There are only 10 cards, so the answer is just the # of pairs of cards that are the same - 1.
*/

import java.util.*;
import java.io.*;

public class pincode {
    int T, N;
    String[] codes, newCodes;

    pincode() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        T = Integer.parseInt(in.readLine());
        for (int i = 0; i < T; i++) {
            N = Integer.parseInt(in.readLine());
            codes = new String[N];
            HashSet<String> isACode = new HashSet<>();
            for (int j = 0; j < N; j++) {
                codes[j] = in.readLine();
                isACode.add(codes[j]);
            }

            int numChanges = 0;
            newCodes = new String[N];
            HashSet<String> alreadyUsed = new HashSet<>();
            for (int j = 0; j < N; j++) {
                if (alreadyUsed.contains(codes[j])) {
                    // Switch last digit
                    for (int k = 0; k <= 9; k++) {
                        String newCode = codes[j].substring(0, 3) + Integer.toString(k);
                        if (isACode.contains(newCode)) continue;
                        newCodes[j] = newCode;
                        numChanges++;
                        isACode.add(newCode);
                        alreadyUsed.add(newCode);
                        break;
                    }
                } else {
                    newCodes[j] = codes[j];
                    alreadyUsed.add(codes[j]);
                }
            }

            out.println(numChanges);
            for (String nc : newCodes) out.println(nc);
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new pincode();
    }
}
