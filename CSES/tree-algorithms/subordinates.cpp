#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
int stSize[MAXN];
vector<int> kids[MAXN];

int dfs(int n) {
    stSize[n] = 1;
    for (int e : kids[n]) {
        stSize[n] += dfs(e);
    }
    return stSize[n];
}

void solve() {
    cin >> N;
    for (int i = 2; i <= N; i++) {
        int p;
        cin >> p;
        kids[p].push_back(i);
    }
    dfs(1);
    for (int i = 1; i <= N; i++) {
        if (i != 1) cout << ' ';
        cout << stSize[i] - 1;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}