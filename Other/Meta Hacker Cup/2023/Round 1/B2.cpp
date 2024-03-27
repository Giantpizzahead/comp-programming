#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()

int P;
vector<int> arr;

int bestLen;
vector<int> bestArr;
bool isDone;

void genArray(int p, int s, int prevMult) {
    // cerr << "on " << p << " " << s << endl;
    if (p == 1) {
        // Done, need to add to sum
        int num1 = 41 - s;
        int cnt = sz(arr) + num1;
        if (cnt < bestLen) {
            bestLen = cnt;
            bestArr = arr;
            rep(i, 0, num1) bestArr.push_back(1);
            // isDone = true;
        }
    } else {
        // Try multiples
        for (int x = prevMult; x >= 2; x--) {
            if (p % x != 0) continue;
            int np = p / x, ns = s + x;
            if (ns > 41) continue;
            arr.push_back(x);
            genArray(np, ns, x);
            if (isDone) return;
            arr.pop_back();
        }
    }
}

void solve() {
    cin >> P;
    bestLen = 99999;
    isDone = false;
    bestArr.clear();
    arr.clear();
    genArray(P, 0, 41);

    if (bestLen == 99999) cout << -1 << "\n";
    else {
        cout << bestLen << " ";
        sort(all(bestArr));
        rep(i, 0, sz(bestArr)) cout << bestArr[i] << " \n"[i==sz(bestArr)-1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    freopen("b.txt", "r", stdin);
    freopen("b.out", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}
