/*
Bad test case:
5
1 10 0 100
2 13 3 60
2 18 -8 30
2 20 11 5
2 20 -11 5
Expected = 90
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

struct Event {
    bool isApple;
    int t, x, n;

    int getCompValue() const {
        // return x;
        return x-t;
        // return isApple ? x-t : x+t;
    }

    bool operator<(const Event& o) const {
        // return make_pair(x, isApple) < make_pair(o.x, o.isApple);
        return getCompValue() < o.getCompValue();
    }
};

struct Pair {
    int xEff, n;
    bool operator<(const Pair& o) const {
        return xEff < o.xEff;
    }
};

void solve() {
    int N; cin >> N;
    vector<Event> E;
    rep(i, 0, N) {
        int q, t, x, c; cin >> q >> t >> x >> c;
        E.push_back({(q == 2), t, x, c});
    }
    sort(all(E));

    multiset<Pair> apples, cows;
    // Sweep
    int answer = 0;
    for (Event& e : E) {
        if (e.isApple) {
            // Try pairing with previous cows
            while (e.n > 0) {
                int minXEff = e.x - e.t;
                auto ptr = cows.lower_bound({minXEff, -1});
                if (ptr != cows.end()) {
                    // Pair these
                    if (e.n > ptr->n) {
                        answer += ptr->n;
                        e.n -= ptr->n;
                        cows.erase(ptr);
                    } else {
                        answer += e.n;
                        cows.insert({ptr->xEff, ptr->n - e.n});
                        cows.erase(ptr);
                        e.n = 0;
                    }
                } else break;
            }
            if (e.n != 0) {
                // These apples can still be paired
                apples.insert({e.x + e.t, e.n});
            }
        } else {
            // Try pairing with previous apples
            while (e.n > 0) {
                int minXEff = e.x + e.t;
                auto ptr = apples.lower_bound({minXEff, -1});
                if (ptr != apples.end()) {
                    // Pair these
                    if (e.n > ptr->n) {
                        answer += ptr->n;
                        e.n -= ptr->n;
                        apples.erase(ptr);
                    } else {
                        answer += e.n;
                        apples.insert({ptr->xEff, ptr->n - e.n});
                        apples.erase(ptr);
                        e.n = 0;
                    }
                } else break;
            }
            if (e.n != 0) {
                // These cows can still be paired
                cows.insert({e.x - e.t, e.n});
            }
        }
    }
    cout << answer << "\n";

    // debug << "Events:" << endl;
    // for (Event& e : E) debug << (e.isApple ? 'A' : 'C') << " " << e.x << " " << e.t << " " << e.n << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}