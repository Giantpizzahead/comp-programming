/*
Solution: Iterate through the elements in ascending order, breaking ties with closest to left
first. Track max element found and element furthest to the right. At each stage of iteration,
make a partition point at location equal to # elements iterated, and time equal to
(furthest right index) - (# elements iterated).

Now, with location time pairs: Sort by time (break ties by left location).
Then, start tracking the splits with (start, end) pairs. Put these into a queue, and split
them up as needed, adding to the answer when required.

Runtime: O(N * log(N)) for both parts of the solution
*/

import java.util.*;
import java.io.*;

public class sort {
    int N;
    Pair[] sortedArr;  // Pairs are (element value, original element index)
    int[] arr;
    Pair[] partitionPoints;  // Pairs are (partition location, partition time)

    sort() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
        N = Integer.parseInt(fin.readLine());
        arr = new int[N];
        sortedArr = new Pair[N];
        for (int i = 0; i < N; i++) {
            arr[i] = Integer.parseInt(fin.readLine());
            sortedArr[i] = new Pair(arr[i], i);
        }
        fin.close();

        // Part 1: Find partition points and times
        Arrays.sort(sortedArr, new Comparator<Pair>() {
            @Override
            public int compare(Pair a, Pair b) {
                int result = a.a - b.a;
                if (result != 0) return result;
                else return a.b - b.b;
            }
        });
        findPartitionPoints();

        // Both locations and times are zero-indexed (partition at index 0 means to the right of 0)
        // Part 2: Find the answer
        Arrays.sort(partitionPoints, new Comparator<Pair>() {
            @Override
            public int compare(Pair a, Pair b) {
                int result = a.b - b.b;
                if (result != 0) return result;
                else return a.a - b.a;
            }
        });

        // System.out.println(Arrays.toString(partitionPoints));
        // Hardcode case where N = 1
        long answer = (N == 1) ? 0 : findAnswer();

        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        fout.println(answer);
        fout.close();
    }

    long findAnswer() {
        Queue<Pair> sections = new LinkedList<>();
        sections.add(new Pair(0, N));
        int numInProgress = N;
        long answer = numInProgress;
        int currLeft = 1;
        int nextLeft = 0;
        int currTime = partitionPoints[0].b;
        int partIndex = 0;
        Pair curr;
        while (!sections.isEmpty()) {
            curr = sections.poll();
            // System.out.println(curr);
            if (currLeft == 0) {
                currLeft = nextLeft;
                nextLeft = 0;
                // Optimization in case next partition point is a long way away
                if (partIndex == partitionPoints.length) {
                    // Done; break
                    break;
                }
                int timeToChange = partitionPoints[partIndex].b - currTime;
                // System.out.println(numInProgress);
                answer += (long) numInProgress * timeToChange;
                currTime += timeToChange;
            }
            currLeft--;

            if (curr.b - curr.a == 1) {
                continue;  // Length 1 can be ignored
            }

            // Split this section into as many parts as possible
            while (partIndex != partitionPoints.length && partitionPoints[partIndex].b == currTime && partitionPoints[partIndex].a < curr.b) {
                sections.add(new Pair(curr.a, partitionPoints[partIndex].a + 1));
                if (partitionPoints[partIndex].a + 1 - curr.a == 1) numInProgress--;
                curr.a = partitionPoints[partIndex].a + 1;
                nextLeft++;
                partIndex++;
            }

            // Add last section
            sections.add(new Pair(curr.a, curr.b));
            if (curr.b - curr.a == 1) numInProgress--;
            nextLeft++;
        }

        return answer;
    }

    void findPartitionPoints() {
        partitionPoints = new Pair[N-1];
        int furthestRight = sortedArr[0].b;
        for (int i = 0; i < N-1; i++) {
            furthestRight = Math.max(sortedArr[i].b, furthestRight);
            partitionPoints[i] = new Pair(i, furthestRight - i);
        }
    }

    public static void main(String[] args) throws IOException {
        new sort();
    }

    static class Pair {
        int a, b;
        Pair(int a, int b) {
            this.a = a;
            this.b = b;
        }

        @Override
        public String toString() {
            return "(" + a + ", " + b + ")";
        }
    }
}
