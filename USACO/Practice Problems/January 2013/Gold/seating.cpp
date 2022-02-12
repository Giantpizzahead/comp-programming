/*
Solution: Use a segment tree to simulate the queries efficiently. Track the longest open range at each node
(max open prefix, suffix, and middle), using lazy propagation to mark ranges as completely empty or full.
Runtime: O(N + M * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
using ll = long long;

const int MAXN = 5e5+5;
const int MAXS = MAXN * 4 + 1;

int N, M;

struct SegmentTree {
    // delta of 1 = Filled, 2 = Emptied
    int maxL[MAXS], maxR[MAXS], maxA[MAXS], delta[MAXS];

    void prop(int n, int lb, int ub) {
        if (delta[n] == 1) {
            maxL[n*2] = maxR[n*2] = maxA[n*2] = 0;
            maxL[n*2+1] = maxR[n*2+1] = maxA[n*2+1] = 0;
            delta[n*2] = delta[n*2+1] = 1;
        } else if (delta[n] == 2) {
            maxL[n*2] = maxR[n*2] = maxA[n*2] = (lb+ub)/2-lb+1;
            maxL[n*2+1] = maxR[n*2+1] = maxA[n*2+1] = ub-(lb+ub)/2;
            delta[n*2] = delta[n*2+1] = 2;
        }
        delta[n] = 0;
    }

    void merge(int n, int lb, int ub) {
        maxL[n] = maxL[n*2];
        if (maxL[n*2] == (lb+ub)/2-lb+1) maxL[n] = maxL[n*2] + maxL[n*2+1];
        maxR[n] = maxR[n*2+1];
        if (maxR[n*2+1] == ub-(lb+ub)/2) maxR[n] = maxR[n*2+1] + maxR[n*2];
        maxA[n] = max(maxR[n*2] + maxL[n*2+1], max(maxA[n*2], maxA[n*2+1]));
    }

    void setOff(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            maxL[n] = maxR[n] = maxA[n] = ub-lb+1;
            delta[n] = 2;
            return;
        }
        prop(n, lb, ub);
        setOff(l, r, n*2, lb, (lb+ub)/2);
        setOff(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n, lb, ub);
    }

    void setOn(int l, int r, int n=1, int lb=0, int ub=N-1) {
        // if (n == 1) debug << "setOn(" << l << ", " << r << ")\n";
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            maxL[n] = maxR[n] = maxA[n] = 0;
            delta[n] = 1;
            return;
        }
        prop(n, lb, ub);
        setOn(l, r, n*2, lb, (lb+ub)/2);
        setOn(l, r, n*2+1, (lb+ub)/2+1, ub);
        merge(n, lb, ub);
    }

    bool tryToSet(int p, int n=1, int lb=0, int ub=N-1) {
        prop(n, lb, ub);
        if (maxA[n] < p) return false;  // No range big enough to fill
        if (p == ub-lb+1) {
            // Entire node is filled
            setOn(lb, ub);
        } else if (maxA[n*2] >= p) {
            // Fill inside left node
            tryToSet(p, n*2, lb, (lb+ub)/2);
        } else if (maxR[n*2] + maxL[n*2+1] >= p) {
            // Fill in both left and right nodes
            int offRight = p - maxR[n*2] - 1;
            setOn((lb+ub)/2 - (maxR[n*2]-1), (lb+ub)/2+1 + offRight);
        } else {
            // Fill inside right node
            // assert(maxA[n*2+1] >= p);
            tryToSet(p, n*2+1, (lb+ub)/2+1, ub);
        }
        return true;
    }

    void print(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            cout << (maxA[n] ? '.' : 'X');
            return;
        }
        prop(n, lb, ub);
        print(n*2, lb, (lb+ub)/2);
        print(n*2+1, (lb+ub)/2+1, ub);
        if (n == 1) cout << '\n';
    }
} segt;

void solve() {
    cin >> N >> M;
    segt.setOff(0, N-1);
    int ans = 0;
    rep(i, 0, M) {
        char c; cin >> c;
        if (c == 'A') {
            int p; cin >> p;
            if (!segt.tryToSet(p)) ans++;
            // debug << "A " << p << "\n";
        } else {
            int a, b; cin >> a >> b; a--, b--;
            segt.setOff(a, b);
            // debug << "L " << a+1 << " " << b+1 << "\n";
        }
        // segt.print();
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("seating.in", "r", stdin);
    freopen("seating.out", "w", stdout);
    solve();
    return 0;
}