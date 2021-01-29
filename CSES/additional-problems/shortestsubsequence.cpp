#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

int N;
set<int> locs[4];

void solve() {
    string str;
    cin >> str;
    N = sz(str);
    rep(i, 0, sz(str)) {
        if (str[i] == 'A') locs[0].insert(i);
        if (str[i] == 'C') locs[1].insert(i);
        if (str[i] == 'G') locs[2].insert(i);
        if (str[i] == 'T') locs[3].insert(i);
    }
    str = "";
    int loc = -1;
    while (loc != N) {
        int bestI = -1, best = loc;
        rep(i, 0, 4) {
            auto ptr = locs[i].upper_bound(loc);
            if (ptr == locs[i].end()) {
                bestI = i;
                best = N;
            } else if (*ptr > best) {
                bestI = i;
                best = *ptr;
            }
        }
        loc = best;
        if (bestI == 0) str += 'A';
        if (bestI == 1) str += 'C';
        if (bestI == 2) str += 'G';
        if (bestI == 3) str += 'T';
    }
    cout << str << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}