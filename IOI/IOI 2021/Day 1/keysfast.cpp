#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 3e5+10;

int N, M;
vector<int> R, ans, ds;
unordered_map<int, vector<int>> adj[MAXN];
unordered_set<int> keys[MAXN];
vector<int> toVisit[MAXN];
vector<int> vis, finalNodes;
vector<bool> isLeaf;

void init() {
	rep(i, 0, N) ds[i] = -1;
}

int find(int x) {
	if (ds[x] < 0) return x;
	int r = find(ds[x]);
	ds[x] = r;
	return r;
}

void addVisit(unordered_map<int, vector<int>>& a, unordered_set<int>& k, vector<int>& v) {
	vector<int> temp;
	if (sz(a) < sz(k)) {
		// Iterate through edges
		for (auto& r : a) {
			if (k.count(r.first)) {
				// Key and edges match
				temp.push_back(r.first);
				for (int e : r.second) {
					v.push_back(find(e));
				}
			}
		}
	} else {
		// Iterate through keys
		for (auto& r : k) {
			if (a.count(r)) {
				// Key and edges match
				temp.push_back(r);
				for (int e : a[r]) {
					v.push_back(find(e));
				}
			}
		}
	}
	for (int r : temp) a.erase(r);
}

int merge(int a, int b) {
	a = find(a), b = find(b);
	if (a == b) return a;
	else if (ds[a] < ds[b]) swap(a, b);

	auto& adjA = adj[a];
	auto& adjB = adj[b];
	auto& keysA = keys[a];
	auto& keysB = keys[b];
	auto& toVisitA = toVisit[a];
	auto& toVisitB = toVisit[b];

	// Add to toVisit
	addVisit(adjA, keysB, toVisitA);
	addVisit(adjB, keysA, toVisitB);

	// Merge adj, keys, and toVisit
	if (sz(adjA) < sz(adjB)) {
		adjB.insert(all(adjA));
		// adj[b] = adjB;
	} else {
		adjA.insert(all(adjB));
		swap(adj[a], adj[b]);
	}
	if (sz(keysA) < sz(keysB)) {
		keysB.insert(all(keysA));
		// keys[b] = keysB;
	} else {
		keysA.insert(all(keysB));
		swap(keys[a], keys[b]);
	}
	if (sz(toVisitA) < sz(toVisitB)) {
		toVisitB.insert(toVisitB.end(), all(toVisitA));
		// toVisit[b] = toVisitB;
	} else {
		toVisitA.insert(toVisitA.end(), all(toVisitB));
		swap(toVisitA, toVisitB);
	}
	
	// Merge a into b
	vis[b] = 1;
	isLeaf[b] = true;
	ds[b] += ds[a];
	ds[a] = b;
	return b;
}

vector<int> currNodes;

void dfs(int n) {
	n = find(n);
	if (vis[n] == 2) return;
	vis[n] = 1;
	currNodes.push_back(n);
	/*
	debug << "dfs(" << n << ")" << endl;
	debug << "stack:";
	for (int x : currNodes) debug << " " << x;
	debug << endl;
	debug << "ds: ";
	rep(i, 0, N) debug << ds[i] << " \n"[i==N-1];
	rep(i, 0, N) {
		debug << i << ": ";
		for (int k : keys[i]) debug << k << " ";
		for (auto r : adj[i]) {
			debug << "(" << r.first << " |";
			for (int e : r.second) debug << " " << e;
			debug << ") ";
		}
		debug << "/ ";
		for (int e : toVisit[i]) debug << e << " ";
		debug << endl;
	}
	debug << endl;
	*/
	vector<int> visited;
	while (!toVisit[n].empty()) {
		int e = find(toVisit[n].back());
		toVisit[n].pop_back();
		visited.push_back(e);
		// debug << "vis " << e << " from " << n << endl;
		if (e == n) continue;
		else if (vis[e] == 0) {
			// Fresh node; start there
			dfs(e);
		} else if (vis[e] == 1) {
			// Cycle; merge all nodes in cycle
			int newN = n;
			while (find(currNodes.back()) != e) {
				newN = merge(find(currNodes.back()), n);
				currNodes.pop_back();
			}
			newN = merge(find(currNodes.back()), n);
			currNodes.pop_back();
			dfs(newN);
			n = find(n);
			break;
		} else if (vis[e] == 2) {
			// Would visit
		}
		n = find(n);
	}
	if (!currNodes.empty() && find(currNodes.back()) == n) {
		// debug << "pop" << endl;
		currNodes.pop_back();
	}
	for (int e : visited) if (n != find(e)) isLeaf[n] = false;
	vis[n] = 2;
}

void solve() {
	// Generate initial toVisit
	rep(n, 0, N) {
		keys[n].insert(R[n]);
		if (!adj[n].count(R[n])) continue;
		for (int e : adj[n][R[n]]) {
			toVisit[n].push_back(e);
		}
		adj[n].erase(R[n]);
	}
	vector<int> visOrder(N);
	rep(i, 0, N) visOrder[i] = i;
	// srand(time(NULL));
	// random_shuffle(all(visOrder));
	rep(i, 0, N) {
		int n = visOrder[i];
		if (vis[find(n)] == 0) dfs(find(n));
	}
	int minSize = MAXN;
	unordered_set<int> minRoots;
	rep(n, 0, N) {
		if (find(n) != n || !isLeaf[n]) continue;
		int s = -ds[n];
		if (s < minSize) {
			minRoots.clear();
			minSize = s;
		}
		if (s <= minSize) minRoots.insert(n);
	}
	rep(n, 0, N) {
		ans[n] = (minRoots.count(find(n)) != 0);
	}
}

vector<int> find_reachable(vector<int> r, vector<int> u, vector<int> v, vector<int> c) {
	R.clear(); ans.clear(); ds.clear();
	vis.clear(); finalNodes.clear();
	isLeaf.clear();
	rep(i, 0, N) {
		adj[i].clear(); keys[i].clear(); toVisit[i].clear();
	}
	N = sz(r), M = sz(u);
    R = r;
	ans.resize(N);
	vis.resize(N);
	isLeaf.resize(N, true);
	ds.resize(N);
	init();
	rep(i, 0, M) {
		adj[u[i]][c[i]].push_back(v[i]);
		adj[v[i]][c[i]].push_back(u[i]);
	}
	solve();
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
