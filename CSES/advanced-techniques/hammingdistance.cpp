/**
 * Use bit operations to check pairs efficiently. (XOR operation + Count # of 1 bits)
 * Pragmas may be helpful to pass within the time limit.
 * Runtime: O(N^2 / 2) but very short and fast
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e4;

int N, K;
unsigned int A[MAXN];

void solve() {
    cin >> N >> K;
    string S;
    rep(i, 0, N) {
        cin >> S;
        rep(j, 0, K) {
            A[i] = A[i] * 2 + S[j] - '0';
        }
        // cout << A[i] << ": " << __builtin_popcount(A[i]) << endl;
    }
    int answer = K;
    rep(i, 0, N) {
        rep(j, i+1, N) {
            answer = min(__builtin_popcount(A[i] ^ A[j]), answer);
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}