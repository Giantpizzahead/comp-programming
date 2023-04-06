#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

int N;
const int MAXN = 2e5+10;
bool used[MAXN];
vector<int> ans;

void solve() {
    cin >> N;
    cout << 2 << '\n';
    ans.clear();
    rep(i, 1, N+1) used[i] = false;
    rep(i, 1, N+1) {
        if (!used[i]) {
            int n = i;
            while (n <= N) {
                used[n] = true;
                ans.push_back(n);
                n *= 2;
            }
        }
    }
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}