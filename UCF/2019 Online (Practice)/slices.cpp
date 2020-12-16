#include <iostream>
using namespace std;
using ll = long long;

const int MAXN = 100005;

int N, K;
int l1, l2;
bool h1, h2;

void solve() {
    cin >> N >> K;
    l1 = 0;
    l2 = 0;
    h1 = false;
    h2 = false;
    string s;
    int l;
    for (int i = 0; i < N; i++) {
        cin >> s >> l;
        if (s == "Kelly") {
            l1 = l;
            if (l1 > l2 + K) h2 = true;
        } else {
            l2 = l;
            if (l2 > l1 + K) h1 = true;
        }
    }
    if (h1 && h2) cout << "Their friendship is doomed\n";
    else if (h1) cout << "Kelly hates Jim\n";
    else if (h2) cout << "Jim hates Kelly\n";
    else cout << "Everything is good\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}