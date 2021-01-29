#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int C[MAXN], ans[MAXN];
vi adj[MAXN];

unordered_set<int>* dfs(int n, int p) {
    bool isLeaf = true;
    vector<unordered_set<int>*> sets;
    for (int e : adj[n]) {
        if (e == p) continue;
        isLeaf = false;
        sets.push_back(dfs(e, n));
    }
    if (isLeaf) {
        unordered_set<int>* colors = new unordered_set<int>();
        colors->insert(C[n]);
        ans[n] = 1;
        return colors;
    }
    while (sets.size() > 1) {
        if (sets[sets.size()-1]->size() > sets[sets.size()-2]->size()) {
            swap(sets[sets.size()-1], sets[sets.size()-2]);
        }
        // Merge last into 2nd last
        for (int x : *sets[sets.size()-1]) sets[sets.size()-2]->insert(x);
        delete sets[sets.size()-1];
        sets.pop_back();
    }
    sets[0]->insert(C[n]);
    ans[n] = sets[0]->size();
    return sets[0];
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> C[i];
    rep(i, 0, N-1) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    delete dfs(0, 0);
    rep(i, 0, N) {
        if (i != 0) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}