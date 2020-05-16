#include <iostream>
#define MAXN 5000000

using namespace std;

bool notPrime[MAXN];

int main() {
    notPrime[0] = true;
    notPrime[1] = true;

    for (int i = 2; i < 5000; i++) {
        if (!notPrime[i]) {
            for (int j = i * 2; j < MAXN; j += i) notPrime[j] = true;
        }
    }

    int primesFound = 0;
    for (int i = 2; i < MAXN; i++) {
        if (!notPrime[i]) {
            primesFound++;
            if (primesFound == 10001) cout << i << endl;
        }
    }
}
