// Solves ST 4
public class seats4 {
    int N, currBeauty;
    boolean[] isBeautiful;
    int[] R, C, minX, minY, maxX, maxY;

    void give_initial_chart(int H, int W, int[] R, int[] C) {
        N = H * W;
        this.R = R;
        this.C = C;
        isBeautiful = new boolean[N];
        minX = new int[N];
        minY = new int[N];
        maxX = new int[N];
        maxY = new int[N];

        // Initial beauty calc
        int cMinX = C[0], cMaxX = C[0], cMinY = R[0], cMaxY = R[0];
        minX[0] = C[0];
        maxX[0] = C[0];
        minY[0] = R[0];
        maxY[0] = R[0];
        isBeautiful[0] = true;
        currBeauty = 1;
        for (int i = 1; i < N; i++) {
            cMinX = Math.min(C[i], cMinX);
            cMaxX = Math.max(C[i], cMaxX);
            cMinY = Math.min(R[i], cMinY);
            cMaxY = Math.max(R[i], cMaxY);
            minX[i] = cMinX;
            maxX[i] = cMaxX;
            minY[i] = cMinY;
            maxY[i] = cMaxY;
            int currArea = (cMaxX - cMinX + 1) * (cMaxY - cMinY + 1);
            if (currArea == i + 1) {
                currBeauty++;
                isBeautiful[i] = true;
            }
        }
    }

    int swap_seats(int a, int b) {
        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }

        int temp = C[a];
        C[a] = C[b];
        C[b] = temp;
        temp = R[a];
        R[a] = R[b];
        R[b] = temp;

        // Only need to update beauty counts from [a, b)
        int cMinX, cMaxX, cMinY, cMaxY;
        if (a == 0) {
            cMinX = C[0];
            cMaxX = C[0];
            cMinY = R[0];
            cMaxY = R[0];
            minX[0] = C[0];
            maxX[0] = C[0];
            minY[0] = R[0];
            maxY[0] = R[0];
            a = 1;
        } else {
            cMinX = minX[a-1];
            cMaxX = maxX[a-1];
            cMinY = minY[a-1];
            cMaxY = maxY[a-1];
        }

        for (int i = a; i < b; i++) {
            cMinX = Math.min(C[i], cMinX);
            cMaxX = Math.max(C[i], cMaxX);
            cMinY = Math.min(R[i], cMinY);
            cMaxY = Math.max(R[i], cMaxY);
            minX[i] = cMinX;
            maxX[i] = cMaxX;
            minY[i] = cMinY;
            maxY[i] = cMaxY;
            int currArea = (cMaxX - cMinX + 1) * (cMaxY - cMinY + 1);
            if (currArea == i + 1) {
                if (!isBeautiful[i]) {
                    currBeauty++;
                    isBeautiful[i] = true;
                }
            } else {
                if (isBeautiful[i]) {
                    currBeauty--;
                    isBeautiful[i] = false;
                }
            }
        }
        return currBeauty;
    }
}