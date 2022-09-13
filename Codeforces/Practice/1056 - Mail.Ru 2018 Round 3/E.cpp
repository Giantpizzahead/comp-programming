/*
https://codeforces.com/contest/1056/problem/E

Solution: There are only at most M/N pairs to check. Check each pair in O(N) time using hashing.
Runtime: O(M)
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

typedef uint64_t ull;
static int C; // initialized below

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x=0) : x(x), b(x) {}
	A(int x, B b) : x(x), b(b) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() { return x ^ (ull) b << 21; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(sz(str)+1), pw(ha) {
		pw[0] = 1;
		rep(i,0,sz(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b)
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
	if (sz(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,sz(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){H h{}; for(char c:s) h=h*C+c;return h;}

int N, M;
string S, T;

void solve() {
    cin >> S >> T;
    N = sz(S), M = sz(T);
    int num0 = 0;
    if (S[0] == '1') rep(i, 0, N) S[i] = (S[i] == '0' ? '1' : '0');
    int firstOne = -1;
    rep(i, 0, N) {
        if (S[i] == '0') num0++;
        else if (firstOne == -1) firstOne = i;
    }
    int num1 = N - num0;
    HashInterval hi(T);
    int ans = 0;
    rep(a, 1, M+1) {
        if (num0 * a > M) break;
        int b = (M - num0 * a) / num1;
        if (b <= 0 || (ll)a*num0 + (ll)b*num1 != M) continue;
        H h0 = hi.hashInterval(0, a);
        H h1 = hi.hashInterval(firstOne*a, firstOne*a+b);
        bool works = true;
        if (a == b && (ull)h0 == (ull)h1) works = false;
        int i = 0;
        rep(j, 0, N) {
            if (S[j] == '0') {
                if ((ull)h0 != (ull)hi.hashInterval(i, i+a)) {
                    works = false;
                    break;
                }
                i += a;
            } else {
                if ((ull)h1 != (ull)hi.hashInterval(i, i+b)) {
                    works = false;
                    break;
                }
                i += b;
            }
        }
        if (works) ans++;
    }
    cout << ans << '\n';
}

#include <sys/time.h>
int main() {
    timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);

    ios::sync_with_stdio(0);
    cin.tie(0);
    cin.exceptions(cin.failbit);
    solve();
    return 0;
}