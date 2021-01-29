#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
int P[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> P[i];
    sort(P, P+N);
    ll cost = 0;
    for (int i = 0; i < N; i++) {
        cost += abs(P[N/2] - P[i]);
    }
    cout << cost << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}