#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXM = 2e5;

int N, M;
int A[MAXM], B[MAXM];

void solve() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &A[i], &B[i]);
        if (A[i] > B[i]) swap(A[i], B[i]);
    }
    for (int i = 0; i < M; i++) {
        printf("%d %d\n", A[i], B[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}