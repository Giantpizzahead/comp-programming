/*
Solution: The # of instructions in each direction must be the same, so remove
instructions until each instruction has the same amount (min of all 4 counts).
One way to arrange these instructions is a simple rectangular cycle (this will
always work). So, just print that.

Runtime: O(10^5)
*/

import java.util.*;
import java.io.*;

public class snowrobot {
    int Q;
    HashMap<Character, Integer> charToInt = new HashMap<>(4, 1);
    char[] chars = new char[] {'U', 'R', 'D', 'L'};

    snowrobot() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        StringTokenizer st = new StringTokenizer(in.readLine());
        Q = Integer.parseInt(st.nextToken());
        charToInt.put('U', 0);
        charToInt.put('R', 1);
        charToInt.put('D', 2);
        charToInt.put('L', 3);
        for (int i = 0; i < Q; i++) {
            char[] str = in.readLine().toCharArray();
            int[] count = new int[4];
            for (char c : str) {
                count[charToInt.get(c)]++;
            }

            // Find minimum count
            int numHor = Math.min(count[1], count[3]);
            int numVert = Math.min(count[0], count[2]);
            // Special cases
            if (numHor > 1 && numVert == 0) {
                numHor = 1;
            } else if (numVert > 1 && numHor == 0) {
                numVert = 1;
            }
            count[1] = numHor;
            count[3] = numHor;
            count[0] = numVert;
            count[2] = numVert;


            // Print info
            out.println(numHor * 2 + numVert * 2);
            StringBuilder sb = new StringBuilder();
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < count[j]; k++) sb.append(chars[j]);
            }
            out.println(sb.toString());
        }
        in.close();
        out.close();
    }

    public static void main(String[] args) throws IOException {
        new snowrobot();
    }
}