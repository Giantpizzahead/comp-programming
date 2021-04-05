#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 102;
int N, M;
int A[MAXN], B[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, M) cin >> B[i];
    int ans = 0, j = 0;
    rep(i, 0, N) {
        while (j != M && B[j] < A[i]) j++;
        if (j != M && A[i] == B[j]) ans++;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}