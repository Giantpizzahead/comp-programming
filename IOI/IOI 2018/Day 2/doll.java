import java.util.ArrayList;

public class doll {
    final int MAXS = 500000;
    int M, N, currS = 0;
    int[] C, X, Y;
    ArrayList<Integer>[] exits;
 
    void create_circuit(int M, int[] A) {
        this.M = M;
        N = A.length;
        exits = new ArrayList[M + 1];
        for (int i = 1; i <= M; i++) exits[i] = new ArrayList<>(2);
        for (int i = 1; i < N; i++) {
            exits[A[i-1]].add(A[i]);
        }
        exits[A[N-1]].add(0);

        C = new int[M + 1];
        X = new int[MAXS];
        Y = new int[MAXS];
        C[0] = A[0];
        for (int i = 1; i <= M; i++) {
            // Add exits as needed to make all ending states X (numExits should be a power of 2)
            int numExits = exits[i].size();
            if (numExits > 2) {
                int pow2 = 1;
                while (pow2 < numExits) pow2 *= 2;
                // Remove last one
                int lastExit = exits[i].remove(exits[i].size() - 1);
                numExits--;
                while (pow2 - 1 > numExits) {
                    // Loop back to starting switch
                    exits[i].add(-currS - 1);
                    numExits++;
                }
                // Add it back
                exits[i].add(lastExit);
                numExits++;
            }
            // System.out.println(numExits);
            int[] currExits = new int[numExits];
            for (int j = 0; j < numExits; j++) currExits[j] = exits[i].get(j);
            C[i] = genSwitches(currExits);
        }

        int[] actualX = new int[currS];
        for (int i = 0; i < currS; i++) actualX[i] = X[i+1];
        int[] actualY = new int[currS];
        for (int i = 0; i < currS; i++) actualY[i] = Y[i+1];
        // System.out.println(Arrays.toString(C));
        // System.out.println(Arrays.toString(actualX));
        // System.out.println(Arrays.toString(actualY));
        doll_lib.answer(C, actualX, actualY);
    }

    int genSwitches(int[] currExits) {
        // System.out.println("currExits = " + Arrays.toString(currExits));
        int numExits = currExits.length;
        if (numExits == 1) {
            // Base case
            return currExits[0];
        } else if (numExits == 0) {
            // Doesn't matter
            return M;
        }
        // Split into odd and even indexes with a new switch
        currS++;
        int switchI = currS;
        int[] xExits = new int[(numExits + 1) / 2];
        int[] yExits = new int[numExits / 2];
        int xi = 0, yi = 0;
        for (int i = 0; i < numExits; i++) {
            if (i % 2 == 0) xExits[xi++] = currExits[i];
            else yExits[yi++] = currExits[i];
        }
        X[switchI] = genSwitches(xExits);
        Y[switchI] = genSwitches(yExits);
        return -switchI;
    }
}
