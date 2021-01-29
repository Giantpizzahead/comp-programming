#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int N = 8;
int K;

double robots[N*N][N][N];
double dp1[N][N], dp2[N][N];

void doDP(int si, int sj) {
    rep(i, 0, N) {
        rep(j, 0, N) {
            dp1[i][j] = 0;
            dp2[i][j] = 0;
        }
    }
    dp1[si][sj] = 1;
    rep(k, 0, K) {
        rep(i, 0, N) {
            rep(j, 0, N) {
                int ways = 0;
                if (i != 0) ways++;
                if (j != 0) ways++;
                if (i != N-1) ways++;
                if (j != N-1) ways++;
                // Transition
                if (i != 0) dp2[i-1][j] += dp1[i][j] / ways;
                if (j != 0) dp2[i][j-1] += dp1[i][j] / ways;
                if (i != N-1) dp2[i+1][j] += dp1[i][j] / ways;
                if (j != N-1) dp2[i][j+1] += dp1[i][j] / ways;
            }
        }
        swap(dp1, dp2);
        rep(i, 0, N) {
            rep(j, 0, N) {
                dp2[i][j] = 0;
            }
        }
    }
    swap(robots[si*N+sj], dp1);
}

void solve() {
    cin >> K;
    rep(i, 0, N) {
        rep(j, 0, N) {
            doDP(i, j);
        }
    }
    double empty = 0;
    rep(i, 0, N) {
        rep(j, 0, N) {
            double currProb = 1;
            rep(k, 0, N*N) currProb *= (1 - robots[k][i][j]);
            empty += currProb;
        }
    }
    cout << setprecision(6) << fixed << empty << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}