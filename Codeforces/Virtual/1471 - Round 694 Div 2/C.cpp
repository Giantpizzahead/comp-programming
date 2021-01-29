#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3e5+5;

int N, M;
int K[MAXN], C[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> K[i];
        K[i]--;
    }
    rep(i, 0, M) cin >> C[i];
    sort(K, K+N, greater<int>());

    ll answer = 0;
    int i = 0;
    for (; i < N; i++) {
        if (K[i] <= i || i >= M) break;
        // Give friend ith present
        answer += C[i];
    }
    for (; i < N; i++) {
        // Give friend money
        answer += C[K[i]];
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}