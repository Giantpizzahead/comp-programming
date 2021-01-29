#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5, MAXS = 50, MAXV = 1e6;

int N;
int A[MAXN];
char O[MAXN];

struct Range {
    int v, i, c;
    bool is1;
};
vector<Range> ranges;

int bestVal;
string bestUsed;

void fillSymbols() {
    rep(i, 0, sz(bestUsed)) {
        rep(j, ranges[i*2+1].i - 1, ranges[i*2+1].i + ranges[i*2+1].c) {
            O[j] = bestUsed[i];
        }
    }
}

string used;
void bruteForce(int i, int v, int m) {
    if (i == ranges.size()) {
        v += m;
        if (v > bestVal) {
            bestVal = v;
            bestUsed = used;
        }
        return;
    }
    if (i % 2 == 0) {
        m *= ranges[i].v;
        bruteForce(i+1, v, m);
    } else {
        // Multiply
        used.push_back('*');
        bruteForce(i+1, v, m);
        used.pop_back();
        // Add
        used.push_back('+');
        bruteForce(i+1, v+m+ranges[i].c, 1);
        used.pop_back();
    }
}

void subproblem(int l, int r) {
    // Remove leading and trailing ones
    while (l <= r && A[l] == 1) {
        O[l] = '+';
        l++;
    }
    while (r >= l && A[r] == 1) {
        O[r-1] = '+';
        r--;
    }
    bool has1 = false;
    rep(i, l, r+1) {
        if (A[i] == 1) {
            has1 = true;
            break;
        }
    }
    if (!has1) {
        rep(i, l, r) O[i] = '*';
        return;
    }
    if (l >= r) return;
    // cout << "sub " << l << " " << r << ": ";
    // rep(i, l, r+1) cout << A[i] << ' ';
    // cout << endl;

    ranges.clear();
    Range curr = {1, l, 0, false};
    int totalMult = 1;
    rep(i, l, r+1) {
        if (A[i] != 1) {
            if (curr.is1) {
                ranges.push_back(curr);
                curr = {1, i, 0, false};
            }
            curr.v *= A[i];
            totalMult *= A[i];
            curr.c++;
            if (totalMult > MAXV) {
                // * must be better no matter what
                rep(i, l, r) O[i] = '*';
                return;
            }
        } else {
            if (!curr.is1) {
                ranges.push_back(curr);
                curr = {0, i, 0, true};
            }
            curr.v++;
            curr.c++;
        }
    }
    ranges.push_back(curr);

    // for (Range& r : ranges) {
    //     cout << "(" << r.v << "," << r.i << "," << r.c << "," << r.is1 << ") ";
    // }
    // cout << endl;

    bestVal = -1;
    bruteForce(0, 0, 1);
    fillSymbols();
}

void solve() {
    cin >> N;
    rep(i, 0, N) cin >> A[i];
    string str;
    cin >> str;
    
    sort(all(str));
    if (str == "+-") str = "+";
    if (str == "*+-") str = "+*";
    if (sz(str) == 1) {
        rep(i, 0, N) {
            cout << A[i];
            if (i != N-1) cout << str[0];
        }
        cout << '\n';
        return;
    } else if (str == "*-") {
        rep(i, 0, N) {
            cout << A[i];
            if (i != N-1) {
                if (A[i+1] == 0) cout << '-';
                else cout << '*';
            }
        }
        cout << '\n';
        return;
    }

    // Allowed operations: + and *
    rep(i, 0, N-1) {
        if (A[i] == 0 || A[i+1] == 0) O[i] = '+';
        else if (A[i] >= 2 && A[i+1] >= 2) O[i] = '*';
    }
    // Divide into subproblems
    int li = 0;
    rep(i, 0, N) {
        if (A[i] == 0) {
            subproblem(li, i-1);
            li = i+1;
        }
    }
    subproblem(li, N-1);
    rep(i, 0, N) {
        cout << A[i];
        if (i != N-1) cout << O[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}