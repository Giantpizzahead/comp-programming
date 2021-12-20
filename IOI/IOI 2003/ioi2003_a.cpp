/**
 * MST with Kruskal's algorithm.
 * Runtime: O(W^2 + WN)
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 200;
const int MAXW = 6000;

struct DisjointSet {
	int V[MAXN];
	
	void reset() {
		rep(i, 0, MAXN) V[i] = -1;
	}
	
	int find(int x) {
		if (V[x] < 0) return x;
		else {
			int r = find(V[x]);
			V[x] = r;
			return r;
		}
	}
	
	int merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return a;
		else if (V[a] > V[b]) {
			V[a] += V[b];
			V[b] = a;
			return a;
		} else {
			V[b] += V[a];
			V[a] = b;
			return b;
		}
	}
} ds;

int N, W;

struct Edge {
	int a, b, c;
};

Edge E[MAXW];

int calcMST(int M) {
	ds.reset();
	int c = 0, e = 0;
	rep(i, 0, M) {
		// Use this edge
		int a = ds.find(E[i].a), b = ds.find(E[i].b);
		if (a != b) {
			ds.merge(a, b);
			c += E[i].c;
			e++;
		}
	}
	return (e == N-1 ? c : -1);
}

void solve() {
	cin >> N >> W;
	rep(i, 0, W) {
		int a, b, c; cin >> a >> b >> c;
		a--, b--;
		// Insert the edge
		E[i] = {a, b, c};
		for (int j = i; j > 0 && E[j-1].c > E[j].c; j--) {
			swap(E[j-1], E[j]);
		}
		// Calculate new MST
		cout << calcMST(i+1) << endl;
	}
}

int main() {
    ios::sync_with_stdio(0);
    //cin.tie(0);
    solve();
    return 0;
}