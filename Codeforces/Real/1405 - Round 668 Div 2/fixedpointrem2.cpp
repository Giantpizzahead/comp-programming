#include <iostream>
#include <algorithm>
#include <set>

using namespace std;
using ll = long long;

const int MAXN = 300005;
const int INF = 987654321;
int N, Q;
int arr[MAXN];

struct SegmentTree {
    int vals[MAXN * 4 + 1], delta[MAXN * 4 + 1];

    SegmentTree() {
        for (int i = 0; i < MAXN; i++) {
            vals[i] = 0;
            delta[i] = 0;
        }
    }

    void propagate(int n) {
        delta[n*2] += delta[n];
        delta[n*2+1] += delta[n];
        vals[n*2] += delta[n];
        vals[n*2+1] += delta[n];
        delta[n] = 0;
    }

    void update(int l, int r, int v, int n = 1, int lb = 0, int ub = MAXN-1) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            delta[n] += v;
            vals[n] += v;
            return;
        }
        propagate(n);
        update(l, r, v, n*2, lb, (lb+ub)/2);
        update(l, r, v, n*2+1, (lb+ub)/2+1, ub);
        vals[n] = max(vals[n*2], vals[n*2+1]);
    }

    int query(int l, int r, int n = 1, int lb = 0, int ub = MAXN-1) {
        if (lb > r || ub < l) return 0;
        else if (lb >= l && ub <= r) return vals[n];
        propagate(n);
        return max(query(l, r, n*2, lb, (lb+ub)/2), query(l, r, n*2+1, (lb+ub)/2+1, ub));
    }

    int queryLowerBound(int r, int v, int n = 1, int lb = 0, int ub = MAXN-1) {
        if (lb > r || vals[n] < v) return -INF;
        else if (lb == ub) return lb;
        propagate(n);
        if ((lb+ub)/2+1 <= r && vals[n*2+1] >= v) return queryLowerBound(r, v, n*2+1, (lb+ub)/2+1, ub);
        else return queryLowerBound(r, v, n*2, lb, (lb+ub)/2);
    }
};

SegmentTree weights;

struct Query {
    int x, y, i;
};

Query queries[MAXN];
int answers[MAXN];

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> arr[i];
    int x, y;
    for (int i = 0; i < Q; i++) {
        cin >> x >> y;
        y = N - 1 - y;
        queries[i] = {x, y, i};
    }
    // Sort in order of increasing y
    sort(queries, queries+Q, [](const Query& a, const Query& b) {
        return a.y < b.y;
    });

    int queryI = 0;
    for (int i = 0; i < N; i++) {
        // Expand left area to include this element
        int weightNeeded = i - (arr[i] - 1);
        if (weightNeeded >= 0) {
            // Find largest x boundary that works
            int largestBoundary = min(i, weights.queryLowerBound(i, weightNeeded));
            // cout << "boundary " << i << ": " << largestBoundary << endl;
            if (largestBoundary != -INF) {
                // Update weights
                weights.update(0, largestBoundary, 1);
            }
        }

        // Answer queries
        for (; queryI < Q && queries[queryI].y == i; queryI++) {
            // cout << "query " << queries[queryI].i << endl;
            answers[queries[queryI].i] = weights.query(queries[queryI].x, queries[queryI].x);
        }

        /*
        for (int j = 0; j < N; j++) {
            cout << weights.query(j, j) << ' ';
        }
        cout << endl;
        */
    }

    for (int i = 0; i < Q; i++) {
        cout << answers[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    for (int i = 0; i < T; i++) solve();
    return 0;
}