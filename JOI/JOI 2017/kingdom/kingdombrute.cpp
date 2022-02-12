/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int INF = 1e9+7;
const int MAXN = 2005;

int H, W, minV = INF, maxV = -INF;
int A[MAXN][MAXN], newA[MAXN][MAXN];

int bestAns;
void getAns(int i = 0, int j = W-1, int maxL = -INF, int minR = INF) {
    if (i == H) {
        // Check result
        bestAns = min(max(maxL - minV, maxV - minR), bestAns);
        return;
    }
    // Brute force the boundary
    for (; j >= -1; j--) {
        int newL = maxL, newR = minR;
        rep(k, 0, j+1) newL = max(A[i][k], newL);
        rep(k, j+1, W) newR = min(A[i][k], newR);
        getAns(i+1, j, newL, newR);
    }
}

void solve() {
    cin >> H >> W;
    rep(i, 0, H) rep(j, 0, W) {
        cin >> A[i][j];
        minV = min(A[i][j], minV);
        maxV = max(A[i][j], maxV);
    }

    // Try all rotations and flips
    int ans = maxV - minV;
    rep(d, 0, 8) {
        // debug << endl;
        // rep(i, 0, H) rep(j, 0, W) debug << A[i][j] << " \n"[j==W-1];
        bestAns = INF;
        getAns();
        // cout << bestAns << '\n';
        ans = min(bestAns, ans);
        if (d != 3) {
            // Rotate board
            // (i, j) -> (j, [new W]-1-i)
            rep(i, 0, H) rep(j, 0, W) newA[j][H-1-i] = A[i][j];
            swap(H, W);
            rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
        } else {
            // Flip board
            // (i, j) -> (H-1-i, j)
            rep(i, 0, H) rep(j, 0, W) newA[H-1-i][j] = A[i][j];
            rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}