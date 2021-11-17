// https://codeforces.com/contest/1557/problem/A

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

void solve() {
    int N; cin >> N;
    vector<int> V;
    double sum = 0;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        V.push_back(x);
        sum += x;
    }
    int m = *max_element(V.begin(), V.end());
    sum -= m;
    cout << m + sum / (N-1) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(9);
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
    return 0;
}