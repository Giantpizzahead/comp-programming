#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, M, compN;
int compID[MAXN], decided[MAXN];
vi adj[MAXN], revAdj[MAXN], compAdj[MAXN], compNodes[MAXN];

stack<int> finishTime;
void dfsFirst(int n) {
    compID[n] = -1;
    for (int e : revAdj[n]) {
        if (compID[e] == 0) dfsFirst(e);
    }
    finishTime.push(n);
}

void dfsSecond(int n) {
    compID[n] = compN;
    compNodes[compN].push_back(n);
    for (int e : adj[n]) {
        if (compID[e] == -1) dfsSecond(e);
    }
}

void solve() {
    cin >> M >> N;
    char c1, c2;
    int n1, n2, on1, on2;
    rep(i, 0, M) {
        cin >> c1 >> n1 >> c2 >> n2;
        n1--;
        n2--;
        if (c1 == '+') on1 = n1 + N;
        else {
            on1 = n1;
            n1 += N;
        }
        if (c2 == '+') on2 = n2 + N;
        else {
            on2 = n2;
            n2 += N;
        }
        adj[on1].push_back(n2);
        revAdj[n2].push_back(on1);
        adj[on2].push_back(n1);
        revAdj[n1].push_back(on2);
    }
    rep(i, 0, N*2) {
        if (compID[i] == 0) dfsFirst(i);
    }
    while (!finishTime.empty()) {
        int n = finishTime.top(); finishTime.pop();
        if (compID[n] != -1) continue;
        dfsSecond(n);
        compN++;
    }
    rep(i, 0, N) {
        if (compID[i] == compID[N+i]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    rep(n, 0, N*2) {
        for (int e : adj[n]) {
            if (compID[n] == compID[e]) continue;
            compAdj[compID[n]].push_back(compID[e]);
        }
    }
    // rep(n, 0, N*2) {
    //     cout << n << ": " << compID[n] << endl;
    // }
    rep(i, 0, compN) {
        // If nothing in this component conflicts, use it
        bool valid = true;
        for (int n : compNodes[i]) {
            if (decided[n % N] != 0) {
                valid = false;
                break;
            }
        }
        if (!valid) continue;
        // Mark all these nodes
        for (int n : compNodes[i]) {
            if (n >= N) decided[n % N] = -1;
            else decided[n] = 1;
        }
    }
    rep(i, 0, N) {
        if (i != 0) cout << ' ';
        cout << (decided[i] == 1 ? '+' : '-');
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}