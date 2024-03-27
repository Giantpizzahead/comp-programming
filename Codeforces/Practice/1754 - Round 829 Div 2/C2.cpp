#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e5+5;

int N, K;
int A[MAXN], B[MAXN];
bool inTarget[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    K = 0;
    rep(i, 0, N) K += A[i];
    K *= -1;  // Now K is the target sum
    rep(i, 1, N) B[i] = A[i] * -2;

    if (abs(K) % 2 == 1) {
        cout << "-1\n";
        return;
    }

    // Pick non-adjacent elements in B to make target sum K
    // cout << "target: " << K << endl;
    vector<int> minLocs, maxLocs;
    minLocs.push_back(-1);
    maxLocs.push_back(-1);
    rep(i, 1, N) {
        if (B[i] == -2 && minLocs.back() <= i-2) minLocs.push_back(i);
        if (B[i] == 2 && maxLocs.back() <= i-2) maxLocs.push_back(i);
    }
    minLocs.erase(minLocs.begin());
    maxLocs.erase(maxLocs.begin());

    vector<int> target;
    if (K >= 0) {
        if (K > 2*sz(maxLocs)) {
            cout << "-1\n";
            return;
        }
        // Use these as the partitions
        rep(i, 0, abs(K)/2) target.push_back(maxLocs[i]);
    } else {
        if (K < -2*sz(minLocs)) {
            cout << "-1\n";
            return;
        }
        rep(i, 0, abs(K)/2) target.push_back(minLocs[i]);
    }

    // Output partitions
    rep(i, 0, N) inTarget[i] = false;
    for (int x : target) inTarget[x] = true;
    vector<pair<int, int>> ans;
    for (int i = N-1; i >= 0; i -= (inTarget[i] ? 2 : 1)) {
        ans.push_back({inTarget[i] ? i-1 : i, i});
    }
    reverse(all(ans));
    cout << sz(ans) << "\n";
    for (auto& p : ans) cout << p.first+1 << " " << p.second+1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    // int T = 1;
    rep(i, 0, T) solve();
    return 0;
}
