#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
using ll = long long;
using namespace std;

int N, L, H;
vector<vector<bool>> plat, vis;

void solve() {
    cin >> N >> L;
    H = 0;
    vector<int> s(N), l(N), h(N);
    int maxS = 0;
    rep(i, 0, N) {
        cin >> s[i] >> l[i] >> h[i];
        s[i] *= 2;
        maxS = max(s[i], maxS);
        l[i] = l[i] * 2 + 1;
        h[i]--;
        H = max(h[i], H);
    }
    H++, L = 2*L + 3;
    plat.resize(H, vector<bool>(L));
    vis.resize(H, vector<bool>(L));
    rep(i, 0, N) {
        rep(j, 0, l[i]) {
            plat[h[i]][s[i]+j] = true;
        }
    }

    vis[0][0] = true;
    rep(i, 0, H) {
        rep(j, 0, L) {
            if (!plat[i][j]) continue;
            if (j > 0) vis[i][j] = vis[i][j] || vis[i][j-1];
            // if (j > 3 && i > 1) vis[i][j] = vis[i][j] || vis[i-2][j-4];
            // if (j > 5 && i > 0) vis[i][j] = vis[i][j] || vis[i-1][j-6];
            // if (j > 7) vis[i][j] = vis[i][j] || vis[i][j-8];
            // Falling down without jumping
            for (int d = 1;; d++) {
                int oi = i + d;
                int oj = j - 2*d;
                if (oi >= H || oj < 0) break;
                if (!plat[oi][oj+1]) vis[i][j] = vis[i][j] || vis[oi][oj];
                if (plat[oi][oj]) break;
            }
            // Falling down with jumping
            for (int d = 0;; d++) {
                int oi = i - 2 + d;
                int oj = j - 4 - 2*d;
                if (oi < 0) continue;
                if (oi >= H || oj < 0) break;
                if (oi+2 < H && plat[oi+2][oj+4] && d != 0) break;
                vis[i][j] = vis[i][j] || vis[oi][oj];
                if (oi+2 < H && plat[oi+2][oj+4]) break;
            }
        }
    }

    // for (int i = H-1; i >= 0; i--) {
    //     rep(j, 0, L) cout << plat[i][j];
    //     cout << endl;
    // }
    // cout << endl;
    // for (int i = H-1; i >= 0; i--) {
    //     rep(j, 0, L) cout << vis[i][j];
    //     cout << endl;
    // }
    // cout << endl;
    
    bool works = false;
    rep(i, 0, H) if (vis[i][maxS]) works = true;
    cout << works << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}