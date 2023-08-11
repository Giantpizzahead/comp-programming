#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

const int INF = 1e9;

struct Event {
    bool isApple;
    int t, x, n;

    bool operator<(const Event& o) const {
        return make_pair(x, isApple) < make_pair(o.x, o.isApple);
    }
};

struct Pair {
    int xEff, id;
    bool operator<(const Pair& o) const {
        return make_pair(xEff, id) < make_pair(o.xEff, id);
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
    vector<int> currCount(N);

    // Initial setup
    set<Pair> apples, cows;
    int id = 0;
    for (Event& e : E) {
        currCount[id] = e.n;
        if (e.isApple) apples.insert({e.x - e.t, id++});
        else cows.insert({e.x + e.t, id++});
    }
    // Sweep
    int answer = 0;
    id = 0;
    for (Event& e : E) {
        // debug << "\nOn " << e.isApple << " " << e.x << " " << e.t << " " << currCount[id] << endl;
        // debug << "Cows:" << endl;
        // for (auto& p : cows) debug << p.xEff << " " << currCount[p.id] << " " << p.id << endl;
        // debug << "Apples:" << endl;
        // for (auto& p : apples) debug << p.xEff << " " << currCount[p.id] << " " << p.id << endl;
        if (e.isApple) {
            // Try pairing with future cows
            while (currCount[id] > 0) {
                auto ptr = cows.upper_bound({e.x + e.t, INF});
                if (ptr != cows.begin()) {
                    // Pair these
                    ptr = prev(ptr);
                    if (currCount[id] > currCount[ptr->id]) {
                        answer += currCount[ptr->id];
                        currCount[id] -= currCount[ptr->id];
                        currCount[ptr->id] = 0;
                        cows.erase(ptr);
                    } else {
                        answer += currCount[id];
                        currCount[ptr->id] -= currCount[id];
                        currCount[id] = 0;
                    }
                } else break;
            }
            // Remove these apples from pairings
            apples.erase({e.x - e.t, id});
        } else {
            // Try pairing with future apples
            while (currCount[id] > 0) {
                auto ptr = apples.upper_bound({e.x - e.t, INF});
                if (ptr != apples.begin()) {
                    // Pair these
                    ptr = prev(ptr);
                    if (currCount[id] > currCount[ptr->id]) {
                        answer += currCount[ptr->id];
                        currCount[id] -= currCount[ptr->id];
                        currCount[ptr->id] = 0;
                        apples.erase(ptr);
                    } else {
                        answer += currCount[id];
                        currCount[ptr->id] -= currCount[id];
                        currCount[id] = 0;
                    }
                } else break;
            }
            // Remove these cows from pairings
            cows.erase({e.x + e.t, id});
        }
        // debug << answer << " answer\n";
        id++;
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