/**
 * Lazy segment tree.
 * 
 * Max runtime with multiply and divide: 297ms
 * Max runtime with bit shifts: ~288ms?
 */

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

ifstream fin("haybales.in");
ofstream fout("haybales.out");

const int MAXN = 2e5+5;

int N, Q;
int arr[MAXN];

struct SegmentTree {
    ll S[MAXN*4+1], M[MAXN*4+1], D[MAXN*4+1];

    void merge(int n) {
        S[n] = S[n<<1] + S[(n<<1)+1];
        M[n] = min(M[n<<1], M[(n<<1)+1]);
    }

    void prop(int n, int lb, int ub) {
        S[n<<1] += D[n] * (((lb+ub)>>1)-lb+1);
        S[(n<<1)+1] += D[n] * (ub-((lb+ub)>>1));
        M[n<<1] += D[n];
        M[(n<<1)+1] += D[n];
        D[n<<1] += D[n];
        D[(n<<1)+1] += D[n];
        D[n] = 0;
    }

    void init(int n=1, int lb=0, int ub=N-1) {
        if (lb == ub) {
            S[n] = M[n] = arr[lb];
            D[n] = 0;
        } else {
            init(n<<1, lb, (lb+ub)>>1);
            init((n<<1)+1, ((lb+ub)>>1)+1, ub);
            merge(n);
        }
    }

    void add(int l, int r, ll v, int n=1, int lb=0, int ub=N-1) {
        // cout << "add(" << l << ", " << r << ", " << v << ", " << n << ", " << lb << ", " << ub << ")" << endl;
        if (lb > r || ub < l) return;
        else if (lb >= l && ub <= r) {
            S[n] += v * (ub-lb+1);
            M[n] += v;
            D[n] += v;
            return;
        }
        prop(n, lb, ub);
        add(l, r, v, n<<1, lb, (lb+ub)>>1);
        add(l, r, v, (n<<1)+1, ((lb+ub)>>1)+1, ub);
        merge(n);
    }

    ll querySum(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (lb > r || ub < l) return 0;
        else if (lb >= l && ub <= r) return S[n];
        prop(n, lb, ub);
        return querySum(l, r, n<<1, lb, (lb+ub)>>1) + querySum(l, r, (n<<1)+1, ((lb+ub)>>1)+1, ub);
    }

    ll queryMin(int l, int r, int n=1, int lb=0, int ub=N-1) {
        if (lb > r || ub < l) return LLONG_MAX;
        else if (lb >= l && ub <= r) return M[n];
        prop(n, lb, ub);
        return min(queryMin(l, r, n<<1, lb, (lb+ub)>>1), queryMin(l, r, (n<<1)+1, ((lb+ub)>>1)+1, ub));
    }
} segt;

int main() {
    fin >> N >> Q;
    rep(i, 0, N) fin >> arr[i];
    segt.init();

    char t;
    int a, b, c;
    rep(i, 0, Q) {
        fin >> t >> a >> b;
        a--, b--;
        // cout << t << ' ' << a << ' ' << b << '\n';
        switch(t) {
            case 'P':
                // Range add
                fin >> c;
                segt.add(a, b, c);
                break;
            case 'S':
                // Range sum
                fout << segt.querySum(a, b) << '\n';
                break;
            case 'M':
                // Range min
                fout << segt.queryMin(a, b) << '\n';
                break;
            default:
                cerr << "Invalid query " << t << '\n';
        }
    }
    return 0;
}