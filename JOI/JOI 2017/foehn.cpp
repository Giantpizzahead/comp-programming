/*
Solution: Each query only updates the temperature change at 2 locations - on the left, and on the right.
So, use a BIT to handle range updates and point queries / update the temperature for each query.
Runtime: O((N+Q) * log(N)) with notable constant factor
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN];
ll S, T;
ll currTemp;

struct BIT {
    ll V[MAXN];

    void upd(int i, ll v) {
        for (; i <= N; i+=i&-i) {
            V[i] += v;
        }
    }

    ll getTemp(int i) {
        if (i == 0 || i == N) return 0;
        ll a = query(i), b = query(i+1);
        if (a < b) return -S * (b-a);
        else return T * (a-b);
    }

    void upd(int l, int r, ll v) {
        currTemp -= getTemp(l-1);
        currTemp -= getTemp(r);
        upd(l, v);
        upd(r+1, -v);
        currTemp += getTemp(l-1);
        currTemp += getTemp(r);
    }

    ll query(int i) {
        ll r = 0;
        for (; i > 0; i-=i&-i) {
            r += V[i];
        }
        return r;
    }
} bit;

void solve() {
    cin >> N >> Q >> S >> T;
    N++;
    currTemp = 0;
    rep(i, 1, N+1) {
        cin >> A[i];
        bit.upd(i, i, A[i]);
    }
    rep(i, 0, Q) {
        int l, r;
        ll x;
        cin >> l >> r >> x;
        l++, r++;
        bit.upd(l, r, x);
        cout << currTemp << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}