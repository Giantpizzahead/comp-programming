#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 262144;

int N, K;

struct BIT {
    int V[MAXN+1] = {};

    void upd(int i, int v) {
        for (; i <= MAXN; i += i & -i) V[i] += v;
    }

    int queryIndex(int i) {
        int r = 0;
        for (int j = MAXN; j > 0; j >>= 1) {
            if (V[r+j] <= i) {
                i -= V[r+j];
                r += j;
            }
        }
        return r+1;
    }
} bit;

void solve() {
    cin >> N >> K;
    rep(i, 1, N+1) bit.upd(i, 1);
    int currLoc = 0, currLeft = N;
    rep(i, 0, N) {
        currLoc = (currLoc + K) % currLeft;
        int x = bit.queryIndex(currLoc);
        cout << x << (i == N-1 ? '\n' : ' ');
        bit.upd(x, -1);
        currLeft--;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}