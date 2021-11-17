#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5;

int H, M, N, G = 0;
int group[MAXN], loc[MAXN];
set<int> open[MAXN];
unordered_map<int, pair<int, int>> locs;

void solve() {
    cin >> H >> M >> N;
    rep(i, 0, H) group[i] = -1;
    int repeats = 0;
    rep(i, 0, H) {
        if (group[i] == -1) {
            int j = i, k = 0;
            while (group[j] == -1) {
                open[G].insert(k);
                group[j] = G;
                loc[j] = k++;
                j = (j + M) % H;
            }
            repeats = k;
            G++;
        }
    }
    // rep(i, 0, H) debug << group[i] << " \n"[i==H-1];
    // rep(i, 0, H) debug << loc[i] << " \n"[i==H-1];
    char t;
    int x, h;
    ll ans = 0;
    locs.reserve(N);
    rep(i, 0, N) {
        cin >> t >> x;
        if (t == '+') {
            // Add
            cin >> h;
            int g = group[h], l = loc[h];
            auto ptr = open[g].lower_bound(l);
            if (ptr == open[g].end()) ptr = open[g].begin();
            int nl = *ptr;
            open[g].erase(ptr);
            locs.emplace(x, pair<int, int>{g, nl});
            ans += (l <= nl ? nl-l : repeats-(l-nl));
        } else {
            // Remove
            auto ptr = locs.find(x);
            int g = ptr->second.first, l = ptr->second.second;
            open[g].insert(l);
            locs.erase(ptr);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}