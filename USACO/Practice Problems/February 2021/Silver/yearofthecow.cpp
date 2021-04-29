#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 65537;

int N, K, ans;
int A[MAXN], S[MAXN];

inline int getJumpLoc(int x) {
    int loc = x + (12-(x%12))%12;
    // cout << x << " -> " << loc << endl;
    return loc;
}

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> A[i];
    A[N++] = 0;
    sort(A, A+N, greater<int>());
    ans = 0;
    int currLoc = getJumpLoc(A[0]);
    rep(i, 0, N) {
        // Don't jump
        int costA = currLoc - A[i];
        // Jump
        int jumpLoc = getJumpLoc(A[i]);
        int costB = currLoc % 12 + (jumpLoc - A[i]);
        ans += costA;
        // cout << "walk: " << costA << endl;
        // cout << "jump: " << costB << endl;
        S[i] = costA - costB;
        currLoc = A[i];
    }
    // Use jumps to minimize answer
    sort(S, S+N, greater<int>());
    rep(i, 0, K-1) if (S[i] > 0) ans -= S[i];
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}