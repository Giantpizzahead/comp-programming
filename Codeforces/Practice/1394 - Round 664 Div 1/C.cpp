#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 5e5+5, INF = 1e9;

int N, minX, maxX, minY, maxY;
int X[MAXN], Y[MAXN];
int minYWithX[MAXN], maxYWithX[MAXN];

struct SegmentTree {
    int V[MAXN*4+1];

    SegmentTree() {
        rep(i, 0, MAXN*4+1) V[i] = -INF;
    }

    void upd(int i, int v, int n = 1, int lb = 0, int ub = MAXN-1) {
        if (lb == ub) {
            V[n] = v;
            return;
        } else if (i > (lb+ub)/2) upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        else upd(i, v, n*2, lb, (lb+ub)/2);
        V[n] = max(V[n*2], V[n*2+1]);
    }

    int query(int l, int r, int n = 1, int lb = 0, int ub = MAXN-1) {
        if (l > ub || r < lb) return -INF;
        else if (lb >= l && ub <= r) return V[n];
        return max(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }
};
SegmentTree segL, segR;

void solve() {
    rep(i, 0, MAXN) {
        minYWithX[i] = INF;
        maxYWithX[i] = -INF;
    }
    cin >> N;
    rep(i, 0, N) {
        string S;
        cin >> S;
        int x = 0, y = 0;
        rep(j, 0, sz(S)) {
            if (S[j] == 'B') x++;
            else y++;
        }
        X[i] = x;
        Y[i] = y;
        minYWithX[x] = min(y, minYWithX[x]);
        maxYWithX[x] = max(y, maxYWithX[x]);
        // cout << X[i] << " " << Y[i] << endl;
    }

    minX = INF;
    minY = INF;
    rep(i, 0, N) {
        minX = min(X[i], minX);
        maxX = max(X[i], maxX);
        minY = min(Y[i], minY);
        maxY = max(Y[i], maxY);
    }
    rep(x, 0, MAXN) {
        segR.upd(minYWithX[x], -(minYWithX[x] - x));
    }

    // Fix x at every location
    int answer = INF, ax = -1, ay = -1;
    rep(x, 0, MAXN) {
        // Move from right to left
        if (-segR.query(minYWithX[x], minYWithX[x]) == minYWithX[x] - x) segR.upd(minYWithX[x], -INF);
        if (segL.query(maxYWithX[x], maxYWithX[x]) < maxYWithX[x] - x) segL.upd(maxYWithX[x], maxYWithX[x] - x);
        // Binary search on y
        int lowY = 0, highY = MAXN-1, bestCost = INF, bestY = -1;
        while (lowY <= highY) {
            int midY = (lowY + highY) / 2;
            int diag = midY - x;
            int upper = segL.query(midY, MAXN-1);
            int lower = -segR.query(0, midY);
            int topCost = max(upper - diag, maxY - midY);
            int botCost = max(diag - lower, midY - minY);
            int cost = max(max(maxX - x, x - minX), max(topCost, botCost));
            // cout << "check " << midY << " = " << topCost << " " << botCost << " = " << cost << endl;
            if (cost <= bestCost) {
                bestCost = cost;
                bestY = midY;
            }
            if (topCost > botCost) {
                lowY = midY + 1;
            } else if (botCost > topCost) {
                highY = midY - 1;
            } else {
                break;
            }
        }
        // cout << x << ": " << bestCost << endl;
        if (bestCost <= answer) {
            answer = bestCost;
            ax = x;
            ay = bestY;
        }
    }
    cout << answer << '\n';
    rep(i, 0, ax) cout << 'B';
    rep(i, 0, ay) cout << 'N';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}