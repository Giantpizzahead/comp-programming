#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int N;
int B[MAXN];

struct SegmentTree {
    int V[MAXN*4+1], D[MAXN*4+1];

    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            V[n] = 0;
            D[n] = 0;
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        V[n] = 0;
        D[n] = 0;
    }

    void prop(int n, int lb, int ub) {
        V[n*2] += D[n] * ((lb+ub)/2-lb+1);
        V[n*2+1] += D[n] * (ub-(lb+ub)/2);
        D[n*2] += D[n];
        D[n*2+1] += D[n];
        D[n] = 0;
    }

    void upd(int l, int r, int v, int n=1, int lb=0, int ub=N-1) {
        if (l > r) return;
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            V[n] += v * (ub-lb+1);
            D[n] += v;
            return;
        }
        prop(n, lb, ub);
        upd(l, r, v, n*2, lb, (lb+ub)/2);
        upd(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        V[n] = V[n*2] + V[n*2+1];
    }

    int query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > r) return 0;
        if (lb > r || ub < l) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
};

SegmentTree active, middle, possible;

int seen1[MAXN], seen2[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> B[i];
        B[i]--;
        seen1[i] = -1;
        seen2[i] = -1;
    }
    active.init();
    middle.init();

    ll answer = 0;
    int possible = 0;
    rep(i, 0, N) {
        int b = B[i];
        if (seen1[b] != -1) {
            // -= # active in middle
            debug << "removeact " << seen2[b]+1 << ' ' << seen1[b]-1 << " = " << active.query(seen2[b]+1, seen1[b]-1) << endl;
            debug << "removeold " << seen1[b] << " = " << middle.query(seen1[b], seen1[b]) << endl;
            possible -= active.query(seen2[b]+1, seen1[b]-1);
            // -= # with middle interval containing old
            possible -= middle.query(seen1[b], seen1[b]);
            // Remove from active
            active.upd(seen1[b], seen1[b], -1);
            // Remove from middle interval
            middle.upd(seen2[b]+1, seen1[b]-1, -1);
        }
        // Update answer
        debug << "possible " << possible << endl;
        answer += possible;
        seen2[b] = seen1[b];
        seen1[b] = i;
        // += # active inside new middle interval
        possible += active.query(seen2[b]+1, seen1[b]-1);
        // Add to active
        active.upd(seen1[b], seen1[b], 1);
        // Add to middle interval
        middle.upd(seen2[b]+1, seen1[b]-1, 1);
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}