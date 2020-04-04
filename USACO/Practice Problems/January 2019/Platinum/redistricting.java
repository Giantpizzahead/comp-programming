/*
Solution: Store previous solutions in a TreeSet, along with the minimum # of districts in any state in
the TreeSet. Split this TreeSet into two: One for x districts, and one for x+1 districts. Sort these
in order of increasing zeroLoc.

State will be (index, zeroLoc). Track how many districts each state needs in 2 sep variables.
When iterating:
If there is a state in the x district TreeSet with zeroLoc strictly less than current sum, add a new
state into the x district TreeSet with (currIndex, currSum) to rep. splitting districts here.
If no state is found, add a new state into the x+1 district TreeSet with (currIndex, currSum) to rep.
splitting a district to cut your losses.
After each iteration, remove any states in either TreeSet with index <= currIndex - K (use a separate
queue). If the x district TreeSet is now empty, move the x+1 to the x TreeSet, and increment x.

If there are any ties when inserting, choose the one with the greatest index.
*/

import java.util.*;
import java.io.*;

public class redistricting {
    int N, K;
    boolean[] isHolstein;

    redistricting() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("redistricting.in"));
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        isHolstein = new boolean[N];
        String line = fin.readLine();
        for (int i = 0; i < N; i++) {
            isHolstein[i] = line.charAt(i) == 'H';
        }
        fin.close();

        int answer = solve();
        PrintWriter fout = new PrintWriter("redistricting.out");
        fout.println(answer);
        fout.close();
    }

    int solve() {
        TreeSet<State> currStates = new TreeSet<>(Comparator.comparingInt(x -> x.zeroLoc));
        currStates.add(new State(0, 0));
        TreeSet<State> nextStates = new TreeSet<>(Comparator.comparingInt(x -> x.zeroLoc));
        int currDistricts = 0;
        int currSum = 0;
        State newState;
        Queue<State> toRemove = new LinkedList<>();
        toRemove.add(new State(0, 0));

        for (int i = 0; i < N; i++) {
            /*
            System.out.println("Iteration " + i);
            System.out.println(currStates);
            System.out.println(nextStates);
             */
            currSum += isHolstein[i] ? 1 : -1;
            newState = new State(i+1, currSum);

            // Check for any allowed district splits
            if (currStates.lower(newState) != null) {
                // New state with same # of districts can be created; add it
                currStates.remove(newState);
                currStates.add(newState);
            } else {
                // Must add a new state with 1 extra district
                nextStates.remove(newState);
                nextStates.add(newState);
            }

            // Remove any outdated states
            while (!toRemove.isEmpty() && toRemove.peek().index <= i - K + 1) {
                // If this state has not been updated, then remove it
                State outdatedState = toRemove.poll();
                // System.out.println("Removed " + outdatedState);
                State checkState = currStates.ceiling(outdatedState);
                if (checkState != null && checkState.zeroLoc == outdatedState.zeroLoc && checkState.index == outdatedState.index) {
                    currStates.remove(checkState);
                }
                checkState = nextStates.ceiling(outdatedState);
                if (checkState != null && checkState.zeroLoc == outdatedState.zeroLoc && checkState.index == outdatedState.index) {
                    nextStates.remove(checkState);
                }
            }

            if (currStates.isEmpty()) {
                // # districts must be moved up
                currStates = nextStates;
                nextStates = new TreeSet<>(Comparator.comparingInt(x -> x.zeroLoc));
                currDistricts++;
                // System.out.println("currDistricts++");
            }

            toRemove.add(newState);
        }

        // Find answer
        do {
            newState = toRemove.poll();
        } while (newState.index != N);

        State checkState = currStates.ceiling(newState);
        if (checkState != null && checkState.zeroLoc == newState.zeroLoc && checkState.index == newState.index) {
            return currDistricts;
        } else return currDistricts + 1;
    }

    public static void main(String[] args) throws IOException {
        new redistricting();
    }

    static class State {
        int index, zeroLoc;
        State(int index, int zeroLoc) {
            this.index = index;
            this.zeroLoc = zeroLoc;
        }
        @Override
        public String toString() {
            return "(" + index + ", " + zeroLoc + ")";
        }
    }
}
