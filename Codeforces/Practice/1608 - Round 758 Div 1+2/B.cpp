#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;
using namespace std;

const int MAXN = 1e5+5;

int N, A, B;
int res[MAXN];

void solve() {
    cin >> N >> A >> B;
    if (A == 0 && B == 0) {
        rep(i, 0, N) cout << i+1 << " \n"[i==N-1];
        return;
    }
    bool toRev = false;
    if (A > B) {
        swap(A, B);
        toRev = true;
    }
    int lowNum = N / 2;
    int highNum = N / 2 + 1;
    int currA = 0, currB = 0;
    rep(i, 0, N) {
        if (i % 2 == 0) {
            res[i] = highNum;
            highNum++;
            if (i != 0 && i != N-1) currA++;
            if (currA == A && currB == B) {
                // Fill out the rest in order
                for (int j = N; j >= highNum; j--) {
                    i++;
                    res[i] = j;
                }
                for (int j = lowNum; j >= 1; j--) {
                    i++;
                    res[i] = j;
                }
                assert(i == N-1);
                break;
            }
        } else {
            res[i] = lowNum;
            lowNum--;
            if (i != N-1) currB++;
            if (currA == A && currB == B) {
                // Fill out the rest in order
                for (int j = 1; j <= lowNum; j++) {
                    i++;
                    res[i] = j;
                }
                for (int j = highNum; j <= N; j++) {
                    i++;
                    res[i] = j;
                }
                assert(i == N-1);
                break;
            }
        }
    }
    if (toRev) rep(i, 0, N) res[i] = (N+1) - res[i];

    if (currA == A && currB == B) rep(i, 0, N) cout << res[i] << " \n"[i==N-1];
    else cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}