// Solves ST 1-3
public class seats13 {
    int N;
    int[] R, C;
    SegmentTree segX, segY;

    void give_initial_chart(int H, int W, int[] R, int[] C) {
        N = H * W;
        this.R = R;
        this.C = C;
        segX = new SegmentTree(N, C);
        segY = new SegmentTree(N, R);
    }

    int swap_seats(int a, int b) {
        segX.update(a, C[b]);
        segX.update(b, C[a]);
        segY.update(a, R[b]);
        segY.update(b, R[a]);
        int temp = R[a];
        R[a] = R[b];
        R[b] = temp;
        temp = C[a];
        C[a] = C[b];
        C[b] = temp;

        // Calculate new beauty
        int minX = C[0], maxX = C[0], minY = R[0], maxY = R[0], beauty = 1;
        int lastI = 0;
        for (int i = 1; i < N;) {
            if (i - lastI <= 5) {
                // Don't waste time doing a segment tree query
                for (int j = lastI + 1; j <= i; j++) {
                    minX = Math.min(C[j], minX);
                    maxX = Math.max(C[j], maxX);
                    minY = Math.min(R[j], minY);
                    maxY = Math.max(R[j], maxY);
                }
            } else {
                // Segment tree queries
                minX = segX.queryMin(0, i);
                maxX = segX.queryMax(0, i);
                minY = segY.queryMin(0, i);
                maxY = segY.queryMax(0, i);
            }
            lastI = i;

            // System.out.println("i = " + i);
            // System.out.println(minX + " " + maxX + " " + minY + " " + maxY);
            int currArea = (maxX - minX + 1) * (maxY - minY + 1);
            if (currArea == i + 1) {
                beauty++;
                i++;
            } else {
                // To save time, jump directly to next possible rectangle
                i = currArea - 1;
            }
        }
        return beauty;
    }
}

// Min / max segment tree
class SegmentTree {
    final int INF = 987654321;
    int size;
    int[] min, max;

    SegmentTree(int size, int[] initArr) {
        this.size = size;
        min = new int[size * 4 + 1];
        max = new int[size * 4 + 1];
        this.initArr = initArr;
        initTree(1, 0, size - 1);
    }

    int queryMin(int l, int r) {
        return queryMin(1, 0, size - 1, l, r);
    }

    int queryMin(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return INF;
        else if (lb >= l && ub <= r) return min[n];
        else return Math.min(queryMin(n*2, lb, (lb+ub)/2, l, r), queryMin(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    int queryMax(int l, int r) {
        return queryMax(1, 0, size - 1, l, r);
    }

    int queryMax(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return 0;
        else if (lb >= l && ub <= r) return max[n];
        else return Math.max(queryMax(n*2, lb, (lb+ub)/2, l, r), queryMax(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    void update(int i, int v) {
        update(1, 0, size - 1, i, v);
    }

    void update(int n, int lb, int ub, int i, int v) {
        if (lb == ub) {
            min[n] = v;
            max[n] = v;
            return;
        } else if ((lb+ub)/2 < i) {
            update(n*2+1, (lb+ub)/2+1, ub, i, v);
        } else {
            update(n*2, lb, (lb+ub)/2, i, v);
        }
        min[n] = Math.min(min[n*2], min[n*2+1]);
        max[n] = Math.max(max[n*2], max[n*2+1]);
    }

    int[] initArr;
    void initTree(int n, int lb, int ub) {
        if (lb == ub) {
            min[n] = initArr[lb];
            max[n] = initArr[lb];
        } else {
            initTree(n*2, lb, (lb+ub)/2);
            initTree(n*2+1, (lb+ub)/2+1, ub);
            min[n] = Math.min(min[n*2], min[n*2+1]);
            max[n] = Math.max(max[n*2], max[n*2+1]);
        }
    }
}