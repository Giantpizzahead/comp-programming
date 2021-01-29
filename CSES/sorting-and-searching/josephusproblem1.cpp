#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N;
int iToNum[MAXN];

vector<int> solve(int N, int s) {
    if (N == 1) return vector<int>(1);

    int left = (N+1-s)/2;
    vector<int> rec = solve(left, (N & 1 ? 1-s : s));

    vector<int> res;
    int j = 0;
    rep(i, 0, N) {
        if (s == 1) {
            res.push_back(i);
            s = 0;
        } else {
            iToNum[j++] = i;
            s = 1;
        }
    }
    rep(i, 0, left) {
        res.push_back(iToNum[rec[i]]);
    }
    // for (int x : res) cout << x << " ";
    // cout << endl;
    return res;
}

void solve() {
    cin >> N;
    vector<int> res = solve(N, 0);
    rep(i, 0, N) cout << res[i]+1 << (i == N-1 ? '\n' : ' ');
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}