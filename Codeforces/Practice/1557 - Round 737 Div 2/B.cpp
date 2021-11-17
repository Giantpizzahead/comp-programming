// https://codeforces.com/contest/1557/problem/A

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

void solve() {
    int N, K; cin >> N >> K;
    vector< pair<int, int> > V;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        V.push_back({x, i});
    }
    sort(V.begin(), V.end());
    int last = V[0].second;
    for (int i = 1; i < N; i++) {
        if (last+1 != V[i].second) K--;
        last = V[i].second;
    }
    cout << (K > 0 ? "Yes" : "No") << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}