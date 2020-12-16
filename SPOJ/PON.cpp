#include <iostream>
#include <random>
#include <ctime>
using namespace std;
using ll = long long;

__int128_t powmod(__int128_t b, ll e, __int128_t m) {
    __int128_t r = 1;
    while (e > 0) {
        if (e % 2 == 1) r = r * b % m;
        e /= 2;
        b = b * b % m;
    }
    return r;
}

bool isPrimeFermat(ll n, int iters) {
    if (n <= 4) return n == 2 || n == 3;
    // Test using Fermat's little theorem with random bases
    for (int i = 0; i < iters; i++) {
        ll b = rand() % (n-2) + 2;
        if (powmod(b, n-1, n) != 1) return false;
    }
    return true;
}

bool isPrimeSlow(int n) {
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    srand(time(NULL));
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        ll N;
        cin >> N;
        if (isPrimeFermat(N, 20)) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    /*
    for (int i = 2; i <= 1000; i++) {
        if (isPrimeFermat(i, 5)) {
            if (isPrimeSlow(i)) cout << i << " prime" << endl;
            else cout << i << " NOT prime" << endl;
        } else if (isPrimeSlow(i)) cout << i << " MISSED prime" << endl;
    }
    */
    return 0;
}