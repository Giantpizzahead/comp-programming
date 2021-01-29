#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N, M, K;
int A[MAXN], B[MAXN];

void solve() {
    cin >> N >> M >> K;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < M; i++) cin >> B[i];
    sort(A, A+N);
    sort(B, B+M);

    int j = 0, answer = 0;
    for (int i = 0; i < N; i++) {
        while (j != M && B[j] < A[i] - K) j++;
        if (j == M) break;
        if (B[j] <= A[i] + K) {
            j++;
            answer++;
        }
    }

    cout << answer << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}