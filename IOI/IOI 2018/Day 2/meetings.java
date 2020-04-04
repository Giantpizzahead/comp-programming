public class meetings {
    int N, Q;
    int[] H;
    long[][] leftCost, rightCost;

    long[] minimum_costs(int[] H, int[] L, int[] R) {
        N = H.length;
        Q = L.length;
        this.H = H;
        long[] ans = new long[Q];
        leftCost = new long[N][N];
        rightCost = new long[N][N];
        for (int meet = 0; meet < N; meet++) {
            int currMax = 0;
            long currCost = 0;
            for (int l = meet; l >= 0; l--) {
                currMax = Math.max(H[l], currMax);
                currCost += currMax;
                leftCost[meet][l] = currCost;
            }
            currMax = 0;
            currCost = 0;
            for (int r = meet; r < N; r++) {
                currMax = Math.max(H[r], currMax);
                currCost += currMax;
                rightCost[meet][r] = currCost;
            }
        }
        for (int i = 0; i < Q; i++) {
            ans[i] = solve(L[i], R[i]);
        }
        return ans;
    }

    long solve(int l, int r) {
        // Find best
        long best = 987654323456789L;
        for (int i = l; i <= r; i++) {
            long cost = rightCost[i][r] + leftCost[i][l] - H[i];
            best = Math.min(best, cost);
        }
        return best;
    }
}
