/*
Solution: If array elements are not all the same, there are at most 2 valid reverses.
Find these, and check Meta condition manually.
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

const int MAXN = 2e6+5;

int N;
int A[MAXN], B[MAXN];
vector<int> D, revD;

const int K = 3;
const ll HASH_C[] = {6291469, 25165843, 100663319};
const ll HASH_MOD[] = {(ll) 1e9+7, 805306457, 1610612741};

struct HashInterval {
    vector<ll> ha[K], pw[K];
    HashInterval() {}
    HashInterval(vector<int>& str) {
        rep(k, 0, K) {
            ha[k].resize(sz(str)+1);
            pw[k].resize(sz(str)+1);
            pw[k][0] = 1;
            rep(i, 0, sz(str)) {
                ha[k][i+1] = (ha[k][i]*HASH_C[k]+str[i]) % HASH_MOD[k];
                pw[k][i+1] = (pw[k][i]*HASH_C[k]) % HASH_MOD[k];
            }
        }
    }
    vector<ll> hashInterval(int a, int b) {  // hash [a, b)
        vector<ll> res(K);
        rep(k, 0, K) {
            res[k] = (ha[k][b] - ha[k][a] * pw[k][b-a]) % HASH_MOD[k];
            if (res[k] < 0) res[k] += HASH_MOD[k];
        }
        return res;
    }
};

HashInterval hashFor, hashRev;

bool tryLoc(int s) {
    vector<int> newD;
    rep(i, 0, 2*N) newD.push_back(D[s+i]);
    bool works = true;
    rep(i, 0, N/2) if (newD[i] >= newD[N+i]) works = false;
    rep(i, (N+1)/2, N) if (newD[i] <= newD[N+i]) works = false;
    return works;
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    rep(i, 0, N) cin >> B[i];
    D.clear();
    rep(i, 0, N) D.push_back(A[i]);
    rep(i, 0, N) D.push_back(B[i]);
    // Check all same
    set<int> uniqueVals;
    rep(i, 0, 2*N) uniqueVals.insert(D[i]);
    if (sz(uniqueVals) == 1) {
        cout << "-1\n";
        return;
    }
    // For rotation purposes
    rep(i, 0, N) D.push_back(A[i]);
    rep(i, 0, N) D.push_back(B[i]);
    
    // Reverse
    revD.clear();
    for (int i = 4*N-1; i >= 0; i--) revD.push_back(D[i]);

    hashFor = HashInterval(D);
    hashRev = HashInterval(revD);

    // Find reverse locations
    vector<int> revLocs;
    rep(i, 0, 2*N) {
        vector<ll> res1 = hashFor.hashInterval(i, i + 2*N);
        vector<ll> res2 = hashRev.hashInterval(2*N-i, 2*N-i + 2*N);
        // cerr << "i = " << i << ": " << res1[0] << " " << res2[0] << endl;
        // cerr << i << " " << i+2*N << " and " << 2*N-i << " " << 2*N-1 + 2*N << endl;
        bool works = true;
        rep(j, 0, K) if (res1[j] != res2[j]) works = false;
        if (works) revLocs.push_back(i);
    }

    cerr << "Num reverse locations: " << sz(revLocs) << endl;

    // Try reverse locations
    int ans = 4*N;
    for (int x : revLocs) if (tryLoc(x)) ans = min(x, ans);
    // for (int x : revLocs) cout << x << " ";
    // cout << endl;

    // rep(i, 0, 4*N) cout << D[i] << " \n"[i==4*N-1];
    // rep(i, 0, 4*N) cout << revD[i] << " \n"[i==4*N-1];
    cout << (ans == 4*N ? -1 : ans) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // For HackerCup
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
