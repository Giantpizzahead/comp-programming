#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 4e5+5;

int N, answer;
struct Pair {
    int a, b, id;
};
Pair C[MAXN];
int id[MAXN];
// 1 = Negative, 2 = Positive, 3 = Unknown
int status[MAXN];
bool flipped[MAXN];

void solve(int l, int r) {
    if (l > r) return;
    // cout << "solve " << l << " " << r << endl;
    // Check outermost card, continue going inward until balanced
    if (C[id[l]].b != r) {
        int numStay = 0, numFlip = 0;
        // Positive; check inner
        status[id[l]] = 2;
        if (!flipped[id[l]]) numStay++;
        else numFlip++;
        int inL = l, inR = C[id[l]].b;
        l++;
        while (l <= inL || r >= inR) {
            // cout << l << ' ' << inL << ' ' << inR << ' ' << r << endl;
            if (l <= inL) {
                // Positive (on left side)
                if (status[id[l]] == 0) {
                    // cout << "extend l\n";
                    inR = min(C[id[l]].b, inR);
                    status[id[l]] = 2;
                    if (!flipped[id[l]]) numStay++;
                    else numFlip++;
                }
                l++;
            } else {
                // Negative (on right side)
                if (status[id[r]] == 0) {
                    // cout << "extend r\n";
                    inL = max(C[id[r]].a, inL);
                    status[id[r]] = 1;
                    if (flipped[id[r]]) numStay++;
                    else numFlip++;
                }
                r--;
            }
        }
        // Recurse
        answer += min(numFlip, numStay);
        solve(inL+1, inR-1);
    } else {
        // Outmost is unknown
        status[id[l]] = 3;
        solve(l+1, r-1);
    }
}

void solve() {
    cin >> N;
    rep(i, 0, N) {
        cin >> C[i].a >> C[i].b;
        C[i].a--, C[i].b--;
        C[i].id = i;
        id[C[i].a] = i;
        id[C[i].b] = i;
        if (C[i].a > C[i].b) {
            flipped[i] = true;
            swap(C[i].a, C[i].b);
        }
        if (C[i].a >= N || C[i].b < N) {
            cout << "-1\n";
            return;
        }
    }
    answer = 0;
    solve(0, 2*N-1);
    // rep(i, 0, N) cout << status[i] << ' ';
    // cout << endl;
    // Try sorting with correct rotations to see if it works
    rep(i, 0, N) if (status[i] == 1) swap(C[i].a, C[i].b);
    sort(C, C+N, [](const Pair& a, const Pair& b) {
        return a.a < b.a;
    });
    // cout << "testsort:\n";
    // rep(i, 0, N) cout << C[i].a << ' ';
    // cout << endl;
    // rep(i, 0, N) cout << C[i].b << ' ';
    // cout << endl;
    rep(i, 1, N) {
        if (C[i-1].a > C[i].a || C[i-1].b < C[i].b) {
            cout << "-1\n";
            return;
        }
    }
    // This works
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}