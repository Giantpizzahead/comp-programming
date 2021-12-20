#include <iostream>
using namespace std;
using ll = long long;

ll N, A, B;

void solve() {
    cin >> N >> A >> B;
    if (A == B) {
        cout << "0\n";
        return;
    }
    if (N % 2 == 0) {
        // 2 simple cycles
        if (A % 2 != B % 2) {
            cout << "Impossible\n";
            return;
        } else {
            if (A > B) swap(A, B);
            ll dist = (B-A)/2;
            dist = min(dist, N/2 - dist);
            cout << dist << "\n";
            return;
        }
    } else {
        // One big cycle
        if (A % 2 == B % 2) {
            if (A > B) swap(A, B);
            ll dist = (B-A)/2;
            dist = min(dist, N - dist);
            cout << dist << "\n";
            return;
        } else {
            // Loop from even to odd
            if (A % 2 == 1) swap(A, B);
            ll dist = (N+1-A)/2;
            A = 1;
            dist += (B-A)/2;
            dist = min(dist, N - dist);
            cout << dist << "\n";
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        cout << "Graph #" << i << ": ";
        solve();
    }
    return 0;
}