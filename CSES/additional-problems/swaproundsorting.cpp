#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAXN = 2e5+1;

int N;
int A[MAXN], vToI[MAXN];
bool used[MAXN];
vector<pair<int, int>> swaps;

void doSwap(int i, int j) {
    // cout << "swap " << i << " " << j << endl;
    used[i] = true;
    used[j] = true;
    swaps.emplace_back(min(i, j), max(i, j));
    swap(vToI[A[i]], vToI[A[j]]);
    swap(A[i], A[j]);
}

void solve() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        vToI[A[i]] = i;
    }

    // Is the array already sorted?
    bool sorted = true;
    for (int i = 1; i <= N; i++) {
        if (A[i] != i) {
            sorted = false;
            break;
        }
    }
    if (sorted) {
        cout << "0\n";
        return;
    }

    // Do one round
    bool oneRound = true;
    for (int i = 1; i <= N; i++) {
        if (used[i] || A[i] == i) {
            used[i] = true;
            continue;
        }
        // Move correct element here
        int j = vToI[i];
        if (used[j]) {
            oneRound = false;
            continue;
        }
        doSwap(i, j);
        while (true) {
            // Move correct element to next location
            int x = A[j];
            if (A[x] == j) break;  // Ready for next round
            oneRound = false;
            // Must move right element here
            int y = vToI[j];
            doSwap(x, y);
            j = y;
        }
    }
    // cout << "arr: ";
    // for (int i = 1; i <= N; i++) cout << A[i] << ' ';
    // cout << endl;

    if (oneRound) {
        cout << "1\n";
        cout << swaps.size() << '\n';
        for (auto p : swaps) cout << p.first << ' ' << p.second << '\n';
        return;
    }

    // Do second round
    cout << "2\n";
    cout << swaps.size() << '\n';
    for (auto p : swaps) cout << p.first << ' ' << p.second << '\n';

    for (int i = 1; i <= N; i++) used[i] = false;
    swaps.clear();
    for (int i = 1; i <= N; i++) {
        if (used[i] || A[i] == i) {
            used[i] = true;
            continue;
        }
        // Move correct element here
        int j = vToI[i];
        doSwap(i, j);
    }
    // cout << "arr: ";
    // for (int i = 1; i <= N; i++) cout << A[i] << ' ';
    // cout << endl;

    cout << swaps.size() << '\n';
    for (auto p : swaps) cout << p.first << ' ' << p.second << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}