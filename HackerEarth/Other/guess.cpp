/*
Problem: Find the sum of all factors of N except N itself.
*/

#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
    int Q, N;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> N;
        long sum = 0;
        int lim = sqrt(N);
        for (int j = 1; j < lim + 2; j++) {
            if (N % j == 0) {
                if (N / j < j) break;
                else if (N / j == j) {
                    if (N != 1) sum += j;
                    break;
                } else {
                    sum += j;
                    if (j != 1) sum += N / j;
                }
            }
        }
        cout << sum << endl;
    }
}