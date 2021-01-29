#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;
const ll INF = 1e18;

int N;
struct Project {
    int a, b, p;
    bool operator<(const Project& o) const {
        if (b != o.b) return b < o.b;
        else return a < o.a;
    }
};
Project P[MAXN];
ll dp[MAXN];
set<pair<int, ll>> mq;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> P[i].a >> P[i].b >> P[i].p;
        P[i].b++;
    }
    sort(P, P+N);
    mq.emplace(0, 0);

    ll answer = 0;
    for (int i = 0; i < N; i++) {
        // Find last project to transition from
        auto ptr = prev(mq.upper_bound({P[i].a, INF}));
        dp[i] = ptr->second + P[i].p;
        answer = max(dp[i], answer);
        if (prev(mq.end())->second < dp[i]) mq.emplace(P[i].b, dp[i]);
    }
    // cout << "dp: ";
    // for (int i = 0; i < N; i++) cout << dp[i] << ' ';
    // cout << endl;

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}