#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 3e5+5;

int N;
set<pair<int, int>> S;
int A[MAXN], B[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        A[N+i] = A[i];
        A[2*N+i] = A[i];
    }
    N *= 3;
    for (int i = N-1; i >= 0; i--) {
        auto ptr = S.lower_bound({(A[i]+1)/2, -1});
        if (ptr == S.begin()) {
            // Never stops because of this song
            B[i] = N;
        } else {
            // Stops here
            ptr = prev(ptr);
            B[i] = ptr->second;
        }
        if (i != N-1) B[i] = min(B[i+1], B[i]);
        // Add to hull
        S.insert({A[i], i});
        while (true) {
            ptr = S.upper_bound({A[i], i});
            if (ptr == S.end()) break;
            S.erase(ptr);
        }
    }
    rep(i, 0, N/3) cout << (B[i] == N ? -1 : B[i]-i) << " \n"[i==N-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}