import java.util.*;

public class dollno {
    final int MAXS = 500000, NULL = 99999999;
    int M, N, currS = 0;
    int[] C, X, Y;
    ArrayList<Integer> exits;

    void create_circuit(int M, int[] A) {
        this.M = M;
        N = A.length;
        exits = new ArrayList<>();
        for (int i = 0; i < N; i++) {
            exits.add(A[i]);
        }
        // Add final exit
        exits.add(0);

        C = new int[M + 1];
        Arrays.fill(C, -1);
        X = new int[MAXS];
        Y = new int[MAXS];
        int numExits = exits.size();
        int[] currExits = new int[numExits];
        for (int j = 0; j < numExits; j++) currExits[j] = exits.get(j);
        // System.out.println(numExits);
        // System.out.println(Arrays.toString(currExits));
        genSwitches(currExits, NULL);

        int[] actualX = new int[currS];
        for (int i = 0; i < currS; i++) actualX[i] = X[i+1];
        int[] actualY = new int[currS];
        for (int i = 0; i < currS; i++) actualY[i] = Y[i+1];
        System.out.println(Arrays.toString(C));
        System.out.println(Arrays.toString(actualX));
        System.out.println(Arrays.toString(actualY));
        doll_lib.answer(C, actualX, actualY);
    }

    int genSwitches(int[] currExits, int oddJumpTo) {
        System.out.println("currExits = " + Arrays.toString(currExits) + ", oddJumpTo = " + oddJumpTo);
        int numExits = currExits.length;
        if (numExits == 1) {
            // Base case
            if (oddJumpTo != NULL) {
                // Odd jump should be first, followed by
                return oddJumpTo;
            }
            else return currExits[0];
        } else if (numExits == 0) {
            // Doesn't matter
            if (oddJumpTo != NULL) return oddJumpTo;
            else return M;
        }

        // Split into odd and even indexes with a new switch
        currS++;
        int switchI = currS;
        int xNum = (numExits + 1) / 2;
        int yNum = numExits / 2;

        // If numExits is odd, this switch must be switched back to X
        if (numExits % 2 == 1 && oddJumpTo == NULL) {
            oddJumpTo = -switchI;
        }

        int[] xExits = new int[xNum];
        int[] yExits = new int[yNum];
        int xi = 0, yi = 0;
        for (int i = 0; i < numExits; i++) {
            if (i % 2 == 0) xExits[xi++] = currExits[i];
            else yExits[yi++] = currExits[i];
        }

        if (oddJumpTo != NULL && xNum % 2 == 1) {
            // Odd place must jump back to first odd switch
            X[switchI] = genSwitches(xExits, oddJumpTo);
            Y[switchI] = genSwitches(yExits, NULL);
        } else if (oddJumpTo != NULL && yNum % 2 == 1) {
            X[switchI] = genSwitches(xExits, NULL);
            Y[switchI] = genSwitches(yExits, oddJumpTo);
        } else {
            X[switchI] = genSwitches(xExits, NULL);
            Y[switchI] = genSwitches(yExits, NULL);
        }
        return -switchI;
    }
}
