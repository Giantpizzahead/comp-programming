#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;

int N;
vector< vector<ll> > S;
vector< pair<int, int> > P;

void solve() {
    cin >> N;
    S.resize(N);
    P.resize(N);
    vector<int> tempU(N), tempS(N);
    rep(i, 0, N) cin >> tempU[i];
    rep(i, 0, N) cin >> tempS[i];
    rep(i, 0, N) S[tempU[i]-1].push_back(tempS[i]);
    rep(i, 0, N) sort(S[i].begin(), S[i].end());
    rep(i, 0, N) rep(j, 1, S[i].size()) S[i][j] += S[i][j-1];
    rep(i, 0, N) P[i] = pair<int, int>(S[i].size(), i);
    sort(P.begin(), P.end());

    // Evaluate each team size
    rep(k, 1, N+1) {
        ll ans = 0;
        for (int id = N-1; id >= 0; id--) {
            if (P[id].first < k) break;
            int leftOut = P[id].first % k;
            int i = P[id].second;
            ans += S[i].back() - (leftOut == 0 ? 0 : S[i][leftOut-1]);
        }
        cout << ans << " \n"[k==N];
    }
    
    // Cleanup
    S.clear();
    P.clear();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}