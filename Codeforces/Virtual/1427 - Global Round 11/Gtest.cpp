#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 200;

int MAXC = 0;
int N;
ll answer = LONG_LONG_MAX;
int A[MAXN][MAXN], B[MAXN][MAXN];

ll contrast() {
    ll ans = 0;
    rep(i, 0, N) {
        rep(j, 0, N) {
            if (i != 0 && A[i][j] != -1 && A[i-1][j] != -1) ans += abs(A[i][j] - A[i-1][j]);
            if (j != 0 && A[i][j] != -1 && A[i][j-1] != -1) ans += abs(A[i][j] - A[i][j-1]);
        }
    }
    return ans;
}

void bruteForce(int i, int j) {
    if (i == N) {
        ll res = contrast();
        if (res < answer) {
            answer = res;
            rep(ri, 0, N) {
                rep(rj, 0, N) {
                    B[ri][rj] = A[ri][rj];
                }
            }
        }
        return;
    }
    if (A[i][j] == 0) {
        rep(k, 1, MAXC+1) {
            A[i][j] = k;
            if (j+1 == N) bruteForce(i+1, 0);
            else bruteForce(i, j+1);
        }
        A[i][j] = 0;
    } else {
        if (j+1 == N) bruteForce(i+1, 0);
        else bruteForce(i, j+1);
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        rep(j, 0, N) {
            cin >> A[i][j];
            MAXC = max(A[i][j], MAXC);
        }
    }
    bruteForce(0, 0);
    cout << answer << endl;
    rep(i, 0, N) {
        rep(j, 0, N) cout << B[i][j] << ' ';
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}