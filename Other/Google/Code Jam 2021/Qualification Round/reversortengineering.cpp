#include <bits/stdc++.h>
using namespace std;

void reverse(vector<int>& vect, int i, int j) {
    if (i > j) return;
    int m = (j-i+1)/2;
    for (int k = 0; k < m; k++) {
        swap(vect[i+k], vect[j-k]);
    }
}

vector<int> genArr(int N, int C) {
    // cout << "gen(" << N << ", " << C << ")\n";
    if (C < 0) return vector<int>(0);
    if (N == 1) {
        if (C != 0) return vector<int>(0);
        vector<int> vect(1);
        vect[0] = 0;
        return vect;
    }
    vector<int> vect(N);
    if (N <= C) {
        // Go as far as possible
        vect[N-1] = 0;
        vector<int> innerVect = genArr(N-1, C-(N-1));
        if (innerVect.empty()) return innerVect;
        reverse(innerVect, 0, N-2);
        for (int i = 0; i < N-1; i++) vect[i] = innerVect[i]+1;
    } else {
        // The rest can be sorted
        int x = 1;
        for (int i = 0; i < N; i++) {
            if (i == C) vect[i] = 0;
            else vect[i] = x++;
        }
        reverse(vect, 0, C-1);
    }
    return vect;
}

void solve() {
    int N, C; cin >> N >> C;
    C -= N-1;
    vector<int> res = genArr(N, C);
    if (res.empty()) cout << " IMPOSSIBLE";
    else for (int x : res) cout << ' ' << x+1;
    cout << '\n';
}

int main() {
    int T; cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Case #" << i << ":";
        solve();
    }
}