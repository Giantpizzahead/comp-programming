/*
Solution: For any station i, the best way to reach it is by going to the closest express station, then the closest
semiexpress, then local the rest of the way. So, the express stations effectively "split" the stations into multiple
ranges, and adding a semiexpress to each range will increase the answer by different amounts. Putting a semi in one
range does not affect the other ranges. So, greedily choose which range to put a new semiexpress in (max additional
stations visited), put the semi at the leftmost station that can't be reached through the other trains, and repeat
until all semis are used.
Runtime: O(K * log(M)) lower than intended?
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int N, M, K;
ll A, B, C, T, ans;
vector<int> S;
vector<ll> timeS;

struct Loc {
    int toAdd;
    int i, l, r;
    ll t;
    bool operator<(const Loc& o) const {
        if (toAdd != o.toAdd) return toAdd > o.toAdd;
        else return i < o.i;
    }
};
set<Loc> improve;

/*
l = Location of last non-local train
r = One index before the next express train
t = Time at location l
*/
void calcRange(int i, int l, int r, ll t) {
    // cout << "calc " << i << " " << l << " " << r << " " << t << '\n';
    // Find number reachable by local
    ll reachable = min((T-t) / A, (ll) (r-l));
    // cout << "reachable " << reachable << " at " << l << '\n';
    ans += reachable;
    int newLoc = l + 1 + reachable;

    ll newT = t + C * (newLoc-l);
    if (reachable < r-l && newT <= T) {
        // Could improve with a semiexpress train; by how much?
        int numLeft = (r-l) - reachable - 1;
        ll newReachable = min((T-newT) / A, (ll) numLeft);
        int toAdd = 1 + newReachable;
        improve.insert({toAdd, i, newLoc, r, newT});
        // cout << "improve " << toAdd << " at " << l << '\n';
    }
}

void solve() {
    cin >> N >> M >> K;
    cin >> A >> B >> C;
    cin >> T;
    ll currT = 0;
    rep(i, 0, M) {
        int x; cin >> x; x--;
        S.push_back(x);
        if (i != 0) currT += B * (S[i]-S[i-1]);
        timeS.push_back(currT);
    }
    ans = -1;  // Not counting station 1
    rep(i, 0, M) {
        if (timeS[i] <= T) ans++;  // Can reach express station
        else break;
        if (i == M-1) break;
        calcRange(i, S[i], S[i+1]-1, timeS[i]);
    }
    // Improve while possible
    rep(i, 0, K-M) {
        if (improve.empty()) break;
        Loc l = *improve.begin();
        improve.erase(l);
        ans++;
        calcRange(l.i, l.l, l.r, l.t);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}