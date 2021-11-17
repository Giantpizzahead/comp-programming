#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define sz(x) ((int) x.size())
#define all(x) x.begin(), x.end()
#define debug if (true) cerr
using ll = long long;

const int MAXN = 10;
int N, Q;

bool query(int a, int b) {
    assert(Q > 0);
    Q--;
    cout << "? " << (char) (a+'A') << " " << (char) (b+'A') << endl;
    char resp; cin >> resp;
    return resp == '>';
}

vector<vector<int>> perms;
int used[MAXN];
vector<int> currPerm;

void bruteForce() {

}

void genPerms(int i) {
    if (i == N) perms.push_back(currPerm);
    else rep(j, 0, N) {
        if (!used[j]) {
            used[j] = true;
            currPerm.push_back(j);
            genPerms(i+1);
            currPerm.pop_back();
            used[j] = false;
        }
    }
}

bool bruteForce(int target, vector<vector<int>> P, bool real = false) {
    // cout << target << " " << sz(P) << endl;
    if (sz(P) == 1) {
        if (real) {
            cout << "! ";
            for (int x : P[0]) cout << (char) (x+'A');
            cout << endl;
        }
        return true;
    } else if (target == 0) return false;
    // Try asking about all pairs
    rep(i, 0, N) {
        rep(j, i+1, N) {
            vector<vector<int>> p1, p2;
            for (vector<int>& p : P) {
                for (int k : p) {
                    if (k == i) {
                        // i < j
                        p1.push_back(p);
                        break;
                    } else if (k == j) {
                        // i > j
                        p2.push_back(p);
                        break;
                    }
                }
            }
            // Good heuristic
            if (p1.empty() || p2.empty() || abs(sz(p1) - sz(p2)) > 1) continue;
            if (!bruteForce(target-1, p1)) continue;
            if (!bruteForce(target-1, p2)) continue;

            // Found a good query to use
            if (real) {
                // cout << "sizes " << sz(p1) << " and " << sz(p2) << endl;
                if (!query(i, j)) {
                    // i < j
                    bruteForce(target-1, p1, true);
                } else {
                    // i > j
                    bruteForce(target-1, p2, true);
                }
            }
            return true;
        }
    }
    // No optimal query sequence found
    return false;
}

void solveSmall() {
    genPerms(0);
    /*
    for (auto& p : perms) {
        for (int x : p) cout << x << ' ';
        cout << endl;
    }
    */
    vector<vector<int>> P = perms;
    bruteForce(Q, P, true);
}

vector<int> solve(int l, int r) {
    if (l == r) {
        vector<int> nums;
        nums.push_back(l);
        return nums;
    }
    vector<int> left = solve(l, (l+r)/2);
    vector<int> right = solve((l+r)/2+1, r);
    int li = 0, ri = 0;
    vector<int> nums;
    while (li != sz(left) && ri != sz(right)) {
        bool res = query(left[li], right[ri]);
        // int dl = sz(left)-li, dr = sz(right)-ri;
        // bool res = (dl < dr);
        // Q--;
        if (res) nums.push_back(right[ri++]);
        else nums.push_back(left[li++]);
    }
    while (li != sz(left)) nums.push_back(left[li++]);
    while (ri != sz(right)) nums.push_back(right[ri++]);
    return nums;
}

void solve() {
    cin >> N >> Q;
    if (N <= 10) {
        solveSmall();
    } else {
        vector <int> ans = solve(0, N-1);
        cout << "! ";
        for (int x : ans) cout << (char) (x+'A');
        cout << endl;
        // cout << "queries left: " << Q << endl;
    }
}

int main() {
    solve();
    return 0;
}