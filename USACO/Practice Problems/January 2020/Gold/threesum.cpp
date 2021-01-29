#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 5000, MAXC = 4e6+10, OFF = 2e6+5;

int N, Q;
int A[MAXN];
ll R[MAXN][MAXN];

int cnt[MAXC];
vector<int> added;
void fillR(int l) {
    for (int i = l+1; i < N; i++) {
        // Query
        R[l][i] = cnt[A[i] + OFF];
        // Add
        int target = -(A[l] + A[i]);
        added.push_back(target + OFF);
        cnt[target + OFF]++;
    }
    for (int x : added) cnt[x]--;
    added.clear();
}

void solve() {
    cin >> N >> Q;
    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) {
        fillR(i);
    }
    for (int sz = 1; sz < N; sz++) {
        for (int i = 0; i < N; i++) {
            int j = i+sz;
            if (j >= N) break;
            R[i][j] += R[i+1][j] + R[i][j-1] - R[i+1][j-1];
        }
    }
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        cout << R[l][r] << '\n';
    }
}

int main() {
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
    cout.flush();
    fclose(stdin);
    fclose(stdout);
    return 0;
}