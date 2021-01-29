#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXM = 2e5+5, MAXDP = 5005;
const ll INF = 1e18+7;

int N, M, Q;
int C[MAXM];
struct Point {
    int x, y;
};
Point queries[MAXM];

void answerQuery(int i) {
    int a = 1, b = 1, c = queries[i].x, d = queries[i].y, c1 = C[1], c2 = C[queries[i].y];
    if (b == d) {
        ll answer = (ll) (c-a) * c1;
        cout << answer << '\n';
        return;
    }
    double best = (double) (c2 - c1) / (2 * (d - b));
    // cout << "best: " << best << endl;
    ll bestT = round(best);
    bestT = min(bestT, (ll) c);
    bestT = max(bestT, (ll) a);
    ll answer = (bestT-a) * c1 + (d-b) * bestT * bestT + (c-bestT) * c2;
    cout << answer << '\n';
}

double getTrans(int y) {
    int a = 1, b = y, d = y+1, c1 = C[y], c2 = C[y+1];
    double best = (double) (c2 - c1) / (2 * (d - b));
    best = max(best, 0.0);
    best = min(best, N+1.0);
    return best;
}

ll dp[MAXDP+1][MAXDP+1];
bool fromX[MAXDP+1][MAXDP+1], fromY[MAXDP+1][MAXDP+1];
void doDP() {
    dp[1][1] = 0;
    rep(x, 1, N+1) {
        rep(y, 1, M+1) {
            if (x == 1 && y == 1) continue;
            dp[x][y] = INF;
            if (y != 1) {
                int c = dp[x][y-1] + x * x;
                if (c < dp[x][y]) {
                    dp[x][y] = c;
                    fromY[x][y] = true;
                    fromX[x][y] = false;
                }
            }
            if (x != 1) {
                int c = dp[x-1][y] + C[y];
                if (c < dp[x][y]) {
                    dp[x][y] = c;
                    fromX[x][y] = true;
                    fromY[x][y] = false;
                }
            }
        }
    }

    // Visualize DP
    cout << endl << "   ";
    rep(y, 1, M) {
        cout << setw(4) << C[y+1] - y * y;
    }
    // cout << endl << "    ";
    // rep(y, 1, M+1) {
    //     cout << setw(4) << setprecision(1) << fixed << getTrans(y);
    // }
    cout << endl;
    rep(x, 1, N+1) {
        cout << setw(2) << x << "  ";
        rep(y, 1, M+1) {
            cout << "O";//dp[x][y];
            if (fromY[x][y+1]) cout << " → ";
            else cout << "   ";
        }
        if (x == N) {
            cout << endl;
            break;
        }
        cout << endl << "+" << 2*x+1;
        if (2*x+1 < 10) cout << " ";
        rep(y, 1, M+1) {
            if (fromX[x+1][y]) cout << " ↓ ";
            else cout << "   ";
            cout << " ";
        }
        cout << endl;
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 1, M+1) cin >> C[i];
    if (N < MAXDP && M < MAXDP) doDP();
    cin >> Q;
    rep(i, 0, Q) {
        cin >> queries[i].x >> queries[i].y;
        if (N >= MAXDP || M >= MAXDP) answerQuery(i);
        else cout << dp[queries[i].x][queries[i].y] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}