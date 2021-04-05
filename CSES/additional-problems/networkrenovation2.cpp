#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, R, C;
int numLeaves[MAXN];
bool isLeaf[MAXN];
vi adj[MAXN];

void findLeaves(int n, int p) {
    for (int e : adj[n]) {
        if (e == p) continue;
        findLeaves(e, n);
        numLeaves[n] += numLeaves[e];
    }
    if (sz(adj[n]) == 1) {
        isLeaf[n] = true;
        numLeaves[n]++;
    }
}

void findCentroid() {
    C = R;
    int tempP = R;
    bool changed;
    do {
        changed = false;
        for (int e : adj[C]) {
            if (e == tempP) continue;
            if (numLeaves[e] > numLeaves[R] / 2) {
                changed = true;
                tempP = C;
                C = e;
                break;
            }
        }
    } while (changed);
}

int G = 0;
vector<stack<int>> nodes;
vector<pair<int, int>> answer;
priority_queue<pair<int, int>> pq;

void findGroups(int n, int p) {
    if (isLeaf[n]) {
        nodes[G].push(n);
        return;
    }
    for (int e : adj[n]) {
        if (e != p) findGroups(e, n);
    }
}

void genAnswer() {
    rep(i, 0, G) pq.emplace(sz(nodes[i]), i);
    while (pq.size() > 1) {
        int a = pq.top().second; pq.pop();
        int b = pq.top().second; pq.pop();
        int u = nodes[a].top(); nodes[a].pop();
        int v = nodes[b].top(); nodes[b].pop();
        answer.emplace_back(u, v);
        if (!nodes[a].empty()) pq.emplace(sz(nodes[a]), a);
        if (!nodes[b].empty()) pq.emplace(sz(nodes[b]), b);
    }
    if (pq.size() == 1) {
        int a = pq.top().second; pq.pop();
        int u = nodes[a].top(); nodes[a].pop();
        answer.emplace_back(u, C);
    }
}

void solve() {
    cin >> N;
    int a, b;
    rep(i, 1, N) {
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    R = (sz(adj[0]) == 1 ? adj[0][0] : 0);
    findLeaves(R, R);
    findCentroid();
    // cout << "leaf centroid: " << C+1 << endl;
    nodes.resize(sz(adj[C]));
    answer.reserve((numLeaves[R]+1)/2);
    for (int e : adj[C]) {
        findGroups(e, C);
        G++;
    }
    genAnswer();
    cout << sz(answer) << '\n';
    for (auto& p : answer) cout << p.first+1 << ' ' << p.second+1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}