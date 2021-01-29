#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 105;
int N;
int A[MAXN], L[MAXN], R[MAXN];

void solve() {
    cin >> N;
    if (N > 100) {
        // Solution no matter what
        cout << 1 << endl;
        return;
    }
    for (int i = 0; i < N; i++) cin >> A[i];

    int answer = 999999;
    for (int i = 0; i < N-1; i++) {
        // Try all matchings
        int maxL = i+1;
        int maxR = N-i-1;
        L[0] = A[i];
        for (int j = 1; j < maxL; j++) {
            L[j] = L[j-1] ^ A[i-j];
        }
        R[0] = A[i+1];
        for (int j = 1; j < maxR; j++) {
            R[j] = R[j-1] ^ A[i+j+1];
        }
        for (int j = 0; j < maxL; j++) {
            for (int k = 0; k < maxR; k++) {
                // cout << "match " << i << " " << j << " " << k << " = " << L[j] << " " << R[k] << endl;
                if (L[j] > R[k]) {
                    answer = min(j + k, answer);
                }
            }
        }
    }
    if (answer == 999999) cout << -1 << endl;
    else cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}