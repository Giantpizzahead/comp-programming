#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, K;
pair<int, int> M[MAXN];
multiset<int> times;

void solve() {
    cin >> N >> K;
    rep(i, 0, K) times.insert(0);
    rep(i, 0, N) {
        cin >> M[i].second >> M[i].first;
    }
    sort(M, M+N);
    int answer = 0;
    rep(i, 0, N) {
        int s = M[i].second, e = M[i].first;
        auto x = times.upper_bound(s);
        if (x == times.begin()) continue;
        times.erase(prev(x));
        times.insert(e);
        answer++;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}