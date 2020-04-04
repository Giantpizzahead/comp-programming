import java.io.*;
import java.util.*;

public class fairphoto2 {
    final int INF = 1000007;
    int N, K;
    int[][] relZero;
    Pair[] cows;
    DeltaTreeSet[] currStates;

    fairphoto2(BufferedReader fin, PrintWriter fout) throws IOException {
        StringTokenizer st = new StringTokenizer(fin.readLine());
        N = Integer.parseInt(st.nextToken());
        K = Integer.parseInt(st.nextToken());
        cows = new Pair[N];
        int x, id;
        for (int i = 0; i < N; i++) {
            st = new StringTokenizer(fin.readLine());
            x = Integer.parseInt(st.nextToken());
            id = Integer.parseInt(st.nextToken()) - 1;
            cows[i] = new Pair(x, id);
        }
        Arrays.sort(cows, new Comparator<Pair>() {
            @Override
            public int compare(Pair o1, Pair o2) {
                return o1.x - o2.x;
            }
        });

        currStates = new DeltaTreeSet[9];

        int answer = -1, prevBreed, stopPoint;
        HashSet<Integer> currBreeds = new HashSet<>(8);
        // Base treeset
        currBreeds.add(cows[0].id);
        currStates[1] = new DeltaTreeSet(1, cows[0].id, currBreeds, 0);
        currBreeds.clear();
        for (int i = 0; i < N; i++) {
            // System.out.println("i = " + i);
            // Update last seen location
            stopPoint = -1;
            for (int j = 1; j < 9; j++) {
                if (currStates[j] == null || currStates[j].lastSeen == cows[i].id) {
                    // Move treesets up all the way to here
                    stopPoint = j;
                    break;
                }
            }

            // Now, move the treesets up
            prevBreed = cows[i].id;
            currBreeds.clear();
            currBreeds.add(prevBreed);

            if (stopPoint != 1) {
                DeltaTreeSet prevNewTS = new DeltaTreeSet(1, prevBreed, currBreeds, i);
                prevBreed = currStates[1].lastSeen;
                for (int j = 2; j < stopPoint; j++) {
                    currBreeds.add(prevBreed);
                    DeltaTreeSet newTS = new DeltaTreeSet(j, prevBreed, currBreeds, currStates[j-1].startI);
                    prevBreed = currStates[j].lastSeen;
                    // Transition old states into this TreeSet
                    currStates[j-1].transitionInto(newTS);
                    currStates[j-1] = prevNewTS;
                    prevNewTS = newTS;
                }
                // Transition final old states into remaining TreeSet
                if (currStates[stopPoint] == null) {
                    // New treeset!
                    currBreeds.add(prevBreed);
                    currStates[stopPoint] = new DeltaTreeSet(stopPoint, prevBreed, currBreeds, currStates[stopPoint-1].startI);
                } else currStates[stopPoint].lastSeen = prevBreed;
                currStates[stopPoint-1].transitionInto(currStates[stopPoint]);
                currStates[stopPoint-1] = prevNewTS;
            }

            // Add new state starting at i
            currStates[1].startState(i);

            // Update zero location for all treesets
            for (int j = 1; j < 9; j++) {
                if (currStates[j] == null) break;
                else currStates[j].addCow(cows[i].id);
            }

            // Query for all zeroes in all treesets
            for (int j = K; j < 9; j++) {
                if (currStates[j] == null) break;
                else if (cows[i].x - cows[currStates[j].startI].x > answer) {
                    answer = Math.max(currStates[j].query(i), answer);
                    // System.out.println("Query " + j + ": " + currStates[j].query(i));
                }
            }

            // System.out.println(Arrays.toString(currStates));
        }

        fout.println(answer);
    }

    class DeltaTreeSet {
        int numBreeds, lastSeen, rootBreed, rootZero, startI;
        int[] relZero, breedToI, iToBreed;
        TreeSet<State> ts;

