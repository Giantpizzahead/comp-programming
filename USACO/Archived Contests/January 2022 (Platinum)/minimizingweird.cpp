#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const int MAXBIT = 500;

int N, K;
int origA[MAXN], A[MAXN];

struct BIT {
    bool isLarge = false;
    vector<int> V;
    vector<pair<int, int>> points;

    void upd(int i, int v) {
        if (isLarge) for (; i <= N; i+=i&-i) V[i] += v;
        else points.push_back({i, v});
        if (!isLarge && sz(points) >= MAXBIT) {
            isLarge = true;
            V.resize(N+1);
            for (auto& p : points) upd(p.first, p.second);
            points.clear();
        }
    }

    int query(int i) {
        int r = 0;
        if (isLarge) for (; i > 0; i-=i&-i) r += V[i];
        else for (auto& p : points) if (p.first <= i) r += p.second;
        return r;
    }

    int query(int i1, int i2) {
        return query(i2) - query(i1-1);
    }
};

struct BIT2D {
    BIT V[MAXN+1];

    void upd(int i, int j, int v) {
        i++, j++;
        for (; i <= MAXN; i+=i&-i) V[i].upd(j, v);
    }

    int query(int i, int j1, int j2) {
        i++, j1++, j2++;
        int r = 0;
        for (; i > 0; i-=i&-i) r += V[i].query(j1, j2);
        return r;
    }

    int query(int i1, int i2, int j1, int j2) {
        int ans = query(i2, j1, j2) - query(i1-1, j1, j2);
        // debug << "query " << i1 << " " << i2 << " " << j1 << " " << j2 << " = " << ans << endl;
        return ans;
    }
} bit;

bool used[MAXN];
vector<int> ans;

void solve() {
    cin >> N >> K;
    // Coord compress
    map<int, int> vals;
    rep(i, 0, N) {
        cin >> origA[i];
        vals[origA[i]] = -1;
    }
    int c = 0;
    for (auto& p : vals) p.second = c++;
    rep(i, 0, N) A[i] = vals[origA[i]];
    // rep(i, 0, N) debug << A[i] << " \n"[i==N-1];

    // Solve the problem
    rep(i, 0, N) bit.upd(A[i], i, 1);
    rep(i, 0, N) {
        int bestV = 1e9+7, bestJ = -1;
        rep(j, 0, N) {
            if (used[j]) continue;
            int minV = vals.lower_bound(origA[j] - K)->second;
            int maxV = prev(vals.upper_bound(origA[j] + K))->second;
            if (bit.query(0, minV-1, 0, j-1) == 0 && bit.query(maxV+1, N-1, 0, j-1) == 0) {
                // This works
                if (A[j] < bestV) {
                    bestV = A[j];
                    bestJ = j;
                }
            }
        }
        // debug << "use " << bestJ << '\n';
        ans.push_back(origA[bestJ]);
        bit.upd(A[bestJ], bestJ, -1);
        used[bestJ] = true;
    }

    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}