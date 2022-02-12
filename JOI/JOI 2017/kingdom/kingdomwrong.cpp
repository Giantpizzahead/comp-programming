/*
Solution: 
Runtime: 
*/
 
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
 
const int INF = 1e9+7;
const int MAXN = 2005;
 
int H, W, minV = INF, maxV = -INF;
int A[MAXN][MAXN], newA[MAXN][MAXN];
struct Loc {
    int i, j, c;
    bool operator<(const Loc& o) const {
        return c > o.c;
    }
};
vector<Loc> locs;
set<pair<int, int>> boundL, boundR;
 
int getAns() {
    locs.clear();
    boundL.clear();
    boundR.clear();
    rep(i, 0, H) rep(j, 0, W) locs.push_back({i, j, max(maxV - A[i][j], A[i][j] - minV)});
    sort(all(locs));
 
    // Place into regions until invalid
    boundL.insert({H, -1});
    boundR.insert({-1, W});
    int ans = INF;
    for (Loc& l : locs) {
        int i = l.i, j = l.j;
        if (maxV - A[i][j] == l.c) {
            // Should go along with min (left) region
            auto ptr = prev(boundR.lower_bound({i, INF}));
            if (ptr->second <= j) {
                // Does not work
                ans = l.c;
                break;
            }
            // This works; update left region bound
            ptr = boundL.lower_bound({i, -1});
            if (ptr->second >= j) continue;  // No update needed
            // Update the bound
            while (true) {
                ptr = boundL.lower_bound({i, INF});
                if (ptr == boundL.begin()) break;
                ptr = prev(ptr);
                if (ptr->second > j) break;
                boundL.erase(ptr);
            }
            // Place new bound
            boundL.insert({i, j});
        } else {
            // Should go along with max (right) region
            auto ptr = boundL.lower_bound({i, -1});
            if (ptr->second >= j) {
                // Does not work
                ans = l.c;
                break;
            }
            // This works; update right region bound
            ptr = prev(boundR.lower_bound({i, INF}));
            if (ptr->second <= j) continue;  // No update needed
            // Update the bound
            while (true) {
                ptr = boundR.lower_bound({i, -1});
                if (ptr == boundR.end() || ptr->second < j) break;
                boundR.erase(ptr);
            }
            // Place new bound
            boundR.insert({i, j});
        }
        ans = min(maxV - A[i][j], A[i][j] - minV);
    }
    return ans;
}
 
void solve() {
    cin >> H >> W;
    rep(i, 0, H) rep(j, 0, W) {
        cin >> A[i][j];
        minV = min(A[i][j], minV);
        maxV = max(A[i][j], maxV);
    }
 
    // Try all rotations and flips
    int ans = maxV - minV;
    rep(d, 0, 8) {
        // debug << endl;
        // rep(i, 0, H) rep(j, 0, W) debug << A[i][j] << " \n"[j==W-1];
        ans = min(getAns(), ans);
        if (d != 3) {
            // Rotate board
            // (i, j) -> (j, [new W]-1-i)
            rep(i, 0, H) rep(j, 0, W) newA[j][H-1-i] = A[i][j];
            swap(H, W);
            rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
        } else {
            // Flip board
            // (i, j) -> (H-1-i, j)
            rep(i, 0, H) rep(j, 0, W) newA[H-1-i][j] = A[i][j];
            rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
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