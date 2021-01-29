#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 40;

int N, X;
int A[MAXN];

unordered_map<int, int> leftSums;

void genLeft(int i, int s) {
    if (i == N/2) {
        leftSums[s]++;
        return;
    }
    genLeft(i+1, s);
    s += A[i];
    if (s <= X) genLeft(i+1, s);
}

ll answer = 0;
void genRight(int i, int s) {
    if (i == N) {
        auto ptr = leftSums.find(X-s);
        if (ptr != leftSums.end()) answer += ptr->second;
        return;
    }
    genRight(i+1, s);
    s += A[i];
    if (s <= X) genRight(i+1, s);
}

void solve() {
    cin >> N >> X;
    leftSums.reserve(1 << (N/2));
    for (int i = 0; i < N; i++) cin >> A[i];
    genLeft(0, 0);
    genRight(N/2, 0);
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}