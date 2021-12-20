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

public class billboard2 {
    int rows, cols, sRows, sDiodes;
    boolean[][] board;
    short[][] prefix;
    TreeSet<Row> usingRows = new TreeSet<>(new Comparator<Row>() {
        @Override
        public int compare(Row a, Row b) {
            if (a.numBroken == b.numBroken) return a.index - b.index;
            else return a.numBroken - b.numBroken;
        }
    });
    TreeSet<Row> usingDiodes = new TreeSet<>(new Comparator<Row>() {
        @Override
        public int compare(Row a, Row b) {
            if (a.numBroken == b.numBroken) return a.index - b.index;
            else return b.numBroken - a.numBroken;
        }
    });

    billboard2() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        board = new boolean[300][300];
        prefix = new short[300][300];
        boolean running = true;
        while (running) {
            running = runTestCase(in, out);
        }
        in.close();
        out.close();
    }

    boolean runTestCase(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        rows = Integer.parseInt(st.nextToken());
        cols = Integer.parseInt(st.nextToken());
        sRows = Integer.parseInt(st.nextToken());
        sDiodes = Integer.parseInt(st.nextToken());
        if (rows == 0 && cols == 0 && sRows == 0 && sDiodes == 0) return false;
        // Special cases
        if (rows == 0 || cols == 0) {
            out.println(0);
            out.flush();
            return true;
        }
        sRows = Math.min(sRows, rows);
        for (int y = 0; y < rows; y++) {
            String line = in.readLine();
            short sum = 0;
            for (int x = 0; x < cols; x++) {
                board[y][x] = line.charAt(x * 2) == '1';
                sum += board[y][x] ? 0 : 1;
                prefix[y][x] = sum;
            }
        }

        // Try every x range (inclusive on both ends)
        // Cheap optimization: If answer is better than max possible you could get from testing a range, don't test it
        // Optimization 2: Test biggest ranges first
        int answer = 0;
        for (int rangeSize = cols; rangeSize > 0; rangeSize--) {
            for (int startX = 0; startX <= cols - rangeSize; startX++) {
                if (answer < rangeSize * rows) answer = Math.max(tryRange(startX, startX + rangeSize - 1) * rangeSize, answer);
                else break;
            }
        }
        out.println(answer);
        out.flush();
        return true;
    }

    int tryRange(int x1, int x2) {
        boolean[] used = new boolean[rows];
        int currSDiodes = sDiodes;
        // Sorted in increasing order to use least first
        usingRows.clear();
        // Sorted in decreasing order to save as many diodes as possible
        usingDiodes.clear();

        // Add initial rows (using spare rows)
        for (int i = 0; i < sRows; i++) {
            usingRows.add(new Row(i, prefix[i][x2] - ((x1 == 0) ? 0 : prefix[i][x1-1])));
        }

        int biggestRange = sRows;
        int currTop = 0;
        for (int currBot = sRows; currBot < rows; currBot++) {
            // Add the new row
            Row toAdd = new Row(currBot, prefix[currBot][x2] - ((x1 == 0) ? 0 : prefix[currBot][x1-1]));

            // Check if it might be beneficial to switch a previously dioded row with the current row
            if (!usingDiodes.isEmpty()) {
                Row toSwitch = usingDiodes.first();
                if (toSwitch.numBroken > toAdd.numBroken) {
                    // Switch the dioded row
                    usingDiodes.remove(toSwitch);
                    usingDiodes.add(toAdd);
                    usingRows.add(toSwitch);
                    used[toSwitch.index] = false;
                    used[toAdd.index] = true;
                    currSDiodes = currSDiodes + toSwitch.numBroken - toAdd.numBroken;
                } else {
                    // Just add this row
                    usingRows.add(toAdd);
                }
            } else {
                // Just add this row
                usingRows.add(toAdd);
            }

            // Add current row by replacing a previous row with diodes instead
            Row toReplace = usingRows.pollFirst();
            if (toReplace != null) {
                currSDiodes -= toReplace.numBroken;
                usingDiodes.add(toReplace);
                used[toReplace.index] = true;
            }

            // If new row cannot be added without removing some previous rows, remove them
            while (currSDiodes < 0 && currTop <= currBot) {
                if (used[currTop]) {
                    // Just add back the # of diodes used
                    currSDiodes += prefix[currTop][x2] - ((x1 == 0) ? 0 : prefix[currTop][x1-1]);
                    // Remove this row from the TreeSet
                    usingDiodes.remove(new Row(currTop, prefix[currTop][x2] - ((x1 == 0) ? 0 : prefix[currTop][x1-1])));
                } else {
                    // Use the newly acquired spare row on the row with the most broken diodes
                    Row toRemove = usingDiodes.pollFirst();
                    if (toRemove != null) {
                        currSDiodes += toRemove.numBroken;
                    }
                    // Remove this row from the TreeSet
                    usingRows.remove(new Row(currTop, prefix[currTop][x2] - ((x1 == 0) ? 0 : prefix[currTop][x1-1])));
                }
                currTop++;
            }

            biggestRange = Math.max(currBot - currTop + 1, biggestRange);
        }

        return biggestRange;
    }

    public static void main(String[] args) throws IOException {
        new billboard2();
    }

    static class Row {
        int index, numBroken;
        Row(int index, int numBroken) {
            this.index = index;
            this.numBroken = numBroken;
        }
    }
}