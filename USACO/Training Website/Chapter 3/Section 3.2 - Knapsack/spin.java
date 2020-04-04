/*
ID: sunnyky1
LANG: JAVA
TASK: spin

Solution: This is an ad-hoc problem; you have to simulate at max up to 360 seconds, since after that the wheels will
cycle. The max # of wedges on each wheel is 5, so checking all possible sets of wedges is only 5^5, which is completely
fine. So, just code a naive solution.

Runtime: O(360 * 5^5)
*/

import java.util.*;
import java.io.*;

public class spin {
    int[] wheelSpeed;
    // arr[i][j] = Wheel i, wedge j
    int[][] wedgeStart, wedgeEnd;

    spin() throws IOException {
        BufferedReader fin = new BufferedReader(new FileReader("spin.in"));
        StringTokenizer st;
        wheelSpeed = new int[5];
        wedgeStart = new int[5][];
        wedgeEnd = new int[5][];
        for (int i = 0; i < 5; i++) {
            st = new StringTokenizer(fin.readLine());
            wheelSpeed[i] = Integer.parseInt(st.nextToken());
            int W = Integer.parseInt(st.nextToken());
            wedgeStart[i] = new int[W];
            wedgeEnd[i] = new int[W];
            int a, b;
            for (int j = 0; j < W; j++) {
                a = Integer.parseInt(st.nextToken());
                b = Integer.parseInt(st.nextToken());
                wedgeStart[i][j] = a;
                wedgeEnd[i][j] = (a + b) % 360;
            }
        }
        fin.close();

        // Simulate all 360 seconds
        int answer = -1;
        for (int i = 0; i < 360; i++) {
            if (checkWheels(0, new int[5])) {
                answer = i;
                break;
            } else {
                // Move all the wedges
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < wedgeStart[j].length; k++) {
                        wedgeStart[j][k] = (wedgeStart[j][k] + wheelSpeed[j]) % 360;
                        wedgeEnd[j][k] = (wedgeEnd[j][k] + wheelSpeed[j]) % 360;
                    }
                }
            }
        }

        PrintWriter fout = new PrintWriter("spin.out");
        if (answer == -1) fout.println("none");
        else fout.println(answer);
        fout.close();
    }

    boolean checkWheels(int wheelI, int[] prevWedges) {
        if (wheelI == 5) return true;  // All wheels satisfied
        else {
            // Try all wedges
            outerLoop:
            for (int i = 0; i < wedgeStart[wheelI].length; i++) {
                // Check intersection with all previous wedges
                for (int j = 0; j < wheelI; j++) {
                    if (!checkIntersect(wedgeStart[j][prevWedges[j]], wedgeEnd[j][prevWedges[j]], wedgeStart[wheelI][i], wedgeEnd[wheelI][i])) {
                        continue outerLoop;
                    }
                }

                // This works; continue
                prevWedges[wheelI] = i;
                if (checkWheels(wheelI + 1, prevWedges)) return true;
            }
        }
        // No wedges worked
        return false;
    }

    boolean checkIntersect(int aStart, int aEnd, int bStart, int bEnd) {
        if (aEnd < aStart && bEnd < bStart) {
            // Both flipped; easy fix
            return checkIntersectSimple(aStart, aEnd + 360, bStart, bEnd + 360);
        } else if (aEnd < aStart) {
            // Only a flipped; try both variations of a
            return checkIntersectSimple(aStart - 360, aEnd, bStart, bEnd) ||
                   checkIntersectSimple(aStart, aEnd + 360, bStart, bEnd);
        } else if (bEnd < bStart) {
            // Only b flipped; try both variations of b
            return checkIntersectSimple(aStart, aEnd, bStart - 360, bEnd) ||
                    checkIntersectSimple(aStart, aEnd, bStart, bEnd + 360);
        } else {
            // Nothing flipped
            return checkIntersectSimple(aStart, aEnd, bStart, bEnd);
        }
    }

    boolean checkIntersectSimple(int a1, int a2, int b1, int b2) {
        return a2 >= b1 && a1 <= b2;
    }

    public static void main(String[] args) throws IOException {
        new spin();
    }
}
