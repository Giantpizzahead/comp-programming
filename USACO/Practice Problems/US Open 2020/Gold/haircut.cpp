#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 1e5+5;

int N;
vector<int> locs[MAXN];
int A[MAXN];
ll answers[MAXN];

struct BIT {
    int V[MAXN];

    void upd(int i, int v) {
        i++;
        while (i < MAXN) {
            V[i] += v;
            i += i & -i;
        }
    }

    int query(int i) {
        i++;
        int R = 0;
        while (i > 0) {
            R += V[i];
            i -= i & -i;
        }
        return R;
    }
};

BIT bit;

void solve() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        locs[A[i]].push_back(i);
        bit.upd(i, 1);
    }

    for (int i = 1; i < N; i++) {
        answers[i] = answers[i-1];
        for (int j : locs[i-1]) {
            answers[i] += bit.query(j-1);
            bit.upd(j, -1);
        }
    }

    for (int i = 0; i < N; i++) cout << answers[i] << '\n';
}

int main() {
    freopen("haircut.in", "r", stdin);
    freopen("haircut.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}