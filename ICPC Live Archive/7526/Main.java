/*
Solution: First, create a prefix sum array for the # of broken diodes in each row.

Then, to find the solution, try every x range from 0 to 300. (N^2)
For each x range: First, simulate using the spare rows to fix all the top rows. Add the #
of broken diodes for all these rows to a priority queue. Also keep a size m used array to
track whether or not you used the spare diodes to repair that row.

Iterate through each row, and replace one of the spare rows used with individual diodes.
Always choose the one with the minimum # of broken diodes (get from pq). If the item gotten
from the priority queue is out of the currently checked y range, skip it.

When your # of remaining spares reaches 0, move the top row down. If that row was marked as
used (spare diodes replaced row fix), add back the # of diodes in that row. Else, replace the
max # of broken diodes that was fixed back to the # of diodes (keep track of this in a max
priority queue). Keep track of the max height that the search ever grows to be.

Max all the answers you get using this method to find the max # of pixels.

Runtime: O(N^3 * log(N)) - Barely enough, since this is just an approximation (actual runtime
is a bit less)
*/

import java.io.*;
import java.util.*;

public class Main {
    int rows, cols, sRows, sDiodes;
    boolean[][] board;
    int[][] prefix;

    Main() throws IOException {
        Scanner in = new Scanner(System.in);
        PrintWriter out = new PrintWriter(System.out);
        boolean running = true;
        while (running) {
            running = runTestCase(in, out);
        }
        in.close();
        out.close();
    }

    boolean runTestCase(Scanner in, PrintWriter out) throws IOException {
        rows = in.nextInt();
        cols = in.nextInt();
        sRows = in.nextInt();
        sDiodes = in.nextInt();
        if (rows == 0 && cols == 0 && sRows == 0 && sDiodes == 0) return false;
        // Special cases
        if (rows == 0 || cols == 0) {
            out.println(0);
            return true;
        }
        sRows = Math.min(sRows, rows);
        board = new boolean[rows][cols];
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                board[y][x] = in.nextInt() == 1;
            }
        }

        // Generate prefix sum array
        prefix = new int[rows][cols];
        for (int y = 0; y < rows; y++) {
            int sum = 0;
            for (int x = 0; x < cols; x++) {
                sum += board[y][x] ? 0 : 1;
                prefix[y][x] = sum;
            }
        }

        // Try every x range (inclusive on both ends)
        int answer = 0;
        for (int x1 = 0; x1 < cols; x1++) {
            for (int x2 = x1; x2 < cols; x2++) {
                answer = Math.max(tryRange(x1, x2) * (x2 - x1 + 1), answer);
            }
        }
        out.println(answer);

        return true;
    }

    int tryRange(int x1, int x2) {
        boolean[] used = new boolean[rows];
        int currSDiodes = sDiodes;
        // Sorted in increasing order to use least first
        PriorityQueue<Row> usingRows = new PriorityQueue<>(Comparator.comparingInt(a -> a.numBroken));
        // Sorted in decreasing order to save as many diodes as possible
        PriorityQueue<Row> usingDiodes = new PriorityQueue<>(Comparator.comparingInt(a -> 301 - a.numBroken));

        // Add initial rows (using spare rows)
        for (int i = 0; i < sRows; i++) {
            usingRows.add(new Row(i, numBroken(i, x1, x2)));
        }

        int biggestRange = sRows;
        int currTop = 0;
        for (int currBot = sRows; currBot < rows; currBot++) {
            // Add the new row
            Row toAdd = new Row(currBot, numBroken(currBot, x1, x2));
            usingRows.add(toAdd);

            // Add current row by replacing a previous row with diodes instead
            Row toReplace;
            do {
                toReplace = usingRows.poll();
            } while (toReplace != null && toReplace.index < currTop);  // To prevent replacing already done rows

            if (toReplace != null) {
                currSDiodes -= toReplace.numBroken;
                usingDiodes.add(toReplace);
                used[toReplace.index] = true;
            }

            // If new row cannot be added without removing some previous rows, remove them
            while (currSDiodes < 0) {
                if (used[currTop]) {
                    // Just add back the # of diodes used
                    currSDiodes += numBroken(currTop, x1, x2);
                } else {
                    // Use the newly acquired spare row on the row with the most broken diodes
                    Row toRemove;
                    do {
                        toRemove = usingDiodes.poll();
                    } while (toRemove != null && toRemove.index < currTop);

                    if (toRemove != null) {
                        currSDiodes += toRemove.numBroken;
                    }
                }
                currTop++;
            }

            biggestRange = Math.max(currBot - currTop + 1, biggestRange);
        }

        return biggestRange;
    }

    int numBroken(int row, int x1, int x2) {
        return prefix[row][x2] - ((x1 == 0) ? 0 : prefix[row][x1-1]);
    }

    public static void main(String[] args) throws IOException {
        new Main();
    }

    static class Row {
        int index, numBroken;
        Row(int index, int numBroken) {
            this.index = index;
            this.numBroken = numBroken;
        }
    }
}