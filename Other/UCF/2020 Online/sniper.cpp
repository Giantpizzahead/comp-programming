#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, K;
int H[MAXN], B[MAXN];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> H[i];
    }
    for (int i = 0; i < N; i++) B[i] = 0;
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        x--;
        B[x]++;
    }
    int diff = 0;
    ll bestDiff = 0;
    for (int i = 0; i < N; i++) {
        if (H[i] < 0) diff--;
        else diff++;
        if (diff > 0) {
            // Fire these bullets
            bestDiff += diff * B[i];
        }
        bestDiff += H[i];
    }
    cout << bestDiff << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}