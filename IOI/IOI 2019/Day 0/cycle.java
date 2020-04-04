 /*
Solution: Modified binary search. Think of your starting room as room 1, and search from there.
Runtime: O(log(N) calls to jump)
*/

import java.util.*;
import java.io.*;

public class cycle {
    int N, curr = 0;

    void escape(int N) {
        this.N = N;
        // Initial search
        boolean initial = grader.jump(0);

        int low, high, mid = N/2;
        if (initial) {
            low = 0;
            high = mid;
        } else {
            low = mid + 1;
            high = N - 1;
        }
        while (low < high) {
            mid = (low+high)/2;
            // We want to be N/2 rooms behind mid
            int targetLoc = mid - N/2;
            if (targetLoc < 0) targetLoc += N;
            int stepsToMove = getStepsTo(targetLoc);
            curr = targetLoc;
            boolean result = grader.jump(stepsToMove);
            if (result) {
                high = mid;
            } else {
                low = mid + 1;
            }
            // System.out.println(curr);
        }

        // We know where it is; just jump to it
        grader.jump(getStepsTo(low));
    }

    int getStepsTo(int target) {
        int stepsToMove = target - curr;
        if (stepsToMove < 0) stepsToMove += N;
        return stepsToMove;
    }
}
