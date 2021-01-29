#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;

const int MAXN = 5005;

int N;
struct Point {
    int x, y, id;
};
Point P[MAXN];

bool angleCheck(int i, int j, int k) {
    ll dot = (ll) (P[i].x - P[j].x) * (P[k].x - P[j].x) + (ll) (P[i].y - P[j].y) * (P[k].y - P[j].y);
    return dot > 0;
}

bool check() {
    // Swap if invalid
    rep(i, 0, N-2) {
        if (!angleCheck(i, i+1, i+2)) {
            // Try to swap out first
            bool found = false;
            rep(j, i+3, N) {
                swap(P[i+2], P[j]);
                if (angleCheck(i, i+1, i+2)) {
                    found = true;
                    break;
                }
                swap(P[i+2], P[j]);
            }
            if (found) continue;

            // Swap points
            swap(P[i+1], P[i+2]);
            assert(angleCheck(i, i+1, i+2));
            if (!angleCheck(i-1, i, i+1)) return false;
        }
    }
    return true;
}

void solve() {
    srand(time(NULL));
    cin >> N;
    rep(i, 0, N) {
        cin >> P[i].x >> P[i].y;
        P[i].id = i+1;
    }

    while (true) {
        random_shuffle(P, P+N);
        if (check()) break;
    }

    rep(i, 0, N) {
        if (i != 0) cout << ' ';
        cout << P[i].id;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    return 0;
}