/*
Solution: Mark any letters inside 1 password as part of the same 'set'. Then, floodfill
to determine how many their are. Only consider starting from letters that were in the
original password list.
*/

import java.util.*;
import java.io.*;

public class secretpass {
    int N;
    boolean[] letterUsed;
    boolean[][] graph;

    secretpass() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        graph = new boolean[26][26];
        letterUsed = new boolean[26];
        for (int i = 0; i < N; i++) {
            String str = in.readLine();
            HashSet<Character> usedChars = new HashSet<>();
            for (char c : str.toCharArray()) {
                letterUsed[c - 'a'] = true;
                usedChars.add(c);
            }
            // Update graph edges (all pairs of characters)
            Character[] used = usedChars.toArray(new Character[0]);
            for (int j = 1; j < used.length; j++) {
                for (int k = 0; k < j; k++) {
                    graph[used[j] - 'a'][used[k] - 'a'] = true;
                    graph[used[k] - 'a'][used[j] - 'a'] = true;
                }
            }
        }
        in.close();

        // Do floodfill
        int answer = 0;
        for (int i = 0; i < 26; i++) {
            if (letterUsed[i]) {
                answer++;
                letterUsed[i] = false;
                floodfill(i);
            }
        }

        System.out.println(answer);
    }

    void floodfill(int n) {
        for (int i = 0; i < 26; i++) {
            if (graph[n][i] && letterUsed[i]) {
                letterUsed[i] = false;
                floodfill(i);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        new secretpass();
    }
}
