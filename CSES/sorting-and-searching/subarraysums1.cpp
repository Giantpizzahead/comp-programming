#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define F0R(i, a) for (int i = 0; i < a; i++)
#define FOR(i, a, b) for (int i = a; i < b; i++)

const int MAXN = 2e5;

int N, X;
int A[MAXN];

void solve() {
    cin >> N >> X;
    F0R(i, N) cin >> A[i];
    int sum = 0, li = 0, cnt = 0;
    F0R(i, N) {
        sum += A[i];
        while (sum >= X) {
            if (sum == X) cnt++;
            sum -= A[li++];
        }
    }
    cout << cnt << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}