#include <iostream>
#include <math.h>

#define MAXN 99999999

using namespace std;

bool isPrime[MAXN];

bool checkPrime(int n) {
    int sqrtN = sqrt(n) + 1;
    for (int i = 2; i < sqrtN; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

#define L 8
int val[L];

void tryVals() {
//    cout << "Trying ";
//    for (int i = 0; i < L; i++) {
//        if (val[i] == 10) cout << '*';
//        else cout << val[i];
//    }
//    cout << endl;

    bool starIsFirst = false;
    for (int i = 0; i < L; i++) {
        if (val[i] == 10) {
            starIsFirst = true;
            break;
        } else if (val[i] != 0) break;
    }

    // Try each digit
    int numPrimes = 0, num, smallest;
    for (int d = 0; d < 10; d++) {
        if (d == 0 && starIsFirst) continue;

        // Generate the number
        num = 0;
        for (int i = 0; i < L; i++) {
            if (val[i] == 10) num = num * 10 + d;
            else num = num * 10 + val[i];
        }

        // Check if prime, and add to numPrimes
        if (isPrime[num]) {
            numPrimes++;
            if (numPrimes == 1) smallest = num;
        }
    }
    if (numPrimes == 8) {
        cout << "8 family found: " << smallest << " (star format: ";
        for (int i = 0; i < L; i++) {
            if (val[i] == 10) cout << '*';
            else cout << val[i];
        }
        cout << ")" << endl;
    }
}

void tryLength(int i) {
    if (i == L) {
        // Generated all random digits; try this
        tryVals();
    } else {
        for (int j = 0; j < 11; j++) {
            val[i] = j;
            tryLength(i + 1);
        }
    }
}

int main() {
    for (int i = 2; i < MAXN; i++) isPrime[i] = true;

    for (int i = 2; i < (int) (sqrt(MAXN) + 2); i++) {
        if (isPrime[i]) {
            for (int j = i * 2; j < MAXN; j += i) isPrime[j] = false;
        }
    }

    tryLength(0);
}
