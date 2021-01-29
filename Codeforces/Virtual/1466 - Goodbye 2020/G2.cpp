#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;
const int MAXC = 1e6+5;

const int HASHC = 4;
const int HASHM[HASHC] = {1000000007, 1838374579, 1532759269, 1234892459};
const int HASHP[HASHC] = {91, 109, 127, 157};
ll HASHPOW[HASHC][MAXC];
struct Hash {
    int H[HASHC];

    bool operator==(const Hash& o) const {
        rep(i, 0, HASHC) if (H[i] != o.H[i]) return false;
        return true;
    }

    bool operator!=(const Hash& o) const {
        return !operator==(o);
    }
};

int powmod(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        b = b * b % m;
        e /= 2;
    }
    return r;
}

int N, Q;
string songs[40], T;
vector<Hash> songFwd[40];
struct Query {
    int k, w, id;
};
Query queries[MAXN];
int answers[MAXN];

vector<Hash> hashString(string& str) {
    vector<Hash> hashes(sz(str));
    ll H[HASHC];
    rep(i, 0, HASHC) H[i] = 0;
    rep(i, 0, sz(str)) {
        rep(j, 0, HASHC) {
            H[j] *= HASHP[j];
            H[j] += str[i] - 80;
            H[j] %= HASHM[j];
            hashes[i].H[j] = H[j];
        }
    }
    // rep(i, 0, sz(str)) {
    //     rep(j, 0, HASHC) {
    //         cout << hashes[i].H[j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    return hashes;
}

Hash substr(vector<Hash>& hashes, int l, int r) {
    if (l > r) {
        Hash h;
        rep(i, 0, HASHC) h.H[i] = 0;
        return h;
    }
    if (l < 0 || r >= sz(hashes)) {
        Hash h;
        rep(i, 0, HASHC) h.H[i] = -1;
        return h;
    }
    Hash h = hashes[r];
    if (l != 0) {
        rep(i, 0, HASHC) {
            h.H[i] -= hashes[l-1].H[i] * HASHPOW[i][r-l+1] % HASHM[i];
            if (h.H[i] < 0) h.H[i] += HASHM[i];
        }
    }
    return h;
}

vector<Hash> hashPat;

int basicSearch(string& pat) {
    // cout << "basic: " << pat << endl;
    int cnt = 0;
    rep(i, 0, sz(songs[0])-sz(pat)+1) {
        if (substr(songFwd[0], i, i+sz(pat)-1) == hashPat[sz(pat)-1]) cnt++;
    }
    return cnt;
}

int finalI;

int findString(int si, string& pat) {
    if (si == 0) {
        // Basic search
        return basicSearch(pat);
    }
    // cout << "find " << si << " " << pat << endl;
    // Go through middle
    int cnt = 0;
    rep(i, 0, sz(pat)) {
        if (T[si] != pat[i]) continue;
        if (substr(songFwd[si-1], sz(songs[si-1])-i, sz(songs[si-1])-1) != substr(hashPat, 0, i-1)) continue;
        if (substr(songFwd[si-1], 0, sz(pat)-2-i) != substr(hashPat, i+1, sz(pat)-1)) continue;
        cnt++;
    }
    // Divide and conquer
    cnt += findString(si-1, pat) * 2;
    return cnt;
}

const int MOD = 1e9+7;

ll pow2[MAXN];
ll numMiddle[256];
int lastUpdate[256];
int smartFind(string& pat, int time) {
    // cout << "smart " << pat << endl;
    // Go through middle
    int cnt = 0;
    rep(i, 0, sz(pat)) {
        if (substr(songFwd[finalI], sz(songs[finalI])-i, sz(songs[finalI])-1) != substr(hashPat, 0, i-1)) continue;
        if (substr(songFwd[finalI], 0, sz(pat)-2-i) != substr(hashPat, i+1, sz(pat)-1)) continue;
        // cout << "add " << numMiddle[pat[i]] << " bc " << pat[i] << endl;
        numMiddle[pat[i]] = (numMiddle[pat[i]] * pow2[time-lastUpdate[pat[i]]]) % MOD;
        lastUpdate[pat[i]] = time;
        cnt = (cnt + numMiddle[pat[i]]) % MOD;
    }
    return cnt;
}

void updateMiddle(int c, int time) {
    numMiddle[c] = (numMiddle[c] * pow2[time-lastUpdate[c]] + 1) % MOD;
    lastUpdate[c] = time;
}

void solve() {
    cin >> N >> Q >> songs[0] >> T;
    songFwd[0] = hashString(songs[0]);
    T = " " + T;
    rep(i, 0, Q) {
        cin >> queries[i].k >> queries[i].w;
        queries[i].id = i;
    }
    sort(queries, queries+Q, [](const Query& a, const Query& b) { return a.k < b.k; });

    int si = 0, qi = 0;
    while (sz(songs[si]) <= 1000000) {
        while (qi != Q && queries[qi].first == si) {
            hashPat = hashString(queries[qi].second.first);
            answers[queries[qi].second.second] = findString(si, queries[qi].second.first);
            qi++;
        }
        if (si == N) break;
        songs[si+1] = songs[si] + T[si+1] + songs[si];
        songFwd[si+1] = hashString(songs[si+1]);
        si++;
    }
    if (sz(songs[si]) <= 1000000) {
        // No queries of length
        goto printAnswers;
    }

    // Gen prefix and suffix hashes
    // cout << "on final" << endl;
    finalI = si-1;
    updateMiddle(T[si], si);
    while (qi != Q) {
        if (queries[qi].first == si) {
            hashPat = hashString(queries[qi].second.first);
            ll cnt = findString(finalI, queries[qi].second.first) * pow2[si-finalI] % MOD;
            // cout << " = " << cnt << endl;
            cnt = (cnt + smartFind(queries[qi].second.first, si)) % MOD;
            answers[queries[qi].second.second] = cnt;
            qi++;
        } else {
            updateMiddle(T[si+1], si+1);
            si++;
        }
    }

    printAnswers:
    rep(i, 0, Q) {
        cout << answers[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    rep(i, 0, HASHC) {
        HASHPOW[i][0] = 1;
        rep(j, 1, MAXC) {
            HASHPOW[i][j] = HASHPOW[i][j-1] * HASHP[i] % HASHM[i];
        }
    }
    pow2[0] = 1;
    rep(i, 1, MAXN) pow2[i] = pow2[i-1] * 2 % MOD;
    solve();
    return 0;
}