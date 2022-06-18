#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 2e5+5;
const int MAXV = 1e9+7;

int N;
int preLeft[MAXN];
int preRight[MAXN];
int X[MAXN];

ll solve(int S) {
    ll ans = 0;
    bool isRight = (S == 0 || (X[S+1] - X[S] <= X[S] - X[S-1]));
    while (true) {
        
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> X[i];
    rep(i, 0, N-1) preLeft[i] = X[i] - (X[i+1]-X[i]);
    rep(i, 1, N) preRight[i] = (MAXV - X[i]) - (X[i]-X[i-1]);
    rep(i, 0, N) cout << solve(i) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}