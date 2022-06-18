// https://open.kattis.com/problems/walls

#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 31;

int L, W, N, R;
int X[MAXN], Y[MAXN], seen[4];

bool canReach(int x1, int y1, int x2, int y2) {
    return (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) <= R*R;
}

void markSeen(int i, int v) {
    if (canReach(X[i], Y[i], -L, 0)) seen[0] += v;
    if (canReach(X[i], Y[i], L, 0)) seen[1] += v;
    if (canReach(X[i], Y[i], 0, -W)) seen[2] += v;
    if (canReach(X[i], Y[i], 0, W)) seen[3] += v;
}

void solve() {
    cin >> L >> W >> N >> R;
    R *= 2;
    rep(i, 0, N) {
        cin >> X[i] >> Y[i];
        X[i] *= 2, Y[i] *= 2;
    }
    X[N] = -200, Y[N] = -200;
    N++;
    int ans = 5;
    rep(a, 0, N) {
        markSeen(a, 1);
        rep(b, 0, N) {
            markSeen(b, 1);
            rep(c, 0, N) {
                markSeen(c, 1);
                rep(d, 0, N) {
                    markSeen(d, 1);
                    bool works = true;
                    rep(e, 0, 4) if (!seen[e]) {
                        works = false;
                        break;
                    }
                    if (works) {
                        int curr = 4;
                        if (a == N-1) curr--;
                        if (b == N-1) curr--;
                        if (c == N-1) curr--;
                        if (d == N-1) curr--;
                        ans = min(curr, ans);
                    }
                    markSeen(d, -1);
                }
                markSeen(c, -1);
            }
            markSeen(b, -1);
        }
        markSeen(a, -1);
    }
    cout << (ans == 5 ? "Impossible" : to_string(ans)) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}