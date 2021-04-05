#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>
#include <string>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;

const int MAXL = 21, MAXN = 1e6;

int N;
string S;

struct SuffixArr {
    int C[MAXN];
    int A[MAXN];

    struct Loc {
        int i, a, b;

        inline void set(Loc& l) {
            i = l.i;
            a = l.a;
            b = l.b;
        }

        inline bool equals(Loc& o) {
            return a == o.a && b == o.b;
        }
    };

    Loc locs[MAXN], locs2[MAXN];
    int cnt[MAXN];
    void countingsort(int A) {
        rep(i, 0, A) cnt[i] = 0;
        rep(i, 0, N) cnt[locs[i].a]++;
        rep(i, 1, A) cnt[i] += cnt[i-1];
        for (int i = N-1; i >= 0; i--) locs2[--cnt[locs[i].a]].set(locs[i]);
        rep(i, 0, N) locs[i].set(locs2[i]);
    }

    void init() {
        // Sort by first character
        rep(i, 0, N) {
            locs[i].i = i;
            locs[i].a = S[i];
        }
        countingsort(256);
        // rep(i, 0, N) cout << "(" << locs[i].i << "," << locs[i].a << "," << locs[i].b << ") ";
        // cout << endl;
        C[locs[0].i] = 0;
        int classes = 1;
        rep(i, 1, N) {
            if (!locs[i].equals(locs[i-1])) classes++;
            C[locs[i].i] = classes - 1;
        }
        // Sort by 2^(k+1) characters
        for (int k = 0, num = 1; num < N; k++, num*=2) {
            // Already sorted by 2nd half (radix sort)
            rep(i, 0, N) {
                locs[i].b = C[locs[i].i];
                locs[i].i -= 1 << k;
                if (locs[i].i < 0) locs[i].i += N;
                locs[i].a = C[locs[i].i];
            }
            countingsort(N);
            // rep(i, 0, N) cout << "(" << locs[i].i << "," << locs[i].a << "," << locs[i].b << ") ";
            // cout << endl;
            C[locs[0].i] = 0, classes = 1;
            rep(i, 1, N) {
                if (!locs[i].equals(locs[i-1])) classes++;
                C[locs[i].i] = classes - 1;
            }
            if (classes == N) break;  // Already sorted
        }
        // Gen suffix array
        rep(i, 0, N) A[i] = locs[i].i;
    }

    void print() {
        rep(i, 0, N) {
            cout << C[i] << ' ';
        }
        cout << endl;
        rep(i, 0, N) {
            cout << S.substr(A[i]) << endl;
        }
    }
} sarr;

void solve() {
    cin >> S;
    N = sz(S);
    sarr.init();
    // sarr.print();
    cout << S.substr(sarr.A[0]) << S.substr(0, sarr.A[0]) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}