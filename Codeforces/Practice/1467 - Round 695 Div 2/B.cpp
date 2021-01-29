#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 3e5+5;

int N;
int A[MAXN];
bool E[MAXN];

bool isE(int i) {
    if (i <= 0 || i >= N-1) return false;
    if (A[i] > A[i-1] && A[i] > A[i+1]) return true;
    if (A[i] < A[i-1] && A[i] < A[i+1]) return true;
    return false;
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    int ans = 0;
    rep(i, 0, N) if (isE(i)) ans++;
    
    int maxDec = 0;
    rep(i, 0, N) {
        int curr = isE(i-1) + isE(i) + isE(i+1);
        int temp = A[i];
        // Change to left
        if (i != 0) {
            A[i] = A[i-1];
            int n = isE(i-1) + isE(i) + isE(i+1);
            maxDec = max(maxDec, curr-n);
        }
        // Change to right
        if (i != N-1) {
            A[i] = A[i+1];
            int n = isE(i-1) + isE(i) + isE(i+1);
            maxDec = max(maxDec, curr-n);
        }
        A[i] = temp;
    }

    cout << ans - maxDec << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}