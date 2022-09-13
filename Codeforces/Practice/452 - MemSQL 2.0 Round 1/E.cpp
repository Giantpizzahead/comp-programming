/*
https://codeforces.com/contest/452/problem/E

Solution: Suffix array magic!
(Any shared substrings will appear consecutively in the suffix array, which lets you do some efficient counting
techniques with prefix sums and math.)
Runtime: O(N * log(N)) where N is the sum of the lengths of all strings

Notes:
Say L=1
Sum for each letter, (# of that in a) * (# of that in b) * (# of that in c)

Any matches of any length L would be grouped together, possibly with matches from the same string
a... 1
a... 2
*/

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;

struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string& s, int lim=256) { // or basic_string<int>
		int n = sz(s) + 1, k = 0, a, b;
		vi x(all(s)+1), y(n), ws(max(n, lim)), rank(n);
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		rep(i,1,n) rank[sa[i]] = i;
		for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
			for (k && k--, j = sa[rank[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

const int MAXN = 3e5+10;

int N;
string A, B, C, S;
int preA[MAXN], preB[MAXN], preC[MAXN], lcp[MAXN];
ll ans[MAXN];

// All inclusive
void addToAnswer(int pi, int pj, int li, int lj) {
    ll numA = preA[lj] - (li == 0 ? 0 : preA[li-1]);
    ll numB = preB[lj] - (li == 0 ? 0 : preB[li-1]);
    ll numC = preC[lj] - (li == 0 ? 0 : preC[li-1]);
    ll ways = numA * numB * numC;
    ans[pj] += ways;
    ans[pi-1] -= ways;
    // cout << "add " << pi << " " << pj << " " << li << " " << lj << " = " << ways << endl;
}

void solve() {
    cin >> A >> B >> C;
    S = A + '#' + B + '$' + C + '%';
    N = sz(S);
    SuffixArray sarr(S);
    // cout << S << '\n';
    int M = 0;
    rep(i, 0, N+1) {
        int loc = sarr.sa[i];
        if (loc == sz(A) || loc == sz(A)+sz(B)+1 || loc >= sz(A)+sz(B)+sz(C)+2) continue;
        // Which string is this suffix from?
        if (loc < sz(A)) preA[M]++;
        else if (loc < sz(A)+sz(B)+1) preB[M]++;
        else preC[M]++;
        lcp[M] = sarr.lcp[i];
        M++;
    }
    lcp[M] = 0;
    M++;
    rep(i, 1, M) {
        preA[i] += preA[i-1];
        preB[i] += preB[i-1];
        preC[i] += preC[i-1];
    }

    vector<int> currPre, currLoc;
    currPre.push_back(0);
    currLoc.push_back(0);
    rep(i, 1, M) {
        if (lcp[i] > currPre.back()) {
            currPre.push_back(lcp[i]);
            currLoc.push_back(i-1);
        } else if (lcp[i] < currPre.back()) {
            int newLoc = i-1;
            while (lcp[i] < currPre.back()) {
                newLoc = currLoc.back();
                addToAnswer(max(lcp[i], currPre[sz(currPre)-2]) + 1, currPre.back(), currLoc.back(), i-1);
                currPre.pop_back();
                currLoc.pop_back();
            }
            if (lcp[i] > currPre.back()) {
                currPre.push_back(lcp[i]);
                currLoc.push_back(newLoc);
            }
        }
    }
    int res = min(min(sz(A), sz(B)), sz(C));
    for (int i = res; i >= 0; i--) ans[i] += ans[i+1];
    rep(i, 1, res+1) cout << ans[i] % 1000000007 << " \n"[i==res];

    // rep(i, 0, M) cout << preA[i] << " \n"[i==M-1];
    // rep(i, 0, M) cout << preB[i] << " \n"[i==M-1];
    // rep(i, 0, M) cout << preC[i] << " \n"[i==M-1];
    // cout << " ";
    // rep(i, 1, M) cout << lcp[i] << " \n"[i==M-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}