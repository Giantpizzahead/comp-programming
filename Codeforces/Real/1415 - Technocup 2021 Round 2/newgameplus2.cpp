#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 500005;

int N, K;
int P[MAXN];
multiset<ll> resets;
ll answer;

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> P[i];
    }
    sort(P, P+N, greater<int>());
    for (int i = 0; i <= K; i++) resets.insert(-0);
    for (int i = 0; i < N; i++) {
        auto best = resets.begin();
        answer += -*best;
        ll oldP = *best;
        resets.erase(best);
        resets.insert(oldP-P[i]);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}