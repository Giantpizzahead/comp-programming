#include <iostream>
#include <math.h>

#define MAXN 2000000

using namespace std;

bool isPrime[MAXN];

int main() {
    for (int i = 2; i < MAXN; i++) isPrime[i] = true;

    for (int i = 2; i < (int) (sqrt(MAXN) + 2); i++) {
        if (isPrime[i]) {
            for (int j = i * 2; j < MAXN; j += i) isPrime[j] = false;
        }
    }

    long long sum = 0;
    for (int i = 2; i < MAXN; i++) if (isPrime[i]) sum += i;

    cout << sum << endl;
    return 0;
}
