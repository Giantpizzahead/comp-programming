#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int D, I;
int A[10];
bool used[10], isFilled[10];
vector<int> works[10];
unordered_map<int, bool> memo;

int createNum() {
    int num = 0;
    for (int i = 0; i < D; i++) {
        num *= 10;
        num += A[i];
    }
    return num;
}

int modpow(ll b, ll e, ll m) {
    ll r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        b = b * b % m;
        e /= 2;
    }
    return r;
}

bool isPrime(int n) {
    if (memo.find(n) != memo.end()) return memo[n];
    for (int iter = 0; iter < 8; iter++) {
        int b = rand() % (n-3) + 2;
        if (modpow(b, n-1, n) != 1) {
            memo[n] = false;
            return false;
        }
    }
    // for (int i = 2; i*i <= n; i++) {
    //     if (n % i == 0) return false;
    // }
    memo[n] = true;
    return true;
}

bool testNum(int n) {
    // cout << n << endl;
    if (n < 10) return n == 2 || n == 3 || n == 5;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0) return false;
    if (!isPrime(n)) return false;
    n += 2;
    if (!isPrime(n)) return false;
    // cout << n << endl;
    return true;
}

void genNum(int x) {
    if (x == D) {
        int num = createNum();
        if (testNum(num)) {
            works[D].push_back(num);
        }
        return;
    }
    for (int i = 0; i < 10; i++) {
        if (!used[i] && (i != 0 || x != 0)) {
            used[i] = true;
            A[x] = i;
            genNum(x+1);
            used[i] = false;
        }
    }
}

void solve() {
    cin >> D >> I;
    if (D >= 10) {
        cout << "Brice doesn't stand a chance!\n";
        return;
    }
    if (!isFilled[D]) {
        isFilled[D] = true;
        genNum(0);
    }
    if (works[D].size() < I) cout << "Brice doesn't stand a chance!\n";
    else cout << works[D][I-1] << '\n';
}

int main() {
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++) {
        solve();
    }
    return 0;
}