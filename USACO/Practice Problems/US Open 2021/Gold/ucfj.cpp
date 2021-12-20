#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N;
int B[MAXN];

struct SegmentTree {
    ll V[MAXN*4+1], D[MAXN*4+1];

    void addDelta(ll v, int n, int lb, int ub) {
        V[n] += v * (ub-lb+1);
        D[n] += v;
    }

    void prop(int n, int lb, int ub) {
        addDelta(D[n], n*2, lb, (lb+ub)/2);
        addDelta(D[n], n*2+1, (lb+ub)/2+1, ub);
        D[n] = 0;
    }

    void merge(int n) {
        V[n] = V[n*2] + V[n*2+1];
    }

    void update(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            addDelta(v, n, lb, ub);
            return;
        }
        prop(n, lb, ub);
        update(l, r, v, n*2, lb, (lb+ub)/2);
        update(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    ll query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        prop(n, lb, ub);
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
} segt;

vector<int> locs[MAXN];
int leftLeader[MAXN], rightLeader[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> B[i];
        B[i]--;
        locs[B[i]].push_back(i);
    }
    // For each breed
    rep(b, 0, N) {
        // Left leaders
        rep(i, 0, sz(locs[b])) {
            int l = locs[b][i];
            int r = (i+1 == sz(locs[b]) ? N-1 : locs[b][i+1]-1);
            leftLeader[l] = r;
        }
        // Right leaders
        for (int i = sz(locs[b])-1; i >= 0; i--) {
            int r = locs[b][i];
            int l = (i-1 == -1 ? 0 : locs[b][i-1]+1);
            rightLeader[r] = l;
        }
    }
    // rep(i, 0, N) debug << leftLeader[i] << " \n"[i==N-1];
    // rep(i, 0, N) debug << rightLeader[i] << " \n"[i==N-1];
    vector<pair<int, int>> leftPoints;
    rep(i, 0, N) {
        leftPoints.push_back({leftLeader[i], i});
        leftPoints.push_back({i-1, -i-1});
    }
    sort(all(leftPoints));
    reverse(all(leftPoints));
    // Sweep
    ll ans = 0;
    int li = 0;
    for (int i = N-1; i >= 0; i--) {
        while (li != sz(leftPoints) && leftPoints[li].first == i) {
            int loc = leftPoints[li].second;
            if (loc < 0) {
                loc = -(loc+1);
                segt.update(loc, loc, -1);
            } else {
                segt.update(loc, loc, 1);
            }
            li++;
        }
        ans += segt.query(rightLeader[i], N-1);
    }
    ans -= N;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}