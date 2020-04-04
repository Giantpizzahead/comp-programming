/*
ID: sunnyky1
LANG: JAVA
TASK: wormhole

Solution: Try all possible pairings, and see if each individual one works or not. Store the
'next' wormhole in a array, and also store a 'visited' array to check if a cycle exists. This
works because the # of possible pairings is actually quite low (~10000).
 */

import java.util.*;
import java.io.*;

public class wormhole {
    int N;
    int[] nextWormhole;
    Point[] wormholeLocs;

    wormhole() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort3.in"));
        N = Integer.parseInt(fin.readLine());
        wormholeLocs = new Point[N];
        int x, y;
        for (int i = 0; i < N; i++) {
            StringTokenizer st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            y = Integer.parseInt(st.nextToken());
            wormholeLocs[i] = new Point(x, y);
        }
        fin.close();

        // Find which wormholes lead to which
        // First, sort wormholes in left to right, then top to bottom order
        Arrays.sort(wormholeLocs, (a, b) -> {
            if (a.y != b.y) return a.y - b.y;
            else if (a.x != b.x) return a.x - b.x;
            else return 0;
        });
        nextWormhole = new int[N];
        for (int i = 1; i < N; i++) {
            if (wormholeLocs[i-1].y != wormholeLocs[i].y) {
                // Last wormhole was the final one in that row
                // It doesn't lead to any next wormhole
                nextWormhole[i-1] = -1;
            } else {
                // Last wormhole leads to this one
                nextWormhole[i-1] = i;
            }
        }
        // Last wormhole in list doesn't go anywhere
        nextWormhole[N-1] = -1;

        // System.out.println(Arrays.toString(nextWormhole));

        int[] pairings = new int[N];
        for (int i = 0; i < N; i++) pairings[i] = -1;

        int answer = tryAllPairs(0, pairings);
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("wormhole.out")));
        fout.println(answer);
        fout.close();
    }

    int tryAllPairs(int i, int[] pairings) {
        int numWorked = 0;
        if (i < N) {
            // Continue genning pairs
            if (pairings[i] == -1) {
                // Choose an unused wormhole to pair with
                for (int j = i + 1; j < N; j++) {
                    if (pairings[j] == -1) {
                        pairings[i] = j;
                        pairings[j] = i;
                        numWorked += tryAllPairs(i + 1, pairings);
                        pairings[i] = -1;
                        pairings[j] = -1;
                    }
                }
            } else {
                numWorked = tryAllPairs(i + 1, pairings);
            }
            return numWorked;
        } else {
            // Test
            // System.out.println(Arrays.toString(pairings));
            return testPairings(pairings) ? 1 : 0;
        }
    }

    boolean testPairings(int[] pairings) {
        // Try starting from every unvisited wormhole
        boolean[] visited = new boolean[N];
        int curr;
        outerLoop:
        for (int i = 0; i < N; i++) {
            if (visited[i]) continue;
            curr = i;
            // Go 13 times max; if it doesn't reach -1 by then, there's a cycle
            for (int j = 0; j < 13; j++) {
                visited[curr] = true;
                if (nextWormhole[curr] == -1) continue outerLoop;
                curr = pairings[nextWormhole[curr]];
            }
            return true;
        }

        // No valid cycle
        return false;
    }

    public static void main(String[] args) throws IOException {
        new wormhole();
    }

    static class Point {
        int x, y;
        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }
}
