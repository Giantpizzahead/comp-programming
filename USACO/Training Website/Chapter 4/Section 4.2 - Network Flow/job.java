/*
ID: sunnyky1
LANG: JAVA
TASK: job

Solution: Use a greedy algorithm to match jobs to machines for the "A" tasks. To do this,
track the earliest possible finishing time for each machine, and greedily choose the
earliest finishing time for each job. Do the same thing in reverse for the finished jobs
to the "B" tasks.
Now, join the two greedy solutions together. Try to start the B greedy algorithm as early
as possible after the A one, and increase this start time if not enough jobs become
available. Output the answer after increasing the start time as needed.
Runtime: O(N * log(M1 + M2))
*/

import java.util.*;
import java.io.*;

public class job {
    int N, M1, M2;
    int[] timeA, timeB, finishA, finishB;

    job(BufferedReader in, PrintWriter out) throws IOException {
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        M1 = Integer.parseInt(st.nextToken());
        M2 = Integer.parseInt(st.nextToken());
        timeA = new int[M1];
        timeB = new int[M2];
        for (int i = 0; i < M1; i++) {
            if (!st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
            timeA[i] = Integer.parseInt(st.nextToken());
        }
        for (int i = 0; i < M2; i++) {
            if (!st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
            timeB[i] = Integer.parseInt(st.nextToken());
        }

        // Greedily generate finishing times for task A & reversed task B
        finishA = genFinishTimes(M1, timeA);
        finishB = genFinishTimes(M2, timeB);
//        System.out.println(Arrays.toString(finishA));
//        System.out.println(Arrays.toString(finishB));

        // Find the time that the A greedy finishes
        int endTimeA = 0;
        for (int i = 0; i < N; i++) endTimeA = Math.max(finishA[i], endTimeA);

        // Now, find the earliest possible time that the B greedy can end
        int endTimeB = endTimeA;
        for (int i = 0; i < N; i++) {
            // Time to finish task A + Time to finish task B
            endTimeB = Math.max(finishA[i] + finishB[N-1-i], endTimeB);
        }

        out.println(endTimeA + " " + endTimeB);
    }

    int[] genFinishTimes(int M, int[] times) {
        PriorityQueue<Machine> pq = new PriorityQueue<>(new Comparator<Machine>() {
            @Override
            public int compare(Machine o1, Machine o2) {
                return o1.t - o2.t;
            }
        });
        // Add initial machine finish times (all ready from time 0)
        for (int i = 0; i < M; i++) pq.add(new Machine(times[i], i));

        // Assign all jobs to machines
        int[] finish = new int[N];
        for (int i = 0; i < N; i++) {
            Machine m = pq.poll();
            finish[i] = m.t;
            // Machine can be reused after times[i] seconds
            pq.add(new Machine(m.t + times[m.i], m.i));
        }
        return finish;
    }

    static class Machine {
        int t, i;
        Machine(int t, int i) {
            this.t = t;
            this.i = i;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("job.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("job.out")));
        new job(in, out);
        in.close();
        out.close();
    }
}
