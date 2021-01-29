#include <bits/stdc++.h>
#define sz(x) (int) (x.size())
#define rep(i, a, b) for (int i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 2e5, MAXB = 4, MAXX = 1e6+1;

int N, M;
int A[MAXN], cnt[MAXX], vToN[MAXX], nToV[MAXN];
int nodeValue[MAXN];
vi adj[MAXN], revAdj[MAXN];
bitset<MAXN> reachable[MAXN];

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> A[i];
        if (cnt[A[i]]++ == 0) {
            M++;
            nToV[M] = A[i];
            vToN[A[i]] = M;
        }
    }
    rep(i, 1, MAXX) {
        if (cnt[i] == 0) continue;
        nodeValue[vToN[i]] = cnt[i];
        rep(j, 0, MAXB) {
            if ((i & (1 << j)) == 0) continue;
            int other = i ^ (1 << j);
            if (vToN[other] != 0) {
                adj[vToN[other]].push_back(vToN[i]);
                revAdj[vToN[i]].push_back(vToN[other]);
            }
        }
    }
    rep(i, 1, M+1) {
        cout << bitset<MAXB>(nToV[i]) << ": ";
        for (int x : adj[i]) cout << bitset<MAXB>(nToV[x]) << " ";
        cout << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}