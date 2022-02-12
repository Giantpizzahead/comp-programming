/*
Solution: Track the open ranges of seats as the queries arrive using a couple of sets. Maintain these ranges when
processing each query.
Runtime: O(N * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int INF = 1e9;

int N, M;
struct Pair {
    int a, b;
    bool operator<(const Pair& o) const {
        if (a != o.a) return a < o.a;
        else return b < o.b;
    }
};
// (a, b) = (left i, right i, both inclusive)
set<Pair> byLoc;
// (a, b) = (# cows in range, left i)
set<Pair> bySize;

void removePair(int l, int r) {
    byLoc.erase({l, r});
    bySize.erase({r-l+1, l});
}

void insertPair(int l, int r) {
    byLoc.insert({l, r});
    bySize.insert({r-l+1, l});
}

// Guaranteed that all seats in [l, r] are open
void addRange(int l, int r) {
    Pair x = *prev(byLoc.lower_bound({l, INF}));
    removePair(x.a, x.b);
    if (l != x.a) {
        // Open range on left
        int a = x.a, b = l-1;
        insertPair(a, b);
    }
    if (r != x.b) {
        // Open range on right
        int a = r+1, b = x.b;
        insertPair(a, b);
    }
}

// NOT guaranteed that all seats [l, r] are filled
void removeRange(int l, int r) {
    // Check for range before
    auto ptr = byLoc.lower_bound({l, -1});
    if (ptr != byLoc.begin()) {
        ptr = prev(ptr);
        if (ptr->b >= r-1) {
            // This range combines with the current one
            l = min(ptr->a, l);
            r = max(ptr->b, r);
            removePair(ptr->a, ptr->b);
        }
    }
    // Remove any open ranges that are inside this range
    while (true) {
        ptr = byLoc.lower_bound({l, -1});
        if (ptr == byLoc.end() || ptr->b > r) break;
        removePair(ptr->a, ptr->b);
    }
    // Check for range after
    ptr = byLoc.lower_bound({l, -1});
    if (ptr != byLoc.end() && ptr->a <= r) {
        // This range combines with the current one
        l = min(ptr->a, l);
        r = max(ptr->b, r);
        removePair(ptr->a, ptr->b);
    }
    // Add new pair
    insertPair(l, r);
}

void solve() {
    cin >> N >> M;
    byLoc.insert({0, N-1});
    bySize.insert({N, 0});
    int ans = 0;
    rep(i, 0, M) {
        char c; cin >> c;
        if (c == 'A') {
            int p; cin >> p;
            auto ptr = bySize.lower_bound({p, -1});
            if (ptr == bySize.end()) ans++;
            else addRange(ptr->b, ptr->b + p - 1);
            cout << "A " << p << "\n";
        } else {
            int a, b; cin >> a >> b; a--, b--;
            removeRange(a, b);
            cout << "L " << a+1 << " " << b+1 << "\n";
        }

        assert(sz(byLoc) == sz(bySize));
        for (auto& p : byLoc) {
            auto ptr = bySize.lower_bound({p.b-p.a+1, p.a});
            assert(ptr != bySize.end() && ptr->a == p.b-p.a+1 && ptr->b == p.a);
            cout << "(" << p.a+1 << ", " << p.b+1 << ")  ";
        }
        cout << '\n';
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("seating.in", "r", stdin);
    // freopen("seating.out", "w", stdout);
    solve();
    return 0;
}