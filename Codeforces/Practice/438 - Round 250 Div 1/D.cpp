#include <iostream>
#include <set>
using namespace std;
using ll = long long;
const int MAXN = 1e5;

int N, M;
int A[MAXN];

struct SegmentTree {
    int V[MAXN*4+1], maxV[MAXN*4+1];
    ll sum[MAXN*4+1];

    void merge(int n) {
        maxV[n] = max(maxV[n*2], maxV[n*2+1]);
        sum[n] = sum[n*2] + sum[n*2+1];
    }

    void update(int l, int r, int x, int n = 1, int lb = 0, int ub = N-1) {
        if (l > ub || r < lb || maxV[n] < x) return;
        else if (lb == ub) {
            V[n] %= x;
            maxV[n] = V[n];
            sum[n] = V[n];
            return;
        }
        update(l, r, x, n*2, lb, (lb+ub)/2);
        update(l, r, x, n*2+1, (lb+ub)/2+1, ub);
        merge(n);
    }

    void set(int i, int x, int n = 1, int lb = 0, int ub = N-1) {
        if (lb == ub) {
            V[n] = x;
            maxV[n] = x;
            sum[n] = x;
            return;
        } else if (i > (lb+ub)/2) {
            set(i, x, n*2+1, (lb+ub)/2+1, ub);
        } else {
            set(i, x, n*2, lb, (lb+ub)/2);
        }
        merge(n);
    }

    ll query(int l, int r, int n = 1, int lb = 0, int ub = N-1) {
        if (l > ub || r < lb) return 0;
        else if (lb >= l && ub <= r) return sum[n];
        return query(l, r, n*2, lb, (lb+ub)/2) + query(l, r, n*2+1, (lb+ub)/2+1, ub);
    }
};

SegmentTree segt;

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        segt.set(i, x);
    }
    int t, a, b, c;
    for (int i = 0; i < M; i++) {
        cin >> t >> a >> b;
        if (t == 1) {
            cout << segt.query(a-1, b-1) << endl;
        } else if (t == 2) {
            cin >> c;
            segt.update(a-1, b-1, c);
        } else {
            segt.set(a-1, b);
        }
    }
    return 0;
}