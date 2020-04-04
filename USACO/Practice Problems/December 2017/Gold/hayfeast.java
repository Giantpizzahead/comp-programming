/*
Solution: Sliding window, with a TreeMap (multiset) to track the max spiciness value.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class hayfeast {
    int N;
    long M;
    int[] flavor, spicy;

    hayfeast() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("hayfeast.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Long.parseLong(st.nextToken());
        flavor = new int[N];
        spicy = new int[N];

        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            flavor[i] = Integer.parseInt(st.nextToken());
            spicy[i] = Integer.parseInt(st.nextToken());
        }
        fin.close();

        int first = 0;
        long currSum = 0;
        int bestSpice = 1987654321;
        TreeMap<Integer, Integer> currSpicy = new TreeMap<>();
        for (int last = 0; last < N; last++) {
            currSum += flavor[last];
            currSpicy.put(spicy[last], currSpicy.getOrDefault(spicy[last], 0) + 1);
            if (currSum < M) continue;
            while (currSum - flavor[first] >= M) {
                currSum -= flavor[first];
                currSpicy.put(spicy[first], currSpicy.get(spicy[first]) - 1);
                currSpicy.remove(spicy[first], 0);
                first++;
            }

            int maxSpice = currSpicy.lastKey();
            if (maxSpice < bestSpice) bestSpice = maxSpice;
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("hayfeast.out")));
        fout.println(bestSpice);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new hayfeast();
    }
}