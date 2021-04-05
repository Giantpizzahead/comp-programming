#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N, K;
multiset<int> loseLen;
bool W[MAXN];

void solve() {
    cin >> N >> K;
    loseLen.clear();
    string S; cin >> S;
    int numW = 0;
    rep(i, 0, N) {
        W[i] = S[i] == 'W';
        if (W[i]) numW++;
    }
    K = min(N-numW, K);
    int li = -1;
    rep(i, 0, N) {
        if (W[i]) {
            if (li != -1 && li != i-1) {
                loseLen.insert(i-li-1);
            }
            li = i;
        }
    }

    int ans = numW + K;
    rep(i, 1, N) if (W[i] && W[i-1]) ans++;

    while (!loseLen.empty()) {
        int x = *loseLen.begin();
        loseLen.erase(loseLen.begin());
        if (K >= x) {
            K -= x;
            ans += x + 1;
        } else break;
    }

    if (numW != 0) ans += K;
    else ans += max(K-1, 0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}