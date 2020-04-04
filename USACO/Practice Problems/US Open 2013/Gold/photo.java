/*
Solution: DP with an optimized previous state selection process. Sort the segments
by the start point. While iterating through each cow, track the ID of the latest
segment that is no longer active, and the latest segment that is active.

Precompute the max endpoint in segments 1 to M for use during the dp.
(Everything here is 1-indexed)

To process a new cow, first update any segments that start or end at the current
index (update the 2 IDs accordingly). Next, check the pq, and put any new states
into the state array. Then, get the previous state by looking for a state with #
constraints satisfied = Latest non-active segment. Add the new state to a pq with
# constraints satisfied = latest active segment, value = # spotted cows + 1, and set
it's max endpoint value accordingly.

The answer is the state with all constraints satisfied.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

public class photo {
    int N, M;
    int[] maxEndpoint;
    Pair[] segments;
    final int INF = 999999999;

    photo() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("photo.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());
        segments = new Pair[M + 1];
        segments[0] = new Pair(-INF, -INF);
        for (int i = 1; i <= M; i++) {
            st = new StringTokenizer(fin.readLine());
            segments[i] = new Pair(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
        }
        fin.close();
        Arrays.sort(segments, Comparator.comparingInt(x -> x.a));

        int currEndpoint = 0;
        maxEndpoint = new int[M + 1];
        for (int i = 1; i <= M; i++) {
            currEndpoint = Math.max(segments[i].b, currEndpoint);
            maxEndpoint[i] = currEndpoint;
        }

        int answer = doDP();
        PrintWriter fout = new PrintWriter("photo.out");
        fout.println(Math.max(answer, -1));
        fout.close();
    }

    int doDP() {
        int[] prevStates = new int[M + 1];
        Arrays.fill(prevStates, -INF);
        prevStates[0] = 0;

        PriorityQueue<Triple> nextStates = new PriorityQueue<>(Comparator.comparingInt(x -> x.c));
        PriorityQueue<Pair> currSegs = new PriorityQueue<>(Comparator.comparingInt(x -> x.a));

        int latestActive = 0, latestInactive = 0;
        for (int i = 1; i <= N; i++) {
            // System.out.println("i = " + i);
            // System.out.println(Arrays.toString(prevStates));
            // Update segments
            while (latestActive != M && segments[latestActive + 1].a <= i) {
                // Segment started
                // System.out.println("Seg started: " + (latestActive + 1));
                currSegs.add(new Pair(segments[++latestActive].b, latestActive));
            }
            while (!currSegs.isEmpty() && currSegs.peek().a < i) {
                // Segment ended
                // System.out.println("Seg ended: " + (currSegs.peek().b));
                latestInactive = Math.max(currSegs.poll().b, latestInactive);
            }

            // Update next states
            while (!nextStates.isEmpty() && nextStates.peek().c < i) {
                Triple ns = nextStates.poll();
                prevStates[ns.a] = Math.max(ns.b, prevStates[ns.a]);
            }

            // Add a new state
            nextStates.add(new Triple(latestActive, prevStates[latestInactive] + 1, maxEndpoint[latestActive]));
        }

        // Do a final check for pending states
        while (!nextStates.isEmpty()) {
            Triple ns = nextStates.poll();
            prevStates[ns.a] = Math.max(ns.b, prevStates[ns.a]);
        }

        return prevStates[M];
    }

    public static void main(String[] args) throws IOException {
        new photo();
    }

    class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }
    }

    class Triple {
        int a, b, c;
        Triple(int a, int b, int c) {
            this.a = a;
            this.b = b;
            this.c = c;
        }
    }
}