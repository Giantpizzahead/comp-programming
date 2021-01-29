#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXK = 500;

int N, K;
bool valid[MAXK+1];

void solve() {
    cin >> N >> K;
    int l, r;
    for (int i = 0; i < N; i++) {
        cin >> l >> r;
        for (int j = l; j <= r; j++) valid[j] = true;
    }
    int ans = 0;
    for (int i = 0; i <= MAXK; i++) {
        if (!valid[i]) continue;
        for (int j = i+1; j <= MAXK; j++) {
            if (!valid[j]) continue;
            for (int k = j+1; k <= MAXK; k++) {
                if (!valid[k]) continue;
                if ((i ^ j) <= K && (i ^ k) <= K && (j ^ k) <= K) ans++;
            }
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}