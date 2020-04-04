/*
ID: sunnyky1
LANG: JAVA
TASK: contact

Solution: The limits are small enough to just generate each length pattern,
and store it in a HashMap. This can be done using a cyclic array. I actually
already implemented this at some point, so this is that implementation.

Runtime: O(~72N)
 */

import java.util.*;
import java.io.*;

public class contact {
    int A, B, N;
    HashMap<String, Integer> patterns;

    contact() throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("contact.in"));
        StringTokenizer st = new StringTokenizer(in.readLine());
        A = Integer.parseInt(st.nextToken());
        B = Integer.parseInt(st.nextToken());
        N = Integer.parseInt(st.nextToken());
        patterns = new HashMap<>(2048);
        int currLoc = 0, lengthSoFar = 0;
        char[] lastBits = new char[B];
        while (true) {
            String line = in.readLine();
            if (line == null) break;

            // Track all bits as they come in
            for (char c : line.toCharArray()) {
                lastBits[currLoc] = c;
                lengthSoFar++;
                // Generate all the previous bit patterns
                String str = "";
                for (int i = 0, modI = currLoc; i < Math.min(lengthSoFar, B); i++, modI--) {
                    if (modI < 0) modI += B;
                    str += lastBits[modI];
                    if (!patterns.containsKey(str)) {
                        patterns.put(str, 0);
                    }
                    patterns.put(str, patterns.get(str) + 1);
                }

                currLoc = (currLoc + 1) % B;
            }

            // System.out.println(patterns);
        }
        in.close();

        // Format the output
        ArrayList<Pattern> sortedPats = new ArrayList<>();
        for (Map.Entry<String, Integer> e : patterns.entrySet()) {
            if (e.getKey().length() >= A) sortedPats.add(new Pattern(e.getKey(), e.getValue()));
        }
        Collections.sort(sortedPats, new Comparator<Pattern>() {
            @Override
            public int compare(Pattern a, Pattern b) {
                if (a.count != b.count) return b.count - a.count;
                else if (a.bits.length() != b.bits.length()) return a.bits.length() - b.bits.length();
                long result = Long.parseLong(a.bits) - Long.parseLong(b.bits);
                if (result == 0) return 0;
                else return (result > 0) ? 1 : -1;
            }
        });

        // System.out.println(sortedPats);

        // Print the output
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("contact.out")));
        int currFreq = 0, currI = 0;
        for (int i = 0; i < N; i++) {
            if (currI == sortedPats.size()) break;
            currFreq = sortedPats.get(currI).count;
            fout.println(currFreq);
            StringBuilder sb = new StringBuilder();
            int numAdded = 0;
            while (currI < sortedPats.size() && sortedPats.get(currI).count == currFreq) {
                if (numAdded++ == 6) {
                    sb.append('\n');
                    numAdded = 1;
                }
                sb.append(sortedPats.get(currI++).bits);
                if (numAdded != 6) sb.append(' ');
            }
            if (sb.charAt(sb.length() - 1) == ' ') fout.println(sb.substring(0, sb.length() - 1));
            else fout.println(sb.toString());
        }
        fout.close();
    }

    String reverse(String str) {
        return new StringBuilder(str).reverse().toString();
    }

    public static void main(String[] args) throws IOException {
        new contact();
    }

    class Pattern {
        String bits;
        int count;
        Pattern(String bits, int count) {
            this.bits = reverse(bits);
            this.count = count;
        }
        @Override
        public String toString() {
            return "(" + bits + ", " + count + ")";
        }
    }
}