#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, K;
vector<int> A;

void solve() {
    cin >> N >> K;
    A.resize(N);
    rep(i, 0, N) {
        cin >> A[i];
    }
    sort(all(A));
    int bestValid = 0;
    int valid = 0;
    rep(a, 0, N+1) {
        rep(b, 0, N+1) {
            valid = 0;
            if (a == b) {
                // Same range
                if (a == 0) valid = A[0]-1;
                else if (a == N) valid = K-A[N-1];
                else valid = A[a] - A[a-1] - 1;
            } else {
                // Different ranges
                if (a == 0) valid += A[0]-1;
                else if (a == N) valid += K-A[N-1];
                else valid += (A[a] - A[a-1])/2;
                if (b == 0) valid += A[0]-1;
                else if (b == N) valid += K-A[N-1];
                else valid += (A[b] - A[b-1])/2;
            }
            bestValid = max(valid, bestValid);
        }
    }
    cout << fixed << setprecision(7);
    cout << (double) bestValid / K << endl;
}

int main() {
    ios::sync_with_stdio(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}