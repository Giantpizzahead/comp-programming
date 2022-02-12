#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 1e5+5;
const int INF = 2e9+7;

int N, K;
int origA[MAXN], A[MAXN];

bool used[MAXN];
set<pair<int, int>> canUse;

struct SegmentTreePoints {
    set<int> V[MAXN*4+1];

    void upd(int i, int v, int n=1, int lb=0, int ub=N-1) {
        // debug << "upd " << i << " " << v << " " << n << " " << lb << " " << ub << endl;
        if (i > ub || i < lb) return;

        if (v >= 0) V[n].insert(v);
        else V[n].erase(-v-1);

        if (lb == ub) return;
        else if (i > (lb+ub)/2) upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        else upd(i, v, n*2, lb, (lb+ub)/2);
    }

    void query(int l, int r, int v1, int v2, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return;
        else if (lb >= l && ub <= r) {
            auto ptr = V[n].lower_bound(v1);
            while (ptr != V[n].end() && *ptr <= v2) {
                int x = *ptr;
                ptr = next(ptr);
                used[x] = true;
                upd(A[x], -x-1);
                canUse.insert({A[x], x});
            }
        } else {
            query(l, r, v1, v2, n*2, lb, (lb+ub)/2);
            query(l, r, v1, v2, n*2+1, (lb+ub)/2+1, ub);
        }
    }
} segtPoints;

struct SegmentTreeMin {
    int V[MAXN*4+1];

    void init() {
        rep(i, 0, MAXN*4+1) V[i] = N-1;
    }

    void upd(int i, int v, int n=1, int lb=0, int ub=N-1) {
        if (i > ub || i < lb) return;
        else if (lb == ub) {
            V[n] = v;
            return;
        }
        upd(i, v, n*2, lb, (lb+ub)/2);
        upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        V[n] = min(V[n*2], V[n*2+1]);
    }

    int query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return N-1;
        else if (lb >= l && ub <= r) return V[n];
        else return min(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }

    int findFirst(int v, int n=1, int lb=0, int ub=N-1) {
        if (V[n] >= v) return N;
        else if (lb == ub) return lb;
        else if (V[n*2] < v) return findFirst(v, n*2, lb, (lb+ub)/2);
        else return findFirst(v, n*2+1, (lb+ub)/2+1, ub);
    }
} segtMin;

struct SegmentTreeMax {
    int V[MAXN*4+1];

    void init() {
        rep(i, 0, MAXN*4+1) V[i] = 0;
    }

    void upd(int i, int v, int n=1, int lb=0, int ub=N-1) {
        if (i > ub || i < lb) return;
        else if (lb == ub) {
            V[n] = v;
            return;
        }
        upd(i, v, n*2, lb, (lb+ub)/2);
        upd(i, v, n*2+1, (lb+ub)/2+1, ub);
        V[n] = max(V[n*2], V[n*2+1]);
    }

    int query(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return V[n];
        else return max(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }

    int findFirst(int v, int n=1, int lb=0, int ub=N-1) {
        if (V[n] <= v) return N;
        else if (lb == ub) return lb;
        else if (V[n*2] > v) return findFirst(v, n*2, lb, (lb+ub)/2);
        else return findFirst(v, n*2+1, (lb+ub)/2+1, ub);
    }
} segtMax;

vector<int> ans;
map<int, int> vals;

int lowerInRange(int i) {
    return vals.lower_bound(origA[i] - K)->second;
}

int upperInRange(int i) {
    return prev(vals.upper_bound(origA[i] + K))->second;
}

void solve() {
    cin >> N >> K;
    // Coord compress
    rep(i, 0, N) {
        cin >> origA[i];
        vals[origA[i]] = -1;
    }
    int c = 0;
    for (auto& p : vals) p.second = c++;
    rep(i, 0, N) A[i] = vals[origA[i]];
    // rep(i, 0, N) debug << A[i] << " \n"[i==N-1];

    // Solve the problem
    segtMax.init();
    segtMin.init();
    rep(i, 0, N) {
        segtPoints.upd(A[i], i);
        segtMax.upd(i, lowerInRange(i));
        segtMin.upd(i, upperInRange(i));
    }

    // Initial lookup
    rep(x, 0, N) {
        int currMax = segtMax.query(0, x-1);
        int currMin = segtMin.query(0, x-1);
        if (A[x] >= currMax && A[x] <= currMin) {
            used[x] = true;
            segtPoints.upd(A[x], -x-1);
            canUse.insert({A[x], x});
        }
    }
    
    int numChecks = 0;
    while (sz(ans) != N) {
        assert(!canUse.empty());
        auto ptr = canUse.begin();
        int i = ptr->second;
        canUse.erase(ptr);
        ans.push_back(origA[i]);
        // Update bounds only of needed values
        int oldMax = segtMax.query(0, i);
        int oldMin = segtMin.query(0, i);
        segtMax.upd(i, 0);
        segtMin.upd(i, N-1);
        int j = i;
        int currMax = segtMax.query(0, i);
        int currMin = segtMin.query(0, i);
        bool maxSame = (currMax == oldMax);
        bool minSame = (currMin == oldMin);
        while (j != N && currMax <= currMin && (oldMax > currMax || oldMin < currMin)) {
            // Find first place where the bound changes
            int j1 = segtMax.findFirst(currMax);
            int j2 = segtMin.findFirst(currMin);
            int nj;
            if ((!maxSame && !minSame)) {
                nj = min(j1, j2);
                // Find new points to add
                segtPoints.query(currMax, currMin, 0, nj-1);
            } else if (maxSame) {
                // Only min needs to update
                nj = j2;
                segtPoints.query(segtMin.query(0, nj), currMin, 0, nj-1);
            } else {
                // Only max needs to update
                nj = j1;
                segtPoints.query(currMax, segtMax.query(0, nj), 0, nj-1);
            }
            j = nj;
            currMax = segtMax.query(0, j);
            currMin = segtMin.query(0, j);
            numChecks++;
            cout << nj << ' ' << maxSame << ' ' << minSame << '\n';
        }
    }
    // assert(numChecks < 5*N);

    rep(i, 0, N) cout << ans[i] << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}