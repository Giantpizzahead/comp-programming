/*
Solution: An optimal solution must have the minimum element(s) in region 1, and the maximum element(s) in region 2.
Once these are placed, the answer becomes simpler to compute:
max(max in region 1 - min of all, max of all - min in region 2).
To minimize this, sort the remaining elements based on how important it is to put them into a certain region, then place
as many into their desired regions as possible. Maintain a "hull" of the fixed elements to efficiently check if a new
element can be placed.

Note - I spent a lot of time debugging this solution, but the issue was trivial (using continue, which led to not
updating the answer). I actually fixed it before stress testing, but didn't think to submit again since I thought it was
just a code cleanup thing. Rip :(

Runtime: O(4N^2 * log(N))
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (false) cerr
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
        // debug << endl << "place A[" << i << "][" << j << "] = " << A[i][j] << endl;
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
            if (ptr->second < j) {
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
            }
            // debug << "left" << endl;
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
            if (ptr->second > j) {
                // Update the bound
                while (true) {
                    ptr = boundR.lower_bound({i, -1});
                    if (ptr == boundR.end() || ptr->second < j) break;
                    boundR.erase(ptr);
                }
                // Place new bound
                boundR.insert({i, j});
            }
            // debug << "right" << endl;
        }
        ans = min(maxV - A[i][j], A[i][j] - minV);

        // Debug boundaries
        /*
        vector<vector<char>> test(H, vector<char>(W, '.'));
        for (auto& p : boundL) {
            if (p.second == -1) continue;
            test[p.first][p.second] = '1';
        }
        for (auto& p : boundR) {
            if (p.first == -1) continue;
            test[p.first][p.second] = '2';
        }
        rep(i, 0, H) rep(j, 0, W) debug << test[i][j] << " \n"[j==W-1];
        */
    }
    // debug << "ans " << ans << endl;
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
    rep(d, 0, 4) {
        // debug << endl;
        // rep(i, 0, H) rep(j, 0, W) debug << A[i][j] << " \n"[j==W-1];
        int tempAns = getAns();
        // cout << tempAns << '\n';
        ans = min(tempAns, ans);
        if (d != 3) {
            // Rotate board
            // (i, j) -> (j, [new W]-1-i)
            rep(i, 0, H) rep(j, 0, W) newA[j][H-1-i] = A[i][j];
            swap(H, W);
            rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
        } else {
            // Flip board
            // (i, j) -> (H-1-i, j)
            // rep(i, 0, H) rep(j, 0, W) newA[H-1-i][j] = A[i][j];
            // rep(i, 0, H) rep(j, 0, W) A[i][j] = newA[i][j];
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