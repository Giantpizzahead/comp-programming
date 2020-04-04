/*
Implementation of a suffix array.

Runtime: O(N * log(N)^2)
*/

import java.util.*;
import java.io.*;

public class suffixarr {
    String str, sub;

    suffixarr(BufferedReader in, PrintWriter out) throws IOException {
        str = in.readLine();
        sub = in.readLine();
        // long startTime = System.currentTimeMillis();
        SuffixArray suffixArr = new SuffixArray(str);
        // System.out.println("String length: " + str.length());
        // System.out.printf("Time taken: %.3f sec", (System.currentTimeMillis() - startTime) / 1000f);
        // suffixArr.printSuffixArr();
        ArrayList<Integer> locs = suffixArr.findSubstring(sub);
        locs.sort(Comparator.naturalOrder());
        for (int i = 0; i < locs.size(); i++) {
            if (i != 0) out.print(' ');
            out.print(locs.get(i));
        }
        // Arrays.stream(suffixArr.suffixArr).forEach(out::println);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(new BufferedOutputStream(System.out));
        // BufferedReader in = new BufferedReader(new FileReader("suffixarr.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("suffixarr.out")));
        new suffixarr(in, out);
        in.close();
        out.close();
    }

    class SuffixArray {
        class Rank {
            int i, rank, nextRank;
        }

        int[][] suffixRanks;
        int[] POW2, suffixArr;
        Rank[] ranks;
        int length, logLength;

        SuffixArray(String str) {
            // Gen POW2 array
            POW2 = new int[20];
            POW2[1] = 1;
            for (int i = 2; i < 20; i++) POW2[i] = POW2[i-1] * 2;

            length = str.length();
            for (int i = 2; i < 20; i++) {
                if (POW2[i] >= length) {
                    logLength = i;
                    break;
                }
            }

            suffixRanks = new int[logLength][length];
            ranks = new Rank[length];
            // Determine starting suffix ranks by first character
            for (int j = 0; j < length; j++) {
                suffixRanks[0][j] = str.charAt(j);
                ranks[j] = new Rank();
            }

            // Sort suffixes by first 2^i characters in each iteration
            for (int i = 1; i < logLength; i++) {
                for (int j = 0; j < length; j++) {
                    ranks[j].i = j;
                    ranks[j].rank = suffixRanks[i-1][j];
                    ranks[j].nextRank = (j + POW2[i] >= length) ? -1 : suffixRanks[i-1][j + POW2[i]];
                }

                // Sort ranks
                Arrays.sort(ranks, (r1, r2) -> {
                    if (r1.rank == r2.rank) return r1.nextRank - r2.nextRank;
                    else return r1.rank - r2.rank;
                });

                // Record ranks for next iteration
                for (int j = 0; j < length; j++) {
                    if (j != 0 && ranks[j-1].rank == ranks[j].rank && ranks[j-1].nextRank == ranks[j].nextRank) {
                        // Exact same ranks; both are tied for next iteration
                        suffixRanks[i][ranks[j].i] = suffixRanks[i][ranks[j-1].i];
                    } else {
                        // Different ranks (or 1st suffix); assign rank of j
                        suffixRanks[i][ranks[j].i] = j;
                    }
                }

                // printSuffixes(i);
            }

            // Gen final suffix array
            suffixArr = new int[length];
            for (int i = 0; i < length; i++) suffixArr[suffixRanks[logLength - 1][i]] = i;
        }

        void printSuffixes(int i) {
            System.out.println("Iteration " + i + ":");
            ArrayList<Integer>[] tempSuffixArr = new ArrayList[length];
            for (int j = 0; j < length; j++) tempSuffixArr[j] = new ArrayList<>(2);
            for (int j = 0; j < length; j++) {
                tempSuffixArr[suffixRanks[i][j]].add(j);
            }

            for (int j = 0; j < length; j++) {
                if (tempSuffixArr[j].isEmpty()) continue;
                for (int s : tempSuffixArr[j]) {
                    System.out.printf("%-10s\t%d%n", str.substring(s), j);
                }
            }
        }

        void printSuffixArr() {
            System.out.println("Suffix arr:");
            for (int j = 0; j < length; j++) System.out.println(str.substring(suffixArr[j]));
        }

        ArrayList<Integer> findSubstring(String sub) {
            // Do 1st binary search to find index to insert sub
            int low = 0, high = length;
            while (low < high) {
                int mid = (low + high) / 2;
                // Compare strings
                if (sub.compareTo(str.substring(suffixArr[mid])) <= 0) {
                    high = mid;
                } else low = mid + 1;
            }

            // Do 2nd binary search to find index to insert sub + '~' (highest ascii val)
            sub += '~';
            int low2 = 0, high2 = length;
            while (low2 < high2) {
                int mid = (low2 + high2) / 2;
                // Compare strings
                if (sub.compareTo(str.substring(suffixArr[mid])) <= 0) {
                    high2 = mid;
                } else low2 = mid + 1;
            }

            // System.out.println(low + " - " + low2);

            ArrayList<Integer> locs = new ArrayList<>(low2 - low);
            for (int i = low; i < low2; i++) {
                locs.add(suffixArr[i]);
            }
            return locs;
        }
    }
}