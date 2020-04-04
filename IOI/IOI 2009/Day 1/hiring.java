/*
Solution: Iterate through workers in order of increasing unit price (min require / qual).
The total cost of a set of workers is (curr unit price * sum of qual levels). If this cost
exceeds the budget, remove the worker with the highest qual level and try again.

1st iter is to find H. 2nd iter will find the actual candidates to hire.

Runtime: O(N * log(N))
*/

import java.util.*;
import java.io.*;

@SuppressWarnings("unchecked")
public class hiring {
    int N;
    long W;
    ArrayList<Worker>[] qToWorkers;
    Worker[] workers;

    hiring(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        W = Long.parseLong(st.nextToken());
        qToWorkers = new ArrayList[20001];
        for (int i = 0; i < 20001; i++) qToWorkers[i] = new ArrayList<>(2);
        workers = new Worker[N];
        int s, q;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(in.readLine());
            s = Integer.parseInt(st.nextToken());
            q = Integer.parseInt(st.nextToken());
            workers[i] = new Worker(s, q, i);
            qToWorkers[q].add(workers[i]);
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
        TreeSet<Worker> pastWorkers = new TreeSet<>(new Comparator<Worker>() {
            @Override
            public int compare(Worker o1, Worker o2) {
                if (o1.q - o2.q == 0) return o1.i - o2.i;
                else return o1.q - o2.q;
            }
        });
        int currH = 0, bestH = 0;
        double maxUnit = 999999999;
        long currQSum = 0;
        for (Worker w : workers) {
            double currUnit = w.unit;
            currQSum += w.q;
            pastWorkers.add(w);
            currH++;
            while (currUnit * currQSum - 0.0000000001 > W) {
                // Remove workers until budget satisfied
                Worker toRemove = pastWorkers.pollLast();
                currQSum -= toRemove.q;
                currH--;
            }
            if (currH > bestH) {
                maxUnit = currUnit;
                bestH = currH;
            }
        }

        // Now, find the actual candidates
        out.println(bestH);
        currH = 0;
        outer:
        for (int i = 0; i < 20001; i++) {
            for (Worker w : qToWorkers[i]) {
                if (w.unit <= maxUnit) {
                    out.println(w.i + 1);
                    if (++currH == bestH) break outer;
                }
            }
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
        new hiring(in, out);
        in.close();
        out.close();
    }
}
