/**
 * Problem link:
 * https://codeforces.com/group/hosRkEuluH/contest/423073/problem/I
 * 
 * Solution:
 * Optimal journey can always be turned into one with string lengths 4 -> 3 -> 2 -> 1 (-1 each time).
 * That means the max possible journey length is sqrt(N) ~ 700.
 * 
 * Say you're at a string T. The next optimal string must be L + T or T + L, where L is a lowercase letter.
 * 
 * A simple DP for this would be as follows:
 * dp[i][k] = Whether it's possible to end a journey at index i with current string length k
 * Trans:
 * dp[i][k] comes from dp[i+1...N-1][k-1], where the new substring is missing either the first or last character.
 * O(NsqrtN) works kinda, but actual # of states to consider is quite a bit smaller
 * But transitions take a long time... even with hashing, it's O(N) per trans naively
 * 
 * Some key things to note:
 * Keeping track of prefixes seen seems like a good idea
 * We only need to check if at least one match exists (or not), do not need to iterate over all!
 * 
 * Also, if dp[i][k] is possible, that means all substrings within that range are possible too (easier to make)
 * that is, dp[i+n][k] or dp[i][k-n] are also true for n < k
 * That suggests some binary search would work for transitions (fix i, what's the biggest k that works?)
 * 
 * Say we have a suffix array. That is, an array of the sorted suffixes (or at least starting indices) for S.
 * LCP array (longest common prefix) is applicable to each of the adjacent suffixes in this array.
 * 
 * To process dp[i][k], find the location of suffix i. Then, find the contiguous range with at least k-1 matching chars
 * in the prefix. If at least one of these has a value >= k-1, then dp[i][k] works. Repeat this for removing the first
 * character.
 * 
 * A suffix array with LCP + some sort of fast range query structure can find the required index range in log(N) time.
 * Finding the maximum in a range is also log(N) time. Setting a specific place (dp[i][k]) is log(N) with a seg tree.
 * There are log(N) checks for each of the N states.
 * 
 * Overall, complexity is O(N * log(N)^2) which is reasonable for a 5 second time limit.
 */

// ============================== BEGIN TEMPLATE ==============================
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#ifdef LOCAL
    #include "pprint.hpp"
#else
    #define debug(...) 42
    #define dumpVars(...) 42
#endif

void solve();

int runTests(bool multiple_tests) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    if (multiple_tests) {
        int T; cin >> T;
        rep(i, 0, T) solve();
    } else solve();
    return 0;
}
// =============================== END TEMPLATE ===============================

// ===============================   KACTL   ===============================
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	rep(it,0,2) {
		int move = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		rep(i,0,sz(b))
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(b.size());
		rep(i,0,sz(b))
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vi a;
	string s;
	SuffixArray(const string& _s) : s(_s + '\0') {
		int N = sz(s);
		vector<pli> b(N);
		a.resize(N);
		rep(i,0,N) {
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			rep(i,1,N)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= N) break;
			rep(i,0,N) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		rep(i,0,sz(a)) a[i] = b[i].second;
	}
	vi lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		int n = sz(a), h = 0;
		vi inv(n), res(n);
		rep(i,0,n) inv[a[i]] = i;
		rep(i,0,n) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};
// =============================== END KACTL ===============================

void solve() {
	// int N; cin >> N;
    // string S; cin >> S;
	int N = 7;
	string S = "abcdbcc";
	SuffixArray sarr(S);
	dumpVars(sarr.a);
	dumpVars(sarr.lcp());
}

int main() {
    bool multipleTests = false;
    return runTests(multipleTests);
}
