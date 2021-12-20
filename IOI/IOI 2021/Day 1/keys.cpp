#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using namespace std;
using ll = long long;

const int MAXN = 6e5+10;

int N, M;
vector<int> R, ans;
unordered_map<int, vector<int>> adj[MAXN];

void dfs(int i) {
	unordered_map<int, vector<int>> active;
	unordered_set<int> keys;
	vector<int> toVisit;
	vector<bool> vis(N);
	toVisit.push_back(i);
	int numVis = 0;
	while (!toVisit.empty()) {
		int n = toVisit.back(); toVisit.pop_back();
		if (vis[n]) continue;
		vis[n] = true; numVis++;
		for (auto& p : adj[n]) {
			auto& v = active[p.first];
			v.insert(v.end(), all(p.second));
		}
		keys.insert(R[n]);
		for (int k : keys) {
			if (active.count(k)) {
				for (int e : active[k]) {
					toVisit.push_back(e);
				}
				active.erase(k);
			}
		}
	}
	ans[i] = numVis;
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c) {
	N = sz(r), M = sz(u);
	R.clear(); ans.clear();
	rep(i, 0, N) adj[i].clear();
    R = r;
	ans.resize(N);
	rep(i, 0, M) {
		adj[u[i]][c[i]].push_back(v[i]);
		adj[v[i]][c[i]].push_back(u[i]);
	}
	int minAns = MAXN;
	rep(i, 0, N) {
		dfs(i);
		minAns = min(ans[i], minAns);
	}
	rep(i, 0, N) ans[i] = (ans[i] == minAns);
	return ans;
}

/*
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
	vector<int> r{0,1,1,2};
	vector<int> u{0,0,1,1,3};
	vector<int> v{1,2,2,3,1};
	vector<int> c{0,0,1,0,2};
    vector<int> ans = find_reachable(r,u,v,c);
	rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];
    return 0;
}
*/
