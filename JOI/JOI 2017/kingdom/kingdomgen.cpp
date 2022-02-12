/*
Solution: 
Runtime: 
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

int randint(int a, int b) {
    return rand() % (b-a+1) + a;
}

void solve() {
    int H = randint(2, 10);
    int W = randint(2, 10);
    int P = randint(1, 30);
    int hDelta = randint(-50, 50);
    int wDelta = randint(-10, 10);
    cout << H << " " << W << "\n";
    rep(i, 0, H) rep(j, 0, W) {
        int x = randint(1, P) + hDelta*i + wDelta*j;
        cout << x << " \n"[j==W-1];
    }
}

int main(int argc, const char* argv[]) {
    srand(hash<const char*>()(argv[1]));
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}