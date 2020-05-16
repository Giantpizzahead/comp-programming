import java.util.*;
import java.io.*;

public class patternmatching {
    int N;
    ArrayList<Character> currPre, currSuf;
    ArrayList<String> inBetween;

    patternmatching(BufferedReader in, PrintWriter out, int tn) throws IOException {
        System.out.print("Case #" + tn + ": ");

        N = Integer.parseInt(in.readLine());
        currPre = new ArrayList<>();
        currSuf = new ArrayList<>();
        inBetween = new ArrayList<>();
        String str, pre, suf;
        boolean impossible = false;
        outerLoop:
        for (int i = 0; i < N; i++) {
            str = in.readLine();
            if (impossible) continue;  // Exhaust input
            String[] split = str.split("\\*");
            if (str.charAt(str.length() - 1) == '*') {
                // Handle special case (empty required suffix)
                String[] newSplit = new String[split.length + 1];
                for (int j = 0; j < split.length; j++) newSplit[j] = split[j];
                newSplit[split.length] = "";
                split = newSplit;
            }
            pre = split[0];
            suf = split[split.length - 1];
            // System.out.println(Arrays.toString(split));
            // Find prefix
            int l, r, j = 0;
            for (l = 0; l < pre.length(); l++) {
                if (currPre.size() > l) {
                    if (currPre.get(l) != pre.charAt(l)) {
                        // Impossible
                        System.out.println("*");
                        impossible = true;
                        continue outerLoop;
                    }
                } else {
                    // Add new character to prefix
                    currPre.add(pre.charAt(l));
                }
            }
            // Find suffix
            for (r = suf.length() - 1; r >= 0; r--, j++) {
                if (currSuf.size() > j) {
                    if (currSuf.get(j) != suf.charAt(r)) {
                        // Impossible
                        System.out.println("*");
                        impossible = true;
                        continue outerLoop;
                    }
                } else {
                    // Add new character to suffix
                    currSuf.add(suf.charAt(r));
                }
            }
            // Find strings in between
            for (j = 1; j < split.length - 1; j++) inBetween.add(split[j]);
        }
        if (impossible) return;

        // Generate working string
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < currPre.size(); i++) sb.append(currPre.get(i));
        for (String s : inBetween) sb.append(s);
        for (int i = currSuf.size() - 1; i >= 0; i--) sb.append(currSuf.get(i));
        String output = sb.toString();
        System.out.println((output.equals("")) ? "A" : output);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        int T = Integer.parseInt(in.readLine());
        for (int i = 1; i <= T; i++) new patternmatching(in, out, i);
        in.close();
        out.close();
    }
}
