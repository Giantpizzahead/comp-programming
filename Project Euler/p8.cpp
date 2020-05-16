#include <iostream>
#include <algorithm>

#define MAXN 1000

using namespace std;

int digits[MAXN];

int main() {
    int K = 13;

    for (int i = 0; i < MAXN; i++) {
        digits[i] = cin.get() - '0';
        if (digits[i] == '\n' - '0') i--;
    }

    long long answer = 1;

    long long product = 1;
    int numZeros = 0;
    for (int i = 0; i < K; i++) {
        int d = digits[i];
        if (d == 0) numZeros++;
        else product *= d;
    }

    if (numZeros == 0) answer = max(product, answer);

    for (int i = K; i < MAXN; i++) {
        int d = digits[i];
        if (d == 0) numZeros++;
        else product *= d;

        d = digits[i-K];
        if (d == 0) numZeros--;
        else product /= d;

        if (numZeros == 0) answer = max(product, answer);
    }

    cout << answer << endl;
}
