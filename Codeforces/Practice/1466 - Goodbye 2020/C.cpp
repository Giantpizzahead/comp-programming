#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i < (b); i++)
#define all(x) x.begin(), x.end()
#define sz(x) (int) (x.size())
using namespace std;
using ll = long long;
using vi = vector<int>;

const int MAXN = 1e5+5;

int N;
int A[MAXN];
string str;

void solve() {
    cin >> str;
    N = sz(str);
    rep(i, 0, N) {
        A[i] = str[i];
    }
    // Check for length 2 and length 3 palindromes
    int answer = 0;
    rep(i, 1, N) {
        if (A[i] == A[i-1]) {
            // Length 2 palindrome
            A[i] = -i;
            answer++;
        }
        if (i != 1 && A[i] == A[i-2]) {
            // Length 3 palindrome
            A[i] = -i;
            answer++;
        }
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T; cin >> T;
    rep(i, 0, T) solve();
    return 0;
}