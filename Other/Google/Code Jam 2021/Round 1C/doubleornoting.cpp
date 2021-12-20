#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int INF = 1e9;

int specialCase = 0, answer;

string A, B;
struct Range {
    int t, c;
};
vector<Range> N, M;

void matchAt(int K) {
    cerr << "matchAt(" << K << ")";
    int ai = K, bi = 0, toExtend = 0;
    while (ai < sz(N)) {
        assert(bi < sz(M));
        if (N[ai].c != M[bi].c) {
            if (ai == sz(N)-1 && N[ai].c < M[bi].c) {
                // Final one; can extend
                toExtend = M[bi].c - N[ai].c;
            } else return;  // Not possible
        }
        ai++, bi++;
    }
    // Works
    int currAns = K + toExtend;
    while (bi < sz(M)) {
        currAns += M[bi].c;
        bi++;
    }
    cerr << " = " << currAns;
    answer = min(currAns, answer);
}

void solve() {
    cin >> A >> B;
    cerr << endl;
    // Special case for equal
    if (A == B) {
        cout << 0 << '\n';
        return;
    }
    // Special case for starting
    if (A == "0") {
        specialCase = 1;
        A = "1";
    } else specialCase = 0;
    A += ".";
    B += ".";
    N.clear();
    M.clear();
    int t = A[0], c = 0;
    rep(i, 0, sz(A)) {
        if (A[i] == t) c++;
        else {
            N.push_back({t-'0', c});
            t = A[i];
            c = 1;
        }
    }
    t = B[0], c = 0;
    rep(i, 0, sz(B)) {
        if (B[i] == t) c++;
        else {
            M.push_back({t-'0', c});
            t = B[i];
            c = 1;
        }
    }
    // Special case for ending
    if (B == "0.") {
        assert(A != "0.");
        cout << sz(N) << '\n';
        return;
    }
    // Normal case
    answer = INF;
    rep(i, 0, sz(N)) {
        matchAt(i);
        cerr << endl;
    }
    cout << specialCase + answer << '\n';

    // for (Range& r : N) cout << r.c << " " << r.t << ", ";
    // cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int T; cin >> T;
    rep(i, 0, T) {
        cout << "Case #" << i+1 << ": ";
        solve();
    }
    return 0;
}