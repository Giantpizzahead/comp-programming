#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 2e5+5, MAXM = 26, H = 3;
int MOD[H], POW[H];

inline int rand(int a, int b) {
    return rand() % (b-a+1) + a;
}

int N, M;
int cToI[MAXM];
int S[MAXN];
map<vector<int>, int> seenH;

vector<int> genHashes(vector<int>& v) {
    ll hashes[H];
    rep(i, 0, H) {
        hashes[i] = 1;
        for (int x : v) {
            hashes[i] = (hashes[i] + x) * POW[i] % MOD[i];
        }
    }
    vector<int> ret(H);
    rep(i, 0, H) ret[i] = hashes[i];
    return ret;
}

void solve() {
    string str; cin >> str;
    N = sz(str);
    rep(i, 0, N) S[i] = str[i] - 'a';
    M = 0;
    rep(i, 0, MAXM) cToI[i] = -1;
    rep(i, 0, N) {
        if (cToI[S[i]] == -1) cToI[S[i]] = M++;
        S[i] = cToI[S[i]];
    }

    // Setup hashes
    rep(i, 0, H) {
        MOD[i] = rand(1e9, 1.5e9);
        POW[i] = rand(500000, 1000000);
    }

    ll answer = 0;
    vector<int> chars(M);
    seenH[genHashes(chars)]++;
    rep(i, 0, N) {
        if (S[i]) chars[S[i]]++;
        else rep(j, 1, M) chars[j]--;
        vector<int> hashes = genHashes(chars);
        answer += seenH[hashes]++;
        // for (int h : hashes) debug << h << ' ';
        // debug << '\n';
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // srand(1337);
    solve();
    return 0;
}