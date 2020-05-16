#include <iostream>
#include <math.h>

using namespace std;

int main() {
    long long N;
    cin >> N;

    int sqrtN = sqrt(N) + 1;
    // cout << sqrtN << endl;

    for (int i = 2; i <= sqrtN; i++) {
        while (N != 1 && N % i == 0) {
            cout << "Prime factor " << i << endl;
            N /= i;
        }
    }

    return 0;
}
