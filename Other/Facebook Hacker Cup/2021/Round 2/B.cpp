#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 800005;

int N, answer;
int F[MAXN], fCnt[MAXN];
vector<int> adj[MAXN];

unordered_map<int, int>* vals[MAXN];
void dfs(int n, int p) {
    unordered_set<int> toCheck;
    toCheck.insert(F[n]);
    (*vals[n])[F[n]]++;
    // Merge children
    for (int e : adj[n]) {
        if (e == p) continue;
        dfs(e, n);
        if (vals[e]->size() > vals[n]->size()) swap(vals[e], vals[n]);
        for (auto x : *vals[e]) {
            toCheck.insert(x.first);
            (*vals[n])[x.first] += x.second;
        }
    }
    for (int x : toCheck) {
        if ((*vals[n])[x] == fCnt[x]) vals[n]->erase(x);
    }
    // cout << n << ": ";
    // for (auto& x : *vals[n]) {
    //     rep(j, 0, x.second) cout << x.first << " ";
    // }
    // cout << endl;
    if (vals[n]->empty()) {
        // cout << "add " << n << endl;
        answer++;
    }
}

void solve() {
    // cout << endl;
    cin >> N;
    rep(i, 0, N) {
        adj[i].clear();
        F[i] = 0;
        fCnt[i] = 0;
        delete vals[i];
        vals[i] = new unordered_map<int, int>();
    }
    rep(i, 1, N) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    rep(i, 0, N) {
        cin >> F[i];
        F[i]--;
        fCnt[F[i]]++;
    }
    answer = 0;
    dfs(0, 0);
    cout << answer-1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, MAXN) vals[i] = new unordered_map<int, int>();
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}