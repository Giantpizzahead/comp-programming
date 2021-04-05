#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5+5, MAXC = 4e5+5;

int N, Q;
int A[MAXN], qT[MAXN], qA[MAXN], qB[MAXN];
vi S;

struct BIT {
    int V[MAXC];

    void upd(int i, int v) {
        for (; i < MAXC; i+=i&-i) V[i] += v;
    }

    int query(int i) {
        int r = 0;
        for (; i > 0; i-=i&-i) r += V[i];
        return r;
    }

    int query(int l, int r) {
        return query(r) - query(l-1);
    }
} bit;

void solve() {
    cin >> N >> Q;
    S.reserve(N+Q+1);
    rep(i, 0, N) {
        cin >> A[i];
        S.push_back(A[i]);
    }
    char c;
    rep(i, 0, Q) {
        cin >> c >> qA[i] >> qB[i];
        if (c == '!') {
            qA[i]--;
            qT[i] = 0;
            S.push_back(qB[i]);
        } else {
            qT[i] = 1;
        }
    }
    // Compress salaries
    sort(all(S));
    S.erase(unique(all(S)), S.end());
    // for (int x : S) cout << x << " ";
    // cout << endl;
    rep(i, 0, N) A[i] = distance(S.begin(), lower_bound(all(S), A[i])) + 1;
    rep(i, 0, Q) {
        if (qT[i] == 1) {
            qA[i] = distance(S.begin(), lower_bound(all(S), qA[i])) + 1;
            qB[i] = distance(S.begin(), upper_bound(all(S), qB[i]));
        } else qB[i] = distance(S.begin(), lower_bound(all(S), qB[i])) + 1;
    }
    // Answer queries
    rep(i, 0, N) bit.upd(A[i], 1);
    rep(i, 0, Q) {
        if (qT[i] == 0) {
            // Update
            bit.upd(A[qA[i]], -1);
            A[qA[i]] = qB[i];
            bit.upd(A[qA[i]], 1);
        } else {
            // Query
            cout << bit.query(qA[i], qB[i]) << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}