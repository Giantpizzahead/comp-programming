#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cout
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
struct Edge {
	int n, id;
};
vector<Edge> adj[MAXN];

int curr = 1;
int D[MAXN], L[MAXN];
bool B[MAXN], rev[MAXN];

int dfs(int n, int p) {
	D[n] = curr;
	L[n] = curr++;
	int cnt = 0;
	for (Edge& e : adj[n]) {
		if (e.id == p) continue;
		else if (!D[e.n]) {
			cnt += dfs(e.n, e.id);
			L[n] = min(L[e.n], L[n]);
			if (L[e.n] > D[n]) {
				B[e.id] = true;
				cnt++;
			}
		} else {
			L[n] = min(D[e.n], L[n]);
		}
	}
	return cnt;
}

void solve() {
	cin >> N >> M;
	rep(i, 0, M) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		if (a > b) rev[i] = true;
		adj[a].push_back({b, i});
		adj[b].push_back({a, i});
	}
	int cnt = dfs(0, -1);
	// rep(i, 0, N) debug << D[i] << " \n"[i==N-1];
	// rep(i, 0, N) debug << L[i] << " \n"[i==N-1];
	cout << cnt << '\n';
	rep(n, 0, N) {
		for (Edge& e : adj[n]) {
			if ((e.n < n ^ rev[e.id]) || !B[e.id]) continue;
			cout << n+1 << ' ' << e.n+1 << '\n';
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	solve();
	return 0;
}