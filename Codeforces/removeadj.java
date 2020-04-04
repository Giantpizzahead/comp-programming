/*
Solution: Use a greedy approach to decide which letters to remove.
Runtime: O(26 * N^2)
*/

import java.util.*;
import java.io.*;

public class removeadj {
    int N;
    ArrayList<Integer> str;

    removeadj(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        str = new ArrayList<>(N);
        String s = in.readLine();
        for (int i = 0; i < N; i++) {
            str.add(s.charAt(i) - 'a');
        }

        // Remove the highest letters first
        int numRemoved = 0;
        boolean removed;
        for (int i = 25; i > 0; i--) {
            removed = true;
            while (removed) {
                removed = false;
                int prev = -999;
                for (int j = 0; j < str.size(); j++) {
                    if (prev == str.get(j) - 1 && str.get(j) == i) {
                        // Current letter can be removed
                        str.remove(j);
                        numRemoved++;
                        removed = true;
                        break;
                    } else if (prev == str.get(j) + 1 && prev == i) {
                        // Previous letter can be removed
                        str.remove(j-1);
                        numRemoved++;
                        removed = true;
                        break;
                    }
                    prev = str.get(j);
                }
                // System.out.println(str);
            }
        }
        // System.out.println(str);
        out.println(numRemoved);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        new removeadj(in, out);
        in.close();
        out.close();
    }
}
