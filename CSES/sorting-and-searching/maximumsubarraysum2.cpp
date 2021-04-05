#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, A, B;
ll X[MAXN], preX[MAXN];

// Stores sliding minimum
struct MonotonicQueue {
    deque<pair<int, ll>> vals;

    void push(int a, ll b) {
        while (!vals.empty() && vals.back().second >= b) vals.pop_back();
        vals.emplace_back(a, b);
    }

    void slide(int a) {
        while (!vals.empty() && vals.front().first < a) vals.pop_front();
    }

    ll query() {
        return vals.front().second;
    }
} mq;

void solve() {
    cin >> N >> A >> B;
    rep(i, 1, N+1) cin >> X[i];
    rep(i, 1, N+1) preX[i] = preX[i-1] + X[i];
    ll ans = LONG_LONG_MIN;
    rep(i, 1, N+1) {
        if (i-A >= 0) mq.push(i-A, preX[i-A]);
        mq.slide(i-B);
        if (!mq.vals.empty()) ans = max(preX[i] - mq.query(), ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}