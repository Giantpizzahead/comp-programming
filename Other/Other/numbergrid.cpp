/*
0 1 2 3 4 5
1 0 3 2 5 4
2 3 0 1 6 7
3 2 1 0 7 6
4 5 6 7 0 1
5 4 7 6 1 0

Recursive approach
12
21
Splits into smaller half with 1s, bigger half with 2s
*/

#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXC = 1 << 30;
int Y, X;

void solve(int i, int j, int c, int is, int js, int cs) {
    // Is the target in this box?
    if (Y < i || Y >= i+is || X < j || X >= j+js) return;
    cout << i << " " << j << " " << c;
    // Is this box the answer?
    if (is == 1 && js == 1) {
        cout << cs << '\n';
        return;
    }
    // Smaller halfs
    solve(i, j, c, is/2, js/2, cs/2);
    solve(i+is/2, j+js/2, c, is/2, js/2, cs/2);
    // Larger halfs
    solve(i+is/2, j, c+cs/2, is/2, js/2, cs/2);
    solve(i, j+js/2, c+cs/2, is/2, js/2, cs/2);
}

void solve() {
    cin >> Y >> X;
    Y--, X--;
    solve(0, 0, 0, MAXC, MAXC, MAXC);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}