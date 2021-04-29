#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXK = 39;
ll pow3[MAXK+1];
struct Solve {
    ll x, d, k;
};

map<tuple<ll, ll, ll>, ll> memo;

ll solve(ll X, ll D, ll K) {
    debug << "solve " << X << " " << D << " " << K << '\n';
    assert(D-1 <= pow3[K+1]);
    auto ptr = memo.find({X, D, K});
    if (ptr != memo.end()) return ptr->second;
    ll x = X, y = 0, steps = 0;
    vector<Solve> nextSolves;
    while (steps < D) {
        ll toX = pow3[K] - x % pow3[K];
        ll toY = pow3[K] - y % pow3[K];
        ll upd = min(D-steps, min(toX, toY));
        // Add solve calls
        ll resX = x / pow3[K], resY = y / pow3[K];
        debug << resX << " " << resY;
        if ((resX & 1) == (resY & 1)) {
            ll nx = (x % pow3[K] == 0 ? y : x) % pow3[K];
            debug << " = (" << nx << ", " << upd << ", " << K-1 << ")";
            nextSolves.push_back({nx, upd, K-1});
        }
        debug << "\n";
        // Update x and y
        x = (x + upd) % pow3[K+1];
        y = (y + upd) % pow3[K+1];
        steps += upd;
    }
    // Combine solve calls greedily
    while (true) {
        break;
    }
    // Call solve
    ll answer = 0;
    for (auto& s : nextSolves) {
        if (s.k == -1) answer++;
        else answer += solve(s.x, s.d, s.k);
    }
    memo.insert({{X, D, K}, answer});
    return answer;
}

void solve() {
    ll D, X, Y;
    cin >> D >> X >> Y;
    if (X < Y) swap(X, Y);
    cout << solve(X-Y, D+Y+1, MAXK-1) - solve(X-Y, Y, MAXK-1) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pow3[0] = 1;
    rep(i, 1, MAXK+1) pow3[i] = pow3[i-1] * 3;
    int Q; cin >> Q;
    rep(i, 0, Q) solve();
    return 0;
}