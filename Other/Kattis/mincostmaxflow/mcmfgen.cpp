#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int randInt(int a, int b) {
    return rand() % (b-a+1) + a;
}

int N, M, S, T;

void solve() {
    N = randInt(2, 20);
    M = randInt(0, 50);
    while (S == T) {
        S = randInt(0, N-1);
        T = randInt(0, N-1);
    }
    cout << N << " " << M << " " << S << " " << T << "\n";
    rep(i, 0, M) {
        int u = randInt(0, N-1);
        int v = randInt(0, N-1);
        int c = randInt(1, 1000);
        int w = randInt(1, 100);
        cout << u << " " << v << " " << c << " " << w << "\n";
    }
}

int main(int argc, const char* argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cout << "argc = " << argc << endl;
    // cout << "args:" << endl;
    // rep(i, 0, argc) cout << argv[i] << endl;
    if (argc > 1) srand(hash<string>()(string(argv[1])));
    solve();
    return 0;
}