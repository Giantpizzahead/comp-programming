#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
vi adj[MAXN];

vector<int>* dfsGen(int n, int p, int d = 0) {
    vector<vector<int>*> kidHashes;
    for (int e : adj[n]) {
        if (e == p) continue;
        kidHashes.push_back(dfsGen(e, n, d+1));
    }
    if (kidHashes.empty()) {
        vector<int>* hash = new vector<int>();
        hash->push_back(d);
        return hash;
    }
    sort(all(kidHashes), [](const vector<int>* a, const vector<int>* b) {
        return *a < *b;
    });
    while (sz(kidHashes) > 1) {
        if (kidHashes[sz(kidHashes)-1]->size() > kidHashes[sz(kidHashes)-2]->size()) {
            swap(kidHashes[sz(kidHashes)-1], kidHashes[sz(kidHashes)-2]);
        }
        for (int x : *kidHashes[sz(kidHashes)-1]) {
            kidHashes[sz(kidHashes)-2]->push_back(x);
        }
        delete kidHashes[sz(kidHashes)-1];
        kidHashes.pop_back();
    }
    kidHashes[0]->push_back(d);
    return kidHashes[0];
}

void solve() {
    cin >> N;
    rep(i, 0, N) adj[i].clear();
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int>* s1 = dfsGen(0, 0);
    rep(i, 0, N) adj[i].clear();
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int>* s2 = dfsGen(0, 0);
    // for (int x : *s1) cout << x << ' ';
    // cout << endl;
    // for (int x : *s2) cout << x << ' ';
    // cout << endl;
    cout << (*s1 == *s2 ? "YES" : "NO") << '\n';
    delete s1;
    delete s2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}