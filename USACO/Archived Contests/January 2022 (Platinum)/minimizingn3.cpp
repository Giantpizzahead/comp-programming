#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;

int N, K;
int A[MAXN];
bool used[MAXN];
vector<int> ans;

void solve() {
    cin >> N >> K;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) {
        int bestJ = -1, bestV = 1e9+7;
        rep(j, 0, N) {
            if (used[j]) continue;
            bool valid = true;
            rep(k, 0, j) {
                if (used[k]) continue;
                if (abs(A[j] - A[k]) > K) {
                    valid = false;
                    break;
                }
            }
            if (valid && A[j] < bestV) {
                bestV = A[j];
                bestJ = j;
            }
        }
        ans.push_back(A[bestJ]);
        used[bestJ] = true;
    }
    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}