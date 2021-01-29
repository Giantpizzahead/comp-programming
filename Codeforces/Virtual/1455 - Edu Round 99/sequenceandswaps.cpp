#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, X;
int A[MAXN];

bool arrSorted() {
    for (int i = 1; i < N; i++) {
        if (A[i] < A[i-1]) {
            return false;
        }
    }
    return true;
}

void solve() {
    cin >> N >> X;
    for (int i = 0; i < N; i++) cin >> A[i];
    // Already sorted?
    if (arrSorted()) {
        cout << 0 << endl;
        return;
    }
    // Is prefix smaller?
    bool largerFound = false;
    for (int i = 0; i < N; i++) {
        if (A[i] >= X) {
            largerFound = true;
        }
        if (A[i] < X && largerFound) {
            cout << -1 << endl;
            return;
        }
    }
    // Greedy...?
    int answer = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] > X) {
            // Must switch (otherwise later switches will be invalid)
            swap(A[i], X);
            answer++;
            // Check if it's sorted
            if (arrSorted()) {
                cout << answer << endl;
                return;
            }
            // cout << "swap ";
            // for (int j = 0; j < N; j++) cout << A[j] << ' ';
            // cout << "x = " << X << endl;
        }
    }
    if (arrSorted()) cout << answer << endl;
    else cout << -1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) solve();
    return 0;
}