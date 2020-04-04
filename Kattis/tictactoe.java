/*
Solution: Use DP to check all rows, columns, and diagonals in a reasonable amount of time.
Check all of these separately to avoid confusion.

DP for rows: dp[i][j] = Max in a row including the cell at (i, j) and all cells with x 0...i
dp[i][j] = dp[i-1][j] if same symbol, else 1
Once any dp reaches m, that player won; record all the cells where the player could've placed
the last X/O to win
If at any time the dp reaches m twice, or it reaches (equals) m * 2, then impossible

DP for columns: Similar to rows

DP for top-left to bottom-right diagonals: dp[i][j] = Max in a \ diagonal including cell at
(i, j) and all cells with x 0...i-1 and y 0...j-1
dp[i][j] = dp[i-1][j-1] if same symbol, else 1
Rest is the same as rows

DP for top-right to bottom-left diagonals: Similar to \ diagonal

If multiple DPs gave a win:
Find the union of each DP HashSet containing the cells that gave the player a win. If after
all the unions, a valid cell still exists, then it's valid. Else, impossible.

Ending checks:
If O won and # of Xs != # of Os, impossible
If X won and # of Xs != # of Os - 1, impossible
If draw and # of each symbol doesn't match (depending on even or odd), impossible

Runtime: O(4 * N^2)
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class tictactoe {
    int N, M, numXs, numOs;
    int[][] dp;
    char[][] board;
    char winner = '?';
    HashSet<Integer> rows, columns, diags1, diags2;

    tictactoe() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        board = new char[N][N];
        numXs = 0;
        numOs = 0;
        for (int y = 0; y < N; y++) {
            String line = in.readLine();
            for (int x = 0; x < N; x++) {
                board[y][x] = line.charAt(x);
                if (board[y][x] == 'X') numXs++;
                else if (board[y][x] == 'O') numOs++;
            }
        }
        in.close();

        if (M == 1) {
            // Special case: Handle this one separately
            // There can be at max 1 symbol
            for (int y = 0; y < N; y++) {
                for (int x = 0; x < N; x++) {
                    if (board[y][x] != '.') {
                        if (winner != '?') {
                            // Impossible
                            System.out.println("ERROR");
                            return;
                        } else {
                            winner = board[y][x];
                        }
                    }
                }
            }

            if (winner == '?') System.out.println("IN PROGRESS");
            else System.out.println(winner + " WINS");
            return;
        }

        // Do all the dps
        dp = new int[N][N];
        rows = new HashSet<>();
        columns = new HashSet<>();
        diags1 = new HashSet<>();
        diags2 = new HashSet<>();
        if (!doDP('R') || !doDP('C') || !doDP('\\') || !doDP('/')) {
            // Impossible
            System.out.println("ERROR");
            return;
        }

        // Check if no wins occurred
        if (rows.isEmpty() && columns.isEmpty() && diags1.isEmpty() && diags2.isEmpty()) {
            // Do some final checks to make sure nothing's impossible
            if (numXs == numOs || numXs - 1 == numOs) {
                // Count of Xs and Os is fine; check for draw
                if (numXs + numOs == N * N) {
                    // Draw
                    System.out.println("DRAW");
                } else {
                    // Still playing
                    System.out.println("IN PROGRESS");
                }
            } else {
                // Count of Xs and Os is impossible
                System.out.println("ERROR");
            }
            return;
        }

        // Check for multiple wins, and see if they're valid
        HashSet<Integer> wins = new HashSet<>();
        HashSet<Integer>[] winSets = new HashSet[] {rows, columns, diags1, diags2};

        /*
        for (HashSet<Integer> s : winSets) {
            System.out.println(s);
        }
         */

        int currSet = 0;
        while (wins.isEmpty()) {
            if (!winSets[currSet].isEmpty()) wins.addAll(winSets[currSet]);
            currSet++;
        }

        // Union all the remaining sets
        for (; currSet < winSets.length; currSet++) {
            if (!winSets[currSet].isEmpty()) {
                HashSet<Integer> unioned = new HashSet<>();
                for (int w : wins) {
                    if (winSets[currSet].contains(w)) unioned.add(w);
                }
                wins = unioned;
            }
        }

        // If the final set is empty, then no one spot could've won the game
        if (wins.isEmpty()) {
            System.out.println("ERROR");
            return;
        }

        // Final sanity checks
        if (winner == 'X' && numXs - 1 != numOs) {
            System.out.println("ERROR");
        } else if (winner == 'O' && numXs != numOs) {
            System.out.println("ERROR");
        } else {
            // Finally, print the winner
            System.out.println(winner + " WINS");
        }
    }

    boolean doDP(char type) {
        int cx, cy;
        HashSet<Integer> hashset;

        switch (type) {
            case 'R':
                cx = 1;
                cy = 0;
                // Base cases
                for (int y = 0; y < N; y++) dp[y][0] = (board[y][0] == '.') ? 0 : 1;
                hashset = rows;
                // Main DP
                for (int y = 0; y < N; y++) {
                    for (int x = 1; x < N; x++) {
                        if (!eval(x, y, cx, cy, hashset)) return false;
                    }
                }
                break;
            case 'C':
                cx = 0;
                cy = 1;
                // Base cases
                for (int x = 0; x < N; x++) dp[0][x] = (board[0][x] == '.') ? 0 : 1;
                hashset = columns;
                // Main DP
                for (int x = 0; x < N; x++) {
                    for (int y = 1; y < N; y++) {
                        if (!eval(x, y, cx, cy, hashset)) return false;
                    }
                }
                break;
            case '\\':
                cx = 1;
                cy = 1;
                // Base cases
                for (int x = 0; x < N; x++) dp[0][x] = (board[0][x] == '.') ? 0 : 1;
                for (int y = 0; y < N; y++) dp[y][0] = (board[y][0] == '.') ? 0 : 1;
                hashset = diags1;
                // Main DP
                for (int x = 1; x < N; x++) {
                    for (int y = 1; y < N; y++) {
                        if (!eval(x, y, cx, cy, hashset)) return false;
                    }
                }
                break;
            default:
                // / diagonal case
                cx = -1;
                cy = 1;
                // Base cases
                for (int x = 0; x < N; x++) dp[0][x] = (board[0][x] == '.') ? 0 : 1;
                for (int y = 0; y < N; y++) dp[y][N-1] = (board[y][N-1] == '.') ? 0 : 1;
                hashset = diags2;
                // Main DP
                for (int x = N-2; x >= 0; x--) {
                    for (int y = 1; y < N; y++) {
                        if (!eval(x, y, cx, cy, hashset)) return false;
                    }
                }
        }

        return true;
    }

    boolean eval(int x, int y, int cx, int cy, HashSet<Integer> hashset) {
        if (board[y][x] == '.') {
            dp[y][x] = 0;
        } else if (board[y][x] == board[y-cy][x-cx]) {
            dp[y][x] = dp[y-cy][x-cx] + 1;
            if (dp[y][x] == M) {
                // Target-in-a-row reached; add valid cells to HashSet
                if (hashset.size() != 0) {
                    // Two rows in different places; Impossible
                    return false;
                } else if (winner != '?' && board[y][x] != winner) {
                    // Winner is different...???
                    return false;
                } else {
                    // Just set the winner for now
                    winner = board[y][x];
                }
            } else if (dp[y][x] >= 2 * M) {
                // Too many in a row to make with one piece; Impossible
                return false;
            }
        } else {
            // Reset; New player's pieces
            dp[y][x] = 1;
        }

        // Update HashSet if needed
        if ((dp[y][x] <= 1 && dp[y-cy][x-cx] >= M) || (dp[y][x] >= M && !inBounds(x+cx, y+cy))) {
            if ((dp[y][x] >= M && !inBounds(x+cx, y+cy))) {
                // Simulate being in the next location
                x += cx;
                y += cy;
            }
            // Add middle cells to HashSet
            int numInARow = dp[y-cy][x-cx];
            for (int i = numInARow - M + 1; i < M + 1; i++) {
                hashset.add(hashCoords(x-i*cx, y-i*cy));
            }
        }

        return true;
    }

    boolean inBounds(int x, int y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    int hashCoords(int x, int y) {
        return x * 1001 + y;
    }

    public static void main(String[] args) throws IOException {
        new tictactoe();
    }
}
