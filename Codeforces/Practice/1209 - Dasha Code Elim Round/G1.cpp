#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e5+5;

int N, Q, maxInComp, answer;
int A[MAXN], L[MAXN], R[MAXN], C[MAXN];
struct Range {
    int l, r, id;
};
vector<Range> ranges;
vector<int> adj[MAXN];
bool vis[MAXN];

void dfs(int n) {
    vis[n] = true;
    maxInComp = max(C[n], maxInComp);
    for (int e : adj[n]) {
        if (!vis[e]) dfs(e);
    }
}

void solve() {
    cin >> N >> Q;
    rep(i, 0, MAXN) {
        L[i] = MAXN;
        R[i] = -1;
    }
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
        C[A[i]]++;
        L[A[i]] = min(i, L[A[i]]);
        R[A[i]] = max(i, R[A[i]]);
    }
    rep(i, 0, MAXN) {
        if (L[i] != MAXN) ranges.push_back({L[i], R[i], i});
    }
    sort(all(ranges), [](const Range& a, const Range& b) {
        return tie(a.l, a.r) < tie(b.l, b.r);
    });
    Range currR = {-1, -1, -1};
    for (Range& r : ranges) {
        if (currR.r >= r.l) {
            // Overlap
            adj[r.id].push_back(currR.id);
            adj[currR.id].push_back(r.id);
            // cout << r.id+1 << " " << currR.id+1 << endl;
            if (r.r > currR.r) currR = r;
        } else {
            // No overlap
            currR = r;
        }
    }
    // Find components
    answer = N;
    rep(i, 0, MAXN) {
        if (C[i] != 0 && !vis[i]) {
            maxInComp = 0;
            dfs(i);
            answer -= maxInComp;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}