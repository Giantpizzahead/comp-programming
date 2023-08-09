/*
IOI 2022 Day 1: Fish
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

vector<vector<ll>> preColSum;

ll getColSum(int x, int i, int j) {
    // Both column and row are one-indexed
    i--, j--;
    return preColSum[x][j+1] - preColSum[x][i];
}

vector<vector<ll>> dpInc, dpDec;

void setMax(ll& a, ll b) {
    a = max(b, a);
}

ll max_weights(int N, int M, vector<int> X, vector<int> Y, vector<int> W) {
    // Generate prefix sum
    preColSum = vector<vector<ll>>(N+1, vector<ll>(N+1, 0));
    for (int i = 0; i < M; i++) preColSum[X[i]+1][Y[i]+1] = W[i];
    for (int x = 1; x <= N; x++) {
        for (int i = 1; i <= N; i++) {
            preColSum[x][i] += preColSum[x][i-1];
        }
    }

    // Do the DP
    ll INF = 1e18;
    ll ans = 0;
    dpInc = vector<vector<ll>>(N+1, vector<ll>(N+1, -INF));
    dpDec = vector<vector<ll>>(N+1, vector<ll>(N+1, -INF));
    dpInc[0][0] = 0;
    for (int x = 0; x < N; x++) {
        for (int p = 0; p <= N; p++) {
            // Handle dpInc
            if (dpInc[x][p] != -INF) {
                // Try all heights for the next pier
                for (int q = p; q <= N; q++) {
                    setMax(dpInc[x+1][q], dpInc[x][p] + getColSum(x, p+1, q));
                }
                // Try switching to decreasing
                setMax(dpDec[x+1][N], dpInc[x][p] + getColSum(x, p+1, N));
            }

            // Handle dpDec
            if (dpDec[x][p] != INF) {
                // Try all heights for the next pier
                for (int q = p; q >= 0; q--) {
                    setMax(dpDec[x+1][q], dpDec[x][p] + getColSum(x+1, q+1, p));
                }
                // Try switching to increasing (without adding anything!)
                setMax(dpInc[x+1][0], dpDec[x][p]);
            }
        }
    }
    for (int p = 0; p <= N; p++) {
        setMax(ans, dpInc[N][p]);
        setMax(ans, dpDec[N][p]);
    }
    return ans;
}






















void sampleCase() {
    int N = 5, M = 4;
    vector<int> X({0, 1, 4, 3}), Y({2, 1, 4, 3}), W({5, 2, 1, 3});
    int ans = 8;
    int result = max_weights(N, M, X, Y, W);
    if (ans == result) {
        cout << "Sample case passed!" << endl;
    } else {
        cout << "Wrong answer: Expected " << ans << ", got " << result << endl;
        exit(-1);
    }
}

void validationCase() {
    int N = 7, M = 9;
    vector<int> X({0, 0, 1, 3, 3, 4, 5, 5, 6});
    vector<int> Y({1, 4, 2, 3, 5, 3, 1, 3, 4});
    vector<int> W({3, 13, 8, 4, 10, 5, 20, 4, 15});
    int ans = 55;
    int result = max_weights(N, M, X, Y, W);
    if (ans == result) {
        cout << "Validation case passed!" << endl;
    } else {
        cout << "Wrong answer: Expected " << ans << ", got " << result << endl;
        exit(-1);
    }
}

int main() {
    sampleCase();
    validationCase();
    return 0;
}
