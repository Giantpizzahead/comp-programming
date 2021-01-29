#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5;

int N, Q;
int X[MAXN], answers[MAXN], lastSeen[MAXN];
vector<pair<int, int>> queries[MAXN];

struct BIT {
    int V[MAXN];

    void update(int i, int v) {
        i++;
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query(int i) {
        int r = 0;
        while (i > 0) {
            r += V[i];
            i -= i & -i;
        }
        return r;
    }

    int query(int l, int r) {
        l++;
        r++;
        return query(r) - query(l-1);
    }
};

BIT bit;

void solve() {
    cin >> N >> Q;
    unordered_map<int, int> xToI;
    xToI.reserve(N);
    rep(i, 0, N) {
        cin >> X[i];
        auto ptr = xToI.find(X[i]);
        if (ptr == xToI.end()) {
            xToI.emplace(X[i], xToI.size());
            X[i] = xToI.size() - 1;
        } else X[i] = ptr->second;
    }
    rep(i, 0, N) lastSeen[i] = -1;
    rep(i, 0, Q) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        queries[b].emplace_back(a, i);
    }

    rep(i, 0, N) {
        if (lastSeen[X[i]] != -1) bit.update(lastSeen[X[i]], -1);
        lastSeen[X[i]] = i;
        bit.update(i, 1);
        for (auto p : queries[i]) {
            answers[p.second] = bit.query(p.first, i);
        }
    }

    rep(i, 0, Q) cout << answers[i] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}