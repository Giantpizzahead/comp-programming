/*
Solution: Find the maximum amount that an element needs to move backward.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class sort {
    int N;
    HashMap<Integer, Queue<Integer>> elementLocs;
    int[] unsorted, sorted;

    sort() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        N = Integer.parseInt(fin.readLine());
        unsorted = new int[N];
        sorted = new int[N];
        elementLocs = new HashMap<>();
        for (int i = 0; i < N; i++) {
            unsorted[i] = Integer.parseInt(fin.readLine());
            if (!elementLocs.containsKey(unsorted[i])) {
                elementLocs.put(unsorted[i], new LinkedList<>());
            }
            elementLocs.get(unsorted[i]).add(i);
            sorted[i] = unsorted[i];
        }
        fin.close();

        Arrays.sort(sorted);
        int answer = 0;
        for (int i = 0; i < N; i++) {
            int unsortedI = elementLocs.get(sorted[i]).poll();
            answer = Math.max(unsortedI - i, answer);
        }

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        fout.println(answer + 1);
        fout.close();
    }

    public static void main(String[] args) throws IOException {
        new sort();
    }
}
