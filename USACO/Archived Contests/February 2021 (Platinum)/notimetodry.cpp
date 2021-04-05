#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;

const int MAXN = 2e5+5;

int N, Q;
int A[MAXN];
struct Query {
    int a, b, id;
};
vector<Query> queries[MAXN];

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        for (; i < MAXN; i+=i&-i) {
            V[i] += v;
        }
    }

    void upd(int l, int r, int v) {
        l++, r++;
        // cout << "upd " << l << " " << r << " " << v << endl;
        if (l > r) return;
        upd(l, v);
        upd(r+1, -v);
    }

    int query(int i) {
        i++;
        int r = 0;
        for (; i > 0; i-=i&-i) {
            r += V[i];
        }
        return r;
    }
} bit;

set<pair<int, int>> lowerHull;
int lastSeen[MAXN], answers[MAXN];

void solve() {
    cin >> N >> Q;
    rep(i, 0, N) {
        cin >> A[i];
        A[i]--;
        lastSeen[i] = -1;
    }
    rep(i, 0, Q) {
        Query q;
        cin >> q.a >> q.b;
        q.a--, q.b--;
        q.id = i;
        queries[q.b].push_back(q);
    }
    lowerHull.emplace(-1, -1);
    rep(i, 0, N) {
        // Find closest # that is smaller
        auto ptr = prev(lowerHull.lower_bound({A[i], -2}));
        int bound = ptr->second;
        // Closest matching #
        if (lastSeen[A[i]] < bound) {
            bound = -1;
        } else {
            bound = lastSeen[A[i]];
        }
        // All locs <= bound do not have to increase paint count
        bit.upd(bound+1, i, 1);
        // Answer queries
        for (Query& q : queries[i]) {
            // cout << "query " << q.id << endl;
            answers[q.id] = bit.query(q.a);
        }
        // Update lastSeen locs & lowerHull
        lastSeen[A[i]] = i;
        while (true) {
            auto ptr = prev(lowerHull.end());
            if (ptr->first >= A[i]) {
                lowerHull.erase(ptr);
            } else break;
        }
        lowerHull.emplace(A[i], i);
    }
    rep(i, 0, Q) cout << answers[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}