#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MAXN = 100005;

int N, K;
int A[MAXN];

void solve() {
    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> A[i];
    int answer = 9999999;
    for (int i = 1; i <= 100; i++) {
        int curr = 0;
        for (int j = 0; j < N; j++) {
            if (A[j] != i) {
                j += K - 1;
                curr++;
            }
        }
        answer = min(curr, answer);
    }
    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
    return 0;
}