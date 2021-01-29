#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, M, ans;
int A[MAXN], P[MAXN];
bool chg[MAXN];

void change(int i) {
    if (i != N-1) {
        if (chg[i]) ans--;
        chg[i] = P[i] > P[i+1];
        if (chg[i]) ans++;
    }
    if (i != 0) {
        if (chg[i-1]) ans--;
        chg[i-1] = P[i-1] > P[i];
        if (chg[i-1]) ans++;
    }
}

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
        P[A[i]] = i;
    }
    ans = 1;
    rep(i, 0, N-1) {
        chg[i] = P[i] > P[i+1];
        if (chg[i]) ans++;
    }
    rep(i, 0, M) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        swap(P[A[a]], P[A[b]]);
        swap(A[a], A[b]);
        change(A[a]);
        change(A[b]);
        cout << ans << '\n';
        // rep(j, 0, N) cout << A[j] << ' ';
        // cout << endl;
        // rep(j, 0, N) cout << P[j] << ' ';
        // cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}