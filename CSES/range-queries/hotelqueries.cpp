#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5;

int N, M;
int H[MAXN];

struct SegmentTree {
    int V[MAXN*4+1];

    void merge(int n) {
        V[n] = max(V[n*2], V[n*2+1]);
    }

    void init(int n = 1, int lb = 1, int ub = N) {
        if (lb == ub) {
            V[n] = H[lb];
            return;
        }
        init(n*2, lb, (lb+ub)/2);
        init(n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void update(int i, int v, int n = 1, int lb = 1, int ub = N) {
        if (lb == ub) {
            V[n] += v;
            return;
        } else if (i > (lb+ub)/2) update(i, v, n*2+1, (lb+ub)/2+1, ub);
        else update(i, v, n*2, lb, (lb+ub)/2);
        merge(n);
    }

    int query(int v, int n = 1, int lb = 1, int ub = N) {
        if (V[n] < v) return 0;
        else if (lb == ub) return lb;
        else if (V[n*2] >= v) return query(v, n*2, lb, (lb+ub)/2);
        else return query(v, n*2+1, (lb+ub)/2+1, ub);
    }
};

SegmentTree segt;

void solve() {
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> H[i];
    }
    segt.init();
    for (int i = 0; i < M; i++) {
        int r;
        cin >> r;
        int h = segt.query(r);
        if (h != 0) segt.update(h, -r);
        if (i != 0) cout << ' ';
        cout << h;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}