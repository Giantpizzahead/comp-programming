import java.util.*;

public class doll {
    final int INF = 987654321;
    int M, N, pow2, maxLoopback, currSwitch = -1;
    int[] exits, C, X, Y;
    boolean[] isY;

    void create_circuit(int M, int[] A) {
        N = A.length;
        if (N == 1) {
            // Special case
            C = new int[M + 1];
            C[0] = A[0];
            C[A[0]] = 0;
            X = new int[0];
            Y = new int[0];
            doll_lib.answer(C, X, Y);
            return;
        }
        this.M = M;
        exits = new int[N];
        for (int i = 0; i < N-1; i++) exits[i] = A[i+1];
        exits[N-1] = 0;

        C = new int[M + 1];
        Arrays.fill(C, -1);
        C[0] = A[0];
        X = new int[N * 2];
        Y = new int[N * 2];
        isY = new boolean[N * 2];

        // Figure out how big the tree needs to be
        pow2 = 1;
        while (pow2 < N) pow2 *= 2;
        maxLoopback = pow2 - N;
        genSwitches(1, pow2);

        // Now, generate the exits
        int exit = 0;
        while (exit != N) {
            if (genExit(-1, exits[exit])) exit++;
        }
        // System.out.println(Arrays.toString(X));
        // System.out.println(Arrays.toString(Y));

        int numSwitches = -currSwitch;
        int[] actualX = new int[numSwitches], actualY = new int[numSwitches];
        for (int i = 0; i < numSwitches; i++) {
            actualX[i] = X[i];
            actualY[i] = Y[i];
        }

        doll_lib.answer(C, actualX, actualY);
    }

    boolean genExit(int negID, int exit) {
        int posID = -negID - 1;
        if (isY[posID]) {
            isY[posID] = !isY[posID];
            if (Y[posID] == -1) return false;
            else if (Y[posID] == INF) {
                Y[posID] = exit;
                return true;
            }
            return genExit(Y[posID], exit);
        } else {
            isY[posID] = !isY[posID];
            if (X[posID] == -1) return false;
            else if (X[posID] == INF) {
                X[posID] = exit;
                return true;
            }
            return genExit(X[posID], exit);
        }
    }

    int genSwitches(int l, int r) {
        if (r <= maxLoopback) {
            // This switch is useless
            return -1;
        } else if (l == r) {
            // Will be assigned later
            return INF;
        } else {
            // This switch is useful!
            int negID = currSwitch--;
            int posID = -negID - 1;
            int mid = (l + r) / 2;
            X[posID] = genSwitches(l, mid);
            Y[posID] = genSwitches(mid+1, r);
            return negID;
        }
    }
}
