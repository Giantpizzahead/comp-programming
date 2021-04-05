#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

ll E[100];
ll K, N = 0;
vi gaps;

void solve() {
    cin >> K;
    if (K & 1) {
        cout << "-1\n";
        return;
    }
    gaps.clear();
    while (K > 0) {
        rep(i, 1, N) {
            if (E[i] > K || i == N-1) {
                gaps.push_back(i-2);
                K -= E[i-1];
                break;
            }
        }
    }
    int cnt = 0;
    rep(g, 0, sz(gaps)) cnt += gaps[g] + 1;
    assert(cnt <= 2000);
    cout << cnt << "\n";
    cout << "1";
    rep(g, 0, sz(gaps)) {
        rep(i, 0, gaps[g]) cout << " 0";
        if (g != sz(gaps)-1) cout << " 1";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll pow2 = 2;
    E[0] = 0;
    while (true) {
        N++;
        E[N] = E[N-1] + pow2;
        // cout << E[N] << ' ';
        pow2 *= 2;
        if (E[N] > 3e17) break;
    }
    N++;
    // cout << endl;
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}