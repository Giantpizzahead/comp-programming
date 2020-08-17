#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include <iostream>

using namespace std;

int N;

int main() {
    cin >> N;
    int curr5 = 5, answer = 0;
    while (curr5 <= N) {
        answer += N / curr5;
        curr5 *= 5;
    }
    cout << answer << endl;
}