#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
ll answer;
int W[MAXN];
vi adj[MAXN];
priority_queue<int> pq;

void solve() {
    cin >> N;
    answer = 0;
    rep(i, 0, N) {
        cin >> W[i];
        answer += W[i];
        adj[i].clear();
    }
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    while (!pq.empty()) pq.pop();
    rep(i, 0, N) {
        rep(j, 1, sz(adj[i])) pq.push(W[i]);
    }
    rep(i, 1, N) {
        if (i != 1) cout << ' ';
        cout << answer;
        if (i != N-1) {
            assert(!pq.empty());
            answer += pq.top();
            pq.pop();
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}