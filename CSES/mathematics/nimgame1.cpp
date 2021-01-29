#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5;

int N;
int A[MAXN];

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> A[i];

    int X = 0;
    for (int i = 0; i < N; i++) X ^= A[i];
    
    if (X == 0) cout << "second" << endl;
    else cout << "first" << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}