        DeltaTreeSet(int numBreeds, int rootBreed, HashSet<Integer> currBreeds, int startI) {
            // System.out.println("numBreeds = " + numBreeds + ", rootBreed = " + rootBreed + ", currBreeds = " + currBreeds);
            this.numBreeds = numBreeds;
            this.lastSeen = rootBreed;
            this.rootBreed = rootBreed;
            this.startI = startI;
            rootZero = 0;
            relZero = new int[numBreeds - 1];
            ts = new TreeSet<>();

            // Generate breedToI and iToBreed
            breedToI = new int[8];
            iToBreed = new int[numBreeds - 1];
            Arrays.fill(breedToI, -1);
            int i = 0;
            for (int n : currBreeds) {
                if (n != rootBreed) {
                    iToBreed[i] = n;
                    breedToI[n] = i++;
                }
            }
        }

        void transitionInto(DeltaTreeSet newDTS) {
            for (State state : ts) {
                int actualRootCount = state.rootCount - rootZero;
                // System.out.println(Arrays.toString(rawCounts));

                // Figure out new deltas
                int[] newRelBreeds = new int[numBreeds];
                int rootDelta;
                if (newDTS.rootBreed == rootBreed) rootDelta = actualRootCount;
                else if (breedToI[newDTS.rootBreed] == -1) rootDelta = 0;
                else rootDelta = actualRootCount + state.relBreeds[breedToI[newDTS.rootBreed]] - relZero[breedToI[newDTS.rootBreed]];
                for (int i = 0; i < numBreeds; i++) {
                    int targeti = breedToI[newDTS.iToBreed[i]];
                    if (newDTS.iToBreed[i] == rootBreed) newRelBreeds[i] = actualRootCount + newDTS.relZero[i] - rootDelta;
                    else if (targeti == -1) newRelBreeds[i] = newDTS.relZero[i] - rootDelta;
                    else newRelBreeds[i] = actualRootCount + state.relBreeds[targeti] - relZero[targeti] + newDTS.relZero[i] - rootDelta;
                }
                newDTS.ts.add(new State(newRelBreeds, rootDelta + newDTS.rootZero, state.i));
            }
        }

        void addCow(int breed) {
            if (breed == rootBreed) {
                for (int i = 0; i < numBreeds - 1; i++) relZero[i]++;
                rootZero--;
            } else relZero[breedToI[breed]]--;
        }

        void startState(int i) {
            int[] newBreeds = new int[numBreeds - 1];
            for (int j = 0; j < numBreeds - 1; j++) newBreeds[j] = relZero[j];
            ts.add(new State(newBreeds, rootZero, i));
        }

        int query(int currI) {
            State state = ts.ceiling(new State(relZero, -INF, -1));
            if (state == null) return -1;
            boolean isZeroState = true;
            for (int i = 0; i < numBreeds - 1; i++) {
                if (state.relBreeds[i] != relZero[i]) {
                    isZeroState = false;
                    break;
                }
            }
            return isZeroState ? (cows[currI].x - cows[state.i].x) : -1;
        }

        @Override
        public String toString() {
            return "DeltaTreeSet{" +
                    "numBreeds=" + numBreeds +
                    ", lastSeen=" + lastSeen +
                    ", rootBreed=" + rootBreed +
                    ", rootZero=" + rootZero +
                    ", relZero=" + Arrays.toString(relZero) +
                    ", breedToI=" + Arrays.toString(breedToI) +
                    ", iToBreed=" + Arrays.toString(iToBreed) +
                    ", ts=" + ts +
                    '}';
        }
    }

    class State implements Comparable<State> {
        int[] relBreeds;
        int rootCount, i;
        State(int[] relBreeds, int rootCount, int i) {
            this.relBreeds = relBreeds;
            this.rootCount = rootCount;
            this.i = i;
        }

        @Override
        public String toString() {
            return "(" + Arrays.toString(relBreeds) + ", " + rootCount + ", " + i + ")";
        }

        @Override
        public int compareTo(State o) {
            // Sort in increasing lexicographical order
            for (int i = 0; i < relBreeds.length; i++) {
                if (relBreeds[i] != o.relBreeds[i]) return relBreeds[i] - o.relBreeds[i];
            }
            if (i != o.i) return i - o.i;
            else if (rootCount != o.rootCount) return rootCount - o.rootCount;
            return 0;
        }
    }

    class Pair {
        int x, id;
        Pair(int x, int id) {
            this.x = x;
            this.id = id;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("fairphoto.in"));
        PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("fairphoto.out")));
        new fairphoto2(fin, fout);
        fin.close();
        fout.close();
    }
}
