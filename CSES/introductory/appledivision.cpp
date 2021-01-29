#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 20;

int N;
int P[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> P[i];

    ll answer = 1e18;
    for (int mask = 0; mask < (1 << N); mask++) {
        ll curr = 0;
        for (int j = 0; j < N; j++) {
            if (mask & (1 << j)) curr += P[j];
            else curr -= P[j];
        }
        answer = min(abs(curr), answer);
    }

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}