#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 5e5+5, MAXL = 21;

int N;
ll M;
int A[3*MAXN], F[MAXL][3*MAXN];
map<ll, int> locs;

void solve() {
    cin >> N;
    if (N == 1) {
        cout << "0\n";
        return;
    }
    M = 0;
    rep(i, 0, N) {
        cin >> A[i];
        M += A[i];
    }
    M /= N;
    rep(i, 0, N) {
        A[i] -= M;
        A[N+i] = A[i];
        A[2*N+i] = A[i];
    }

    rep(i, 0, 3*N) F[0][i] = 3*N-1;

    ll currSum = 0;
    locs[0] = 3*N;
    for (int i = 3*N-1; i >= 0; i--) {
        currSum += A[i];

        if (i < 2*N) {
            // Find next sum to 0
            auto ptr = locs.find(currSum);
            assert(ptr != locs.end());
            F[0][i] = ptr->second;
        }

        locs[currSum] = i;
    }

    rep(i, 1, MAXL) {
        rep(j, 0, 3*N) {
            F[i][j] = F[i-1][F[i-1][j]];
        }
    }

    // Find best when starting at each loc
    int best = 0;
    rep(i, 0, N) {
        int cnt = 0;
        int curr = i;
        for (int j = MAXL-1; j >= 0; j--) {
            if (F[j][curr] < N+i) {
                cnt += 1 << j;
                curr = F[j][curr];
            }
        }
        // cout << cnt << '\n';
        best = max(cnt, best);
    }
    // rep(j, 0, MAXL) rep(i, 0, 3*N) cout << F[j][i] << " \n"[i==2*N-1];

    cout << N-1-best << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}