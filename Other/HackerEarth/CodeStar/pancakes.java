package CodeStar;/*
Solution: Greedy using a pq.
*/

import java.util.*;
import java.io.*;

public class pancakes {
    int N, K;
    int[] pancakes;

    pancakes() throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(in.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        pancakes = new int[N];
        st = new StringTokenizer(in.readLine());
        for (int i = 0; i < N; i++) {
            pancakes[i] = Integer.parseInt(st.nextToken());
        }
        in.close();

        greedy();
    }

    void greedy() {
        PriorityQueue<State> pq = new PriorityQueue<>(new Comparator<State>() {
            @Override
            public int compare(State a, State b) {
                return a.n - b.n;
            }
        });

        // Initial push
        for (int i = 0; i < Math.min(K+1, N); i++) {
            pq.add(new State(pancakes[i], i));
        }

        // Main greedy loop
        ArrayList<Integer> order = new ArrayList<>();
        State curr;
        int stackLoc = 0;
        int addLoc = Math.min(K+1, N);
        int numLeftToSkip = K;
        while (!pq.isEmpty()) {
            curr = pq.poll();

            // If later in stack
            if (curr.i >= stackLoc) {
                // Pop off as many elements from pancakes as needed to get this one first
                int needToPop = curr.i - stackLoc;
                stackLoc += needToPop + 1;
                numLeftToSkip -= needToPop;
                order.add(curr.n);

                // Add next element to pq (if there are any left)
                if (addLoc < N) {
                    pq.add(new State(pancakes[addLoc], addLoc));
                    addLoc++;
                }
            } else {
                // Just add it
                order.add(curr.n);
            }
        }

        for (int i = 0; i < order.size() - 1; i++) {
            System.out.print(order.get(i) + " ");
        }
        System.out.println(order.get(order.size() - 1));
    }

    public static void main(String[] args) throws IOException {
        new pancakes();
    }

    static class State {
        int n, i;
        State(int n, int i) {
            this.n = n;
            this.i = i;
        }
    }
}
