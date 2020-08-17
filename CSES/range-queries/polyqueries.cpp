#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 200005;

int N, Q;
int initArr[MAXN];

ll calculateSum(ll s, ll n, ll d) {
    return n * s + d * n * (n-1) / 2;
}

class SegmentTree {
public:
    ll arr[MAXN * 4 + 1], delta[MAXN * 4 + 1], deltaCount[MAXN * 4 + 1];

    ll merge(ll a, ll b) {
        return a + b;
    }

    void propagate(int n, int lb, int ub) {
        if (deltaCount[n] != 0) {
            arr[n*2] += calculateSum(delta[n], (lb+ub)/2-lb+1, deltaCount[n]);
            arr[n*2+1] += calculateSum(delta[n] + ((lb+ub)/2-lb+1) * deltaCount[n], ub-((lb+ub)/2+1)+1, deltaCount[n]);
            delta[n*2] += delta[n];
            delta[n*2+1] += delta[n] + ((lb+ub)/2-lb+1) * deltaCount[n];
            deltaCount[n*2] += deltaCount[n];
            deltaCount[n*2+1] += deltaCount[n];
            delta[n] = 0;
            deltaCount[n] = 0;
        }
    }

    void init(int n, int lb, int ub) {
        delta[n] = 0;
        if (lb == ub) {
            arr[n] = initArr[lb];
        } else {
            init(n*2, lb, (lb+ub)/2);
            init(n*2+1, (lb+ub)/2+1, ub);
            arr[n] = merge(arr[n*2], arr[n*2+1]);
        }
    }

    void update(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            arr[n] += calculateSum(lb-l+1, ub-lb+1, 1);
            delta[n] += lb-l+1;
            deltaCount[n]++;
            return;
        }
        propagate(n, lb, ub);
        update(n*2, lb, (lb+ub)/2, l, r);
        update(n*2+1, (lb+ub)/2+1, ub, l, r);
        arr[n] = merge(arr[n*2], arr[n*2+1]);
    }

    void update(int l, int r) {
        update(1, 0, N-1, l, r);
    }

    ll query(int n, int lb, int ub, int l, int r) {
        if (lb > r || ub < l) return 0;
        else if (lb >= l && ub <= r) return arr[n];
        propagate(n, lb, ub);
        return merge(query(n*2, lb, (lb+ub)/2, l, r), query(n*2+1, (lb+ub)/2+1, ub, l, r));
    }

    ll query(int l, int r) {
        return query(1, 0, N-1, l, r);
    }
};

SegmentTree segt;

int main() {
    ios::sync_with_stdio(false);
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> initArr[i];
    segt.init(1, 0, N-1);

    int t, a, b;
    for (int i = 0; i < Q; i++) {
        cin >> t >> a >> b;
        if (t == 1) {
            segt.update(a-1, b-1);
        } else {
            cout << segt.query(a-1, b-1) << '\n';
        }
    }
    return 0;
}