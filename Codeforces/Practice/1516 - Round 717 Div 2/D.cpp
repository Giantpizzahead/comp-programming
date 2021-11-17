#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const int MAXL = 18;

int N, Q;
int A[MAXN], ans[MAXN], S[MAXN];
int dpNext[MAXL][MAXN], dpCnt[MAXL][MAXN];
vector<int> tempP;
map<int, int> seenP;
int P[MAXN];

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) cin >> A[i];

    // Find stoppage points
    S[N] = N;
    for (int i = N-1; i >= 0; i--) {
        while (A[i] > 1) {
            tempP.push_back(P[A[i]]);
            A[i] /= P[A[i]];
        }
        S[i] = S[i+1];
        for (int p : tempP) {
            auto ptr = seenP.find(p);
            if (ptr != seenP.end()) S[i] = min(ptr->second, S[i]);
        }
        for (int p : tempP) seenP[p] = i;
        tempP.clear();
    }

    // Binary lifting
    for (int i = N; i >= 0; i--) {
        dpNext[0][i] = S[i], dpCnt[0][i] = 1;
        rep(j, 1, MAXL) {
            dpNext[j][i] = dpNext[j-1][dpNext[j-1][i]];
            dpCnt[j][i] = dpCnt[j-1][i] + dpCnt[j-1][dpNext[j-1][i]];
        }
    }

    // Answer queries
    int l, r;
    rep(i, 0, Q) {
        cin >> l >> r;
        l--, r--;
        int res = 0;
        for (int j = MAXL-1; j >= 0; j--) {
            if (dpNext[j][l] <= r) {
                res += dpCnt[j][l];
                l = dpNext[j][l];
            }
        }
        cout << res+1 << '\n';
    }
    // rep(i, 0, N+1) cout << S[i] << " \n"[i==N];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    rep(i, 2, MAXN) {
        if (!P[i]) {
            for (int j = i; j < MAXN; j += i) P[j] = i;
        }
    }
    solve();
    return 0;
}