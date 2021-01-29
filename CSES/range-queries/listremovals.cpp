#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+5, MAXBIT = 1 << 18;

int N;
int X[MAXN];

struct BIT {
    int V[MAXBIT + 1];

    void update(int i, int v) {
        while (i <= MAXBIT) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query(int v) {
        int i = 0, s = MAXBIT;
        while (s > 0) {
            if (V[i+s] < v) {
                v -= V[i+s];
                i += s;
            }
            s /= 2;
        }
        return i+1;
    }
};

BIT bit;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        bit.update(i+1, 1);
    }
    // cout << endl << "bit: ";
    // for (int j = 1; j <= N; j++) cout << bit.query(j) << ' ';
    // cout << endl;
    int p;
    for (int i = 0; i < N; i++) {
        cin >> p;
        p = bit.query(p);
        if (i != 0) cout << ' ';
        cout << X[p-1];
        bit.update(p, -1);
        // cout << endl << "bit: ";
        // for (int j = 1; j < N-i; j++) cout << bit.query(j) << ' ';
        // cout << endl;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}