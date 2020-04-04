/*
Solution: Iterate through workers in order of increasing unit price (min require / qual).
The total cost of a set of workers is (curr unit price * sum of qual levels). If this cost
exceeds the budget, remove the worker with the highest qual level and try again.

Trying some small optimizations to bring this under the 3 second time limit.

Runtime: O(N * log(N))
*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;

@SuppressWarnings("unchecked")
public class hiring2 {
    int N;
    long W;
    Worker[] workers;

    hiring2(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        W = Long.parseLong(st.nextToken());
        workers = new Worker[N];
        int s, q;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            s = Integer.parseInt(st.nextToken());
            q = Integer.parseInt(st.nextToken());
            workers[i] = new Worker(s, q, i);
        }

        // Sort workers by unit cost
        Arrays.sort(workers, new Comparator<Worker>() {
            @Override
            public int compare(Worker o1, Worker o2) {
                double result = o1.unit - o2.unit;
                if (result < 0) return -1;
                else if (result > 0) return 1;
                return 0;
            }
        });

        // Find the value of H
        // Sort in decreasing order of qualification
        PriorityQueue<Worker> pastWorkers = new PriorityQueue<>(11, new Comparator<Worker>() {
            @Override
            public int compare(Worker o1, Worker o2) {
                if (o1.q - o2.q == 0) return o1.i - o2.i;
                else return o2.q - o1.q;
            }
        });
        int[] actionID = new int[N * 2];
        boolean[] actionSet = new boolean[N * 2];
        int currH = 0, bestH = 0, actionI = 0, wantedI = 0;
        long currQSum = 0;
        for (Worker w : workers) {
            double currUnit = w.unit;
            currQSum += w.q;
            pastWorkers.add(w);
            actionID[actionI] = w.i;
            actionSet[actionI++] = true;
            currH++;
            while (currUnit * currQSum - 0.0000000001 > W) {
                // Remove workers until budget satisfied
                Worker toRemove = pastWorkers.poll();
                actionID[actionI++] = toRemove.i;
                currQSum -= toRemove.q;
                currH--;
            }
            if (currH > bestH) {
                wantedI = actionI;  // Record last action to do
                bestH = currH;
            }
        }

        // Now, find the actual candidates by replaying the actions done on the priority queue
        boolean[] inQueue = new boolean[N];
        for (int i = 0; i < wantedI; i++) {
            inQueue[actionID[i]] = actionSet[i];
        }
        out.println(bestH);
        for (int i = 0; i < N; i++) {
            if (inQueue[i]) out.println(i+1);
        }
    }

    static class Worker {
        int s, q, i;
        double unit;
        Worker(int s, int q, int i) {
            this.s = s;
            this.q = q;
            this.i = i;
            unit = (double) s / q;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter out = new PrintWriter(System.out);
        // BufferedReader in = new BufferedReader(new FileReader("hiring.in"));
        // PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("hiring.out")));
        new hiring2(in, out);
        in.close();
        out.close();
    }
}
