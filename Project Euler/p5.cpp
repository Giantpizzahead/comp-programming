#include <iostream>

typedef long long ll;

using namespace std;

ll gcf(ll a, ll b) {
    if (a == 0) return b;
    else return gcf(b % a, a);
}

ll lcm(ll a, ll b) {
    return a * b / gcf(a, b);
}

int main() {
    ll N = 1;
    for (int i = 2; i <= 20; i++) N = lcm(N, i);
    cout << N << endl;
}
