/*
Solution: Do a whole lot of DP. Split the problem up into individual problems, each for a specific
shared edge y coordinate (N problems). For each of these problems:
First, calculate the max rectangle with left endpoint = the problem's left corner x, right endpoint x2,
with either the top or bottom edge's y known (2 * N^2). This can be done in O(N^2) time by again splitting
it into N problems where the 2 x endpoints are set, then iterating downwards to find the max size rects.
Next, iterate through every possible left x coordinate, starting from the one closest to the
right (Runs in N since y coord is already set). Keep a max array with the new maximum area of any rects
that have right endpoint <= a certain x coordinate. Add any new rectangles that can now be used into the
max array. After doing this:
Iterate through every possible right x coordinate, updating the area of the bottom rectangle / maxing
the area of the top rectangle. Max the sums of these with the answer.

Runtime: O(N^3)
*/

import java.util.*;
import java.io.*;

public class eight {
    int N;
    long answer = -1;
    int[][] prefixStars;
    char[][] grid;
    final int INF = 987654321;

    eight() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("eight.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        grid = new char[N+1][];
        // For easier implementation
        grid[N] = new char[N];
        Arrays.fill(grid[N], '*');
        for (int y = 0; y < N; y++) {
            String str = fin.readLine();
            grid[y] = str.toCharArray();
        }
        fin.close();

        // Generate prefix sum array for # of stars in a given range of a row
        prefixStars = new int[N][N];
        for (int y = 0; y < N; y++) {
            int currStars = 0;
            for (int x = 0; x < N; x++) {
                currStars += (grid[y][x] == '*') ? 1 : 0;
                prefixStars[y][x] = currStars;
            }
        }

        // Check dp gen
        // System.out.println(rectDP(2)[12][7][0]);

        // Do main queries
        doQueries();

        PrintWriter fout = new PrintWriter("eight.out");
        fout.println((answer == 0) ? -1 : answer);
        fout.close();
    }

    void doQueries() {
        // int[y][x] = Max area of top rectangle that has bottom-right endpoint at (x, y)
        int[][] maxTopArea = new int[N][N];
        for (int lx = N - 3; lx >= 0; lx--) {
            // Generate required rectangle info
            // State: (y, rightX, fixedBottom (0) or fixedTop (1))
            int[][][] maxRectAreas = rectDP(lx);
            for (int y = 0; y < N; y++) {
                // Update rectangle areas
                for (int rx = lx + 2; rx < N; rx++) {
                    maxTopArea[y][rx] = Math.max(maxRectAreas[y][rx][0], maxTopArea[y][rx]);
                }

                // Iterate through bottom-right endpoint
                int currTopArea = 0;
                for (int rx = lx + 2; rx < N; rx++) {
                    currTopArea = Math.max(maxTopArea[y][rx], currTopArea);
//                    if ((long) maxRectAreas[y][rx][1] * currTopArea > answer) {
//                        System.out.println("New best answer with rects " + maxRectAreas[y][rx][1] + " and " + currTopArea);
//                    }
                    answer = Math.max((long) maxRectAreas[y][rx][1] * currTopArea, answer);
                }
            }
        }
    }

    int[][][] rectDP(int leftX) {
        int[][][] dp = new int[N][N][2];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) Arrays.fill(dp[i][j], -INF);
        }

        // Set rightX
        for (int rightX = leftX + 2; rightX < N; rightX++) {
            // Main DP
            int highestSeg = -1, lowestSeg = -1;
            Queue<Integer> prevSegs = new LinkedList<>();
            for (int y = 0; y < N + 1; y++) {
                if (grid[y][leftX] == '*' || grid[y][rightX] == '*') {
                    // Rectangles are cut off here; reset everything
                    while (!prevSegs.isEmpty()) {
                        int prevY = prevSegs.poll();
                        if (lowestSeg - prevY >= 2) {
                            dp[prevY][rightX][1] = (lowestSeg - prevY - 1) * (rightX - leftX - 1);
                        }
                    }
                    highestSeg = -1;
                    lowestSeg = -1;
                } else if (starSum(y, leftX, rightX) == 0) {
                    // Segment can be put here
                    if (highestSeg == -1) highestSeg = y;
                    else if (y - highestSeg >= 2){
                        // Update area
                        dp[y][rightX][0] = (y - highestSeg - 1) * (rightX - leftX - 1);
                    }
                    lowestSeg = y;
                    prevSegs.add(y);
                }
            }
        }

//        System.out.println("leftX=" + leftX);
//        for (int i = 0; i < N; i++) {
//            System.out.println(Arrays.deepToString(dp[i]));
//        }
        return dp;
    }

    int starSum(int y, int lx, int rx) {
        return prefixStars[y][rx] - ((lx == 0) ? 0 : prefixStars[y][lx-1]);
    }

    public static void main(String[] args) throws IOException {
        new eight();
    }
}
