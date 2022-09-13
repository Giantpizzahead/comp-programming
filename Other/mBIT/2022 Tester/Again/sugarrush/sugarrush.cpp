/*
https://codeforces.com/gym/383128/problem/J

Solution: For each starting location, the path traveled will turn at most log(N) times.
So, simulate each starting location by efficiently locating these turn points.
I did this with an offline sweep, which results in a tight runtime and is somewhat long to code.
Runtime: O(N * log^2(N))
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int MAXN = 2e5+5;
const ll INF = 1e18;

int N;
ll X[MAXN], D[MAXN];
ll ans[MAXN];
struct Query {
    int id, l, r;
    ll a;
};
vector<Query> queries, revQueries;
vector<pair<ll, int>> pairLocs;
set<int> activePairs;

void solve() {
    cin >> N;
    rep(i, 1, N+1) cin >> X[i];
    X[0] = -INF/10;
    N++;
    X[N++] = INF/10;
    rep(i, 1, N-1) {
        if (X[i+1]-X[i] <= X[i]-X[i-1]) {
            // Going right first
            queries.push_back({i, i, i, X[i-1]});
        } else {
            // Going left first
            revQueries.push_back({i, N-1-i, N-1-i, -X[i+1]});
        }
    }
    // Repeatedly perform sweeps
    bool isRev = false;
    while (!queries.empty() || !revQueries.empty()) {
        if (isRev) for (Query& q : queries) q.a++;
        // Sort queries
        sort(all(queries), [](const Query& a, const Query& b) {
            return a.a > b.a;
        });
        // Set pair values
        rep(i, 0, N-1) D[i] = 2*X[i] - X[i+1];
        D[0] = -INF;
        D[N-2] = -INF;
        rep(i, 0, N-1) pairLocs.push_back({D[i], i});
        sort(all(pairLocs));
        reverse(all(pairLocs));
        // Process queries
        while (!queries.empty()) {
            if (pairLocs.empty() || queries.back().a <= pairLocs.back().first) {
                // Query
                Query q = queries.back();
                // cout << "query " << q.a << "\n";
                queries.pop_back();
                int i = *activePairs.lower_bound(q.r);
                // Path turns here
                ans[q.id] += X[i] - X[q.l];
                int nl = N-1-i;
                int nr = N-1-q.l;
                // cout << "query " << q.id << " " << q.l << " " << q.r << " " << q.a << ": " << i << " " << X[i] - X[q.r] << "\n";
                if (nl == 1 && nr == N-2) continue;
                revQueries.push_back({q.id, nl, nr, -X[i+1]});
            } else {
                // Add pair
                // cout << "pair " << pairLocs.back().second << "\n";
                activePairs.insert(pairLocs.back().second);
                pairLocs.pop_back();
            }
        }
        queries.clear();
        pairLocs.clear();
        activePairs.clear();
        swap(revQueries, queries);
        // Reverse the array
        // cout << "reverse\n";
        rep(i, 0, N) X[i] *= -1;
        reverse(X, X+N);
        isRev = !isRev;
        // rep(i, 0, N) cout << X[i] << " \n"[i==N-1];
    }
    rep(i, 1, N-1) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}