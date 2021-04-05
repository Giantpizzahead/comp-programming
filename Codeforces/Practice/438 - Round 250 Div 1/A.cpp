#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e3+5;

int N, M;
pair<int, int> R[MAXN];
int V[MAXN];
vi adj[MAXN];

void solve() {
    cin >> N >> M;
    rep(i, 0, N) {
        cin >> V[i];
        R[i].first = V[i];
        R[i].second = i;
    }
    sort(R, R+N, greater<pair<int, int>>());
    int a, b;
    rep(i, 0, M) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    ll answer = 0;
    rep(i, 0, N) {
        int n = R[i].second;
        for (int x : adj[n]) answer += V[x];
        V[n] = 0;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}