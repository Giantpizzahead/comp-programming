#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 300, MAXP = 90001;
const int INF = 1e9+7;

int N, M, P;
struct Point {
    int i, j;
};
vector<Point> points[MAXP];
int A[MAXN][MAXN], C[MAXN][MAXN];

int D[MAXN][MAXN];
void transHeavy(int L) {
    // Reset array
    rep(i, 0, N) {
        rep(j, 0, M) {
            if (A[i][j] != L) D[i][j] = INF;
            else D[i][j] = C[i][j];
        }
    }
    // Move right
    rep(i, 0, N) rep(j, 1, M) D[i][j] = min(D[i][j-1] + 1, D[i][j]);
    // Move left
    rep(i, 0, N) for (int j = M-2; j >= 0; j--) D[i][j] = min(D[i][j+1] + 1, D[i][j]);
    // Move down
    rep(i, 1, N) rep(j, 0, M) D[i][j] = min(D[i-1][j] + 1, D[i][j]);
    // Move up
    for (int i = N-2; i >= 0; i--) rep(j, 0, M) D[i][j] = min(D[i+1][j] + 1, D[i][j]);
    // Save results
    for (Point& p : points[L+1]) {
        C[p.i][p.j] = D[p.i][p.j];
    }
}

void transLight(int L) {
    for (Point& a : points[L]) {
        for (Point& b : points[L+1]) {
            C[b.i][b.j] = min(C[a.i][a.j] + abs(a.i-b.i) + abs(a.j-b.j), C[b.i][b.j]);
        }
    }
}

void solve() {
    cin >> N >> M >> P;
    rep(i, 0, N) {
        rep(j, 0, M) {
            cin >> A[i][j];
            points[A[i][j]].push_back({i, j});
            if (A[i][j] != 1) C[i][j] = INF;
            else C[i][j] = i+j;
        }
    }
    // Move through each "layer"
    rep(i, 1, P) {
        if (sz(points[i]) >= MAXN || sz(points[i+1]) >= MAXN) {
            transHeavy(i);
        } else {
            transLight(i);
        }
        // cout << "layer " << i << endl;
        // rep(a, 0, N) {
        //     rep(b, 0, N) {
        //         cout << C[a][b] << " \n"[b==N-1];
        //     }
        // }
    }
    cout << C[points[P][0].i][points[P][0].j] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